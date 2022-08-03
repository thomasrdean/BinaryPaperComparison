#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <getopt.h>

#include <iostream>
#include <string>

#include <pcap.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/igmp.h>
#include <netinet/udp.h>
#include <netinet/if_ether.h>
#include <signal.h>

#include <antlr4-runtime.h>
#include <tree/ParseTreeWalker.h>

#include "antlr4cpp_generated_src/DNS/DNSLexer.h"
#include "antlr4cpp_generated_src/DNS/DNSParser.h"
#include "ByteInputStream.h"

//defines for the packet type code in an ETHERNET header
#define ETHER_TYPE_IP (0x0800)
#define ETHER_TYPE_IPv6 (0x86dd)
#define ETHER_TYPE_8021Q (0x8100)
#define BIGENDIAN (0x0)
#define LITTLEENDIAN (0x1)


char * progname;

//========================================
// args variab les
char * traceFileParserName = NULL;
char * traceFileConsName = NULL;
char * traceFileAppParserName = NULL;
char * traceFileAppConsName = NULL;
char * pcapFileName = NULL;
char * RDFFileName = NULL;
char * envDirectory = NULL;

int record = 0;
int debugLevel = 0;

int numOptErrs = 0;
//========================================

// various files given by opts
FILE * traceFileParser = NULL;
FILE * traceFileCons = NULL;
FILE * traceFileAppParser = NULL;
FILE * traceFileAppCons = NULL;
FILE * rdfFile = NULL;

// num packets, and num failed pase
unsigned long long pduCount = 1;
unsigned long long pduSkipped = 0;
unsigned long long pduFailed = 0;
unsigned long long pduTotal = 0;

pcap_t *pcapHandle = NULL;
static char errbuf[PCAP_ERRBUF_SIZE];

static void findTotal(const char * filename, unsigned long long * total);
static void updateProgress(const unsigned long long * count);
void constraintIntrHandler();
void parserIntrHandler();
static void mainIntrHandler(int signal);
static void userReport(int signal);
static void print_usage();
static void handle_options(int argc, char * argv[]);
static void dump_options();
static void closeFiles();


class BailErrorStrategy : public antlr4::DefaultErrorStrategy {
  public:
    virtual void recover(antlr4::Parser *recognizer, std::exception_ptr e) override;
    virtual antlr4::Token* recoverInline(antlr4::Parser *recognizer) override;
};
void BailErrorStrategy::recover(antlr4::Parser *recognizer, std::exception_ptr e) {
  throw e;
}
antlr4::Token* BailErrorStrategy::recoverInline(antlr4::Parser *recognizer) {
  throw antlr4::InputMismatchException(recognizer);
}
class BinaryErrorListener : public antlr4::BaseErrorListener {
  public:
    virtual void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line,
    size_t charPositionInLine, const std::string &msg, std::exception_ptr e) override;
};

void BinaryErrorListener::syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line,
size_t charPositionInLine, const std::string &msg, std::exception_ptr e) {
  fprintf(stderr, "crap\n");
}

int main(int argc, char * argv[]){

    progname = argv[0];
    handle_options(argc, argv);
    dump_options();

    if(traceFileParserName){
        traceFileParser = fopen(traceFileParserName, "w");
	if (traceFileParser == NULL){
	    fprintf(stderr, "%s: could not open parser trace file %s\n",progname,traceFileParserName);
	    exit(1);
	}
    }

    signal(SIGINT,mainIntrHandler);
    signal(SIGUSR1,userReport);
   
    pcapHandle = pcap_open_offline(pcapFileName, errbuf);
    if (pcapHandle == NULL) {
	fprintf(stderr,"%s: could not open pcap file %s: %s\n", progname, pcapFileName, errbuf);
	exit(1);
    }

    findTotal(pcapFileName, &pduTotal);

    // should be a way to rewind. Aparently, can get the file * 
    // and get the file position and seek to it.
    // but for now, close and reopon.

    pcap_close(pcapHandle);
    pcapHandle = pcap_open_offline(pcapFileName, errbuf);
    if (pcapHandle == NULL) {
	fprintf(stderr,"%s: could not open pcap file %s: %s\n", progname, pcapFileName, errbuf);
	exit(1);
    }

    printf("Total number of packets %lld\n", pduTotal);


    struct pcap_pkthdr head; // The header that pcap gives us
    const unsigned char *packet; // The packet data
	
    while ((packet = pcap_next(pcapHandle,&head)) != NULL) {
        fprintf(stderr, "parsing packet number: %llu\n", pduCount);
	if ((pduCount % 100000) == 0) {
	    updateProgress(&pduCount);
	}

	// header contains information about the packet (e.g. timestamp)
	unsigned char *pkt_ptr = (unsigned char *)packet; //cast a pointer to the packet data

	//parse the first (ethernet) header, grabbing the type field
	int ether_type = ((int)(pkt_ptr[12]) << 8) | (int)pkt_ptr[13];
	int ether_offset = 0;

	if (ether_type == ETHER_TYPE_IP || ether_type == ETHER_TYPE_IPv6)
	    ether_offset = 14;
	else if (ether_type == ETHER_TYPE_8021Q)
	    ether_offset = 18;

	if (ether_offset == 0) {
	    if (traceFileParser) fprintf(traceFileParser,"Unknown ether type %d in packet %lld\n",ether_type,pduCount);
	    // report and move to next packet
	    pduCount++;
	    continue;
	}

	//parse the IP header
	pkt_ptr += ether_offset;  //skip past the Ethernet header
		

	if (ether_type == ETHER_TYPE_IP) {
	    struct ip *ip_hdr = (struct ip *)pkt_ptr; //point to an IP header structure
			
	    if(ip_hdr->ip_p == 0x11) { 

		// *********** UDP ************************

		if (traceFileParser) fprintf(traceFileParser,"%7llu\tUDP",pduCount);
		//if (traceFileParser) fprintf(traceFileParser,"\n");

		pkt_ptr += (ip_hdr->ip_hl * 4); // pass the ip header to the UDP packet.
		struct udphdr * up_hdr = (struct udphdr *) pkt_ptr;
		pkt_ptr += (sizeof(struct udphdr));
		int data_len = ntohs(up_hdr->uh_ulen) - sizeof(struct udphdr);
        if (data_len != ntohs(ip_hdr->ip_len)-ip_hdr->ip_hl*4 - sizeof(struct udphdr)) {
		    fprintf(stderr,"%s: malformed packet (data_len discrepancy) error file: %s line: %d\n",progname, __FILE__ , __LINE__);
        }

        // ***********************************
        // Assume it is a DNS packet
        antlr4::ByteInputStream *bytesFromPacket = new antlr4::ByteInputStream();

        DNS::DNSLexer *dnsLexer = new DNS::DNSLexer(bytesFromPacket);
        antlr4::CommonTokenStream *dnsTokens = new antlr4::CommonTokenStream(dnsLexer);
        DNS::DNSParser *dnsParser = new DNS::DNSParser(dnsTokens);
        // TODO: I think this is a memory leak:
        BinaryErrorListener listener = BinaryErrorListener();
        dnsParser->addErrorListener(&listener);
        dnsParser->setErrorHandler(std::make_shared<BailErrorStrategy>());

        bytesFromPacket->load(reinterpret_cast<const char*>(pkt_ptr), data_len);
        dnsParser->reset();	

        try {
            antlr4::tree::ParseTree * parseTree = dnsParser->dns();
            if (traceFileParser) fprintf(traceFileParser,"\tDNS");
		    if (traceFileParser) fprintf(traceFileParser,"\tSUCCESS");
		    if (traceFileParser) fprintf(traceFileParser,"\n");
        } catch (...) {
		    //fprintf(stderr, "Couldn't Parse packet # %d\n", count+1);
		    if (traceFileParser) fprintf(traceFileParser,"\tFAILED\n");
		    ++pduFailed;
		}
        // ***********************************

	    } else {
	        // ******** OTHER (e.g. TCP) **********************
		if (traceFileParser) fprintf(traceFileParser,"%llu\t\t\tOTHER\n", pduCount);
            ++pduSkipped;
	    }
	} else if (ether_type == ETHER_TYPE_IPv6) {
	    struct ip6_hdr *ip_hdr = (struct ip6_hdr *)pkt_ptr; //point to an IP header structure
			
	    if(ip_hdr->ip6_ctlun.ip6_un1.ip6_un1_nxt == 0x11) { 

		// *********** UDP ************************

		if (traceFileParser) fprintf(traceFileParser,"%7llu\tUDP",pduCount);
		//if (traceFileParser) fprintf(traceFileParser,"\n");

		pkt_ptr += 40; // pass the ip header to the UDP packet.
		struct udphdr * up_hdr = (struct udphdr *) pkt_ptr;
		pkt_ptr += (sizeof(struct udphdr));
		int data_len = ntohs(up_hdr->uh_ulen) - sizeof(struct udphdr);
        if (ip_hdr->ip6_ctlun.ip6_un1.ip6_un1_plen != up_hdr->uh_ulen) {
		    fprintf(stderr,"%s: malformed packet (data_len discrepancy) error file: %s line: %d\n",progname, __FILE__ , __LINE__);
        }

        // ***********************************
        // Assume it is a DNS packet
        antlr4::ByteInputStream *bytesFromPacket = new antlr4::ByteInputStream();

        DNS::DNSLexer *dnsLexer = new DNS::DNSLexer(bytesFromPacket);
        antlr4::CommonTokenStream *dnsTokens = new antlr4::CommonTokenStream(dnsLexer);
        DNS::DNSParser *dnsParser = new DNS::DNSParser(dnsTokens);
        // TODO: I think this is a memory leak:
        BinaryErrorListener listener = BinaryErrorListener();
        dnsParser->addErrorListener(&listener);
        dnsParser->setErrorHandler(std::make_shared<BailErrorStrategy>());

        bytesFromPacket->load(reinterpret_cast<const char*>(pkt_ptr), data_len);
        dnsParser->reset();	

        try {
            antlr4::tree::ParseTree * parseTree = dnsParser->dns();
            if (traceFileParser) fprintf(traceFileParser,"\tDNS");
		    if (traceFileParser) fprintf(traceFileParser,"\tSUCCESS");
		    if (traceFileParser) fprintf(traceFileParser,"\n");
        } catch (...) {
		    //fprintf(stderr, "Couldn't Parse packet # %d\n", count+1);
		    if (traceFileParser) fprintf(traceFileParser,"\tFAILED\n");
		    ++pduFailed;
		}
        // ***********************************
	    } else {
	        // ******** OTHER (e.g. TCP) **********************
		if (traceFileParser) fprintf(traceFileParser,"%llu\t\t\tOTHER\n", pduCount);
            ++pduSkipped;
	    }
	}
	pduCount++;
	//printf("COUNT : %lu\n", count);
    } //end internal loop for reading packets (all in one file)
	
    pcap_close(pcapHandle);  //close the pcap file 


    pduCount -= 1;

    fprintf(stdout, "\nPackets Parsed: %llu\nPackets Failed: %llu\nTotal Packets: %llu\nFailure rate: %0.2f%%\n", pduCount-pduSkipped-pduFailed, pduFailed, pduCount, ((float)pduFailed/pduCount) * 100);
    if(traceFileParser) fprintf(traceFileParser, "\nPackets Parsed: %llu\nPackets Failed: %llu\nTotal Packets: %llu\nFailure rate: %0.2f%%\n", pduCount-pduSkipped-pduFailed, pduFailed, pduCount, ((float)pduFailed/pduCount) * 100);

    closeFiles();
    return 0;
}

//============================================
// command line options
//============================================

static void print_usage() {
        fprintf(stderr, "Usage %s [args] pcapfile\n",progname);
        fprintf(stderr, "-p | --pcap <pCapFile>\n");
        fprintf(stderr, "-t | --traceFile <parserTraceFile>\n");
        fprintf(stderr, "-c | --traceFileCons <constraintTraceFile>\n");
        fprintf(stderr, "-a | --appTraceFile <AppLevelParserTraceFile>\n");
        fprintf(stderr, "-g | --appTtraceFileCons <AppLevelConstraintTraceFile>\n");
        fprintf(stderr, "-e | --recordEnvironment\n");
        fprintf(stderr, "-E | --envDir <dirname>\n");
        fprintf(stderr, "-d | --debugLevel 1..3 \n");
        fprintf(stderr, "-h | --help\n");
        fprintf(stderr, "-r | --RDF <RDFFile>\n");
        exit(1);
}

static struct option long_options[] = {
    {"recordEnvironment", no_argument, 0, 'e'},
    {"envDir", no_argument, 0, 'E'},
    {"traceFile", required_argument, 0, 't'},
    {"traceFileCons", required_argument, 0, 'c'},
    {"appTraceFile", required_argument, 0, 'a'},
    {"appTraceFileCons", required_argument, 0, 'g'},
    {"debugLevel", required_argument, 0, 'd'},
    {"help", no_argument, 0, 'h'},
    {0, 0, 0, 0}
};

static void handle_options(int argc, char * argv[]){

    int option, prev_ind;

    while (prev_ind = optind,(option = getopt_long(argc, argv, ":ehr:t:c:p:d:a:g:E:", long_options, NULL)) != -1){
        if (optarg){
	    if (optind == prev_ind + 2 && *optarg == '-'){
		optopt = option;
		option = ':';
		optind--;
	    }
	}
	switch(option) {
	    case 'e' :
		record = 1;
		break;
	    case 'h' :
		print_usage();
		exit(0);
		break;
	    case 'r' :
		if(strlen(optarg) > 200) { fprintf(stderr, "%s: Filename too long.\n", progname); exit(1); }
		RDFFileName = optarg;
		break;
	    case 'E' :
		if(strlen(optarg) > 200) { fprintf(stderr, "%s: Filename too long.\n", progname); exit(1); }
		envDirectory = optarg;
		break;
	    case 't' :
		if(strlen(optarg) > 200) { fprintf(stderr, "%s: Filename too long.\n", progname); exit(1); }
		traceFileParserName = optarg;
		break;
	    case 'c' :
		if(strlen(optarg) > 200) { fprintf(stderr, "%s: Filename too long.\n", progname); exit(1); }
		traceFileConsName = optarg;
		break;
	    case 'd' :{
	        int d = atoi(optarg);
		if((d < 1) ||(d > 3)) {fprintf(stderr, "debug level is 1 to 3. Value entered: %s\n", optarg); exit(1); }
		debugLevel = d;
		}
		break;
	    case 'a' :
		if(strlen(optarg) > 200) { fprintf(stderr, "%s: Filename too long.\n", progname); exit(1); }
	        traceFileAppParserName = optarg;
		break;
	    case 'g' :
		if(strlen(optarg) > 200) { fprintf(stderr, "%s: Filename too long.\n", progname); exit(1); }
		traceFileAppConsName = optarg;
		break;
	    case '?' :
	        fprintf(stderr,"unregonized option argument %c\n", optopt);
		numOptErrs++;
		break;
	    case ':' :
	        fprintf(stderr,"-%c without value\n", optopt);
		numOptErrs++;
		break;
	    default :
		fprintf(stderr, "getopt default case\n");
		break;

        }
    }

    //printf("after optarg, argc = %d\n", argc);
    //printf("after optarg, optind = %d\n", optind);
    //printf("after optarg, numOptErrs = %d\n", numOptErrs);

    //for (int i = 0; i < argc; i++){
       //printf("%i: %s\n", i, argv[i]);
    //}

    if (argc != optind+1){
       fprintf(stderr,"missing name of pcap file\n");
       numOptErrs++;
    }

    if (numOptErrs > 0){
	print_usage();
    }

    pcapFileName = argv[optind];

}

static void dump_options(){

    if(pcapFileName == NULL){
       fprintf(stderr,"No pcap file name\n");
    } else{
       fprintf(stderr,"pcapFileName = %s\n",pcapFileName);
    }

    if(traceFileParserName == NULL){
       fprintf(stderr,"No parser trace file name\n");
    } else{
       fprintf(stderr,"traceFileParserName = %s\n",traceFileParserName);
    }

    if(traceFileConsName == NULL){
       fprintf(stderr,"No constraint trace file name\n");
    } else{
       fprintf(stderr,"traceFileConsName = %s\n",traceFileConsName);
    }

    if(traceFileAppParserName == NULL){
       fprintf(stderr,"No app parser trace file name\n");
    } else{
       fprintf(stderr,"traceFileAppParserName = %s\n",traceFileAppParserName);
    }

    if(traceFileAppConsName == NULL){
       fprintf(stderr,"No app constraint trace file name\n");
    } else{
       fprintf(stderr,"traceFileAppConsName = %s\n",traceFileAppConsName);
    }

    if(RDFFileName == NULL){
       fprintf(stderr,"No RDF file name\n");
    } else{
       fprintf(stderr,"RDFFileName = %s\n",RDFFileName);
    }

    if(envDirectory == NULL){
       fprintf(stderr,"No environment directory name\n");
    } else{
       fprintf(stderr,"envDirectory = %s\n",envDirectory);
    }

   fprintf(stderr,"record environment = %d\n",record);
   fprintf(stderr,"deubg level = %d\n",debugLevel);
    
}

//============================================
// handle Ctrl - C sanely
//============================================

void constraintIntrHandler() {
}

void parserIntrHandler() {
}

static void mainIntrHandler(int signal){
    // pass int on to others if needed.
    constraintIntrHandler();
    parserIntrHandler();

    // close pcapfile
    if (pcapHandle) pcap_close(pcapHandle);

    // close other files
    closeFiles();

    exit(0);
}

void closeFiles(){
    if(traceFileParser) fclose(traceFileParser);
    if(traceFileCons) fclose(traceFileCons);
    if(traceFileAppParser) fclose(traceFileAppParser);
    if(traceFileAppCons) fclose(traceFileAppCons);
    if(rdfFile) fclose(rdfFile);
}


//============================================
// User report triggered by SIGUSR1
//============================================
static void userReport(int signal)
{
	if (traceFileParser) fflush(traceFileParser);
	if (traceFileCons) fflush(traceFileCons);
}


static void findTotal(const char * filename, unsigned long long * total) {
    *total = 0;
    struct pcap_pkthdr head;
    while(pcap_next(pcapHandle,&head) != NULL) {
	++(*total);
    }
}

static void updateProgress(const unsigned long long * count) {
	//unsigned int complete = (int)(((long double)*count / *total) * 80);
	/*//printf("complete : %d \n", complete);
	static unsigned int previous = 0;
	if ((complete - previous) >= 4) {
		previous = complete;
		if (!start) {
			//printf("%82s", "\b");
			//printf("%82s", "HELLO");
			//fflush(stdout);

			char bar[80];
			for (int i = 0; i < 80; ++i)
				if(i <= complete)
					bar[i] = '*';
				else
					bar[i] = ' ';
			printf("[%s]\n", bar);
			fflush(stdout);
		} else {
			printf("[%80c]", ' ');
			//fflush(stdout);
			start = 0;
		}
	}*/
	printf("*");
	fflush(stdout);
}

// Fuzzer.cpp
// Main driver for FormatFuzzer

#include <unordered_map>
#include <stdlib.h>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <getopt.h>
#include <stdint.h>
#include <climits>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <string>
#include <stdarg.h>

#include "formatfuzzer.h"

static const char *bin_name = "formatfuzzer";

extern bool get_parse_tree;
extern bool debug_print;

extern bool aflsmart_output;

// Each command comes as if it were invoked from the command line

// fuzz - generate random inputs
int fuzz(int argc, char **argv)
{
	const char *decision_source = "/dev/urandom";

	// Process options
	while (1)
	{
		static struct option long_options[] =
			{
				{"help", no_argument, 0, 'h'},
				{"decisions", required_argument, 0, 'd'},
				{0, 0, 0, 0}};
		int option_index = 0;
		int c = getopt_long(argc, argv, "d:p",
							long_options, &option_index);

		// Detect the end of the options.
		if (c == -1)
			break;

		switch (c)
		{
		case 'h':
		case '?':
			fprintf(stderr, "fuzz: usage: fuzz [--decisions SOURCE] [FILES...|-]\n");
			fprintf(stderr, "Outputs random data to given FILES (or `-' for standard output).\n");
			fprintf(stderr, "Options:\n");
			fprintf(stderr, "--decisions SOURCE: Use SOURCE for generation decisions (default %s)\n", decision_source);
			fprintf(stderr, "-p: print parse tree\n");
			return 0;

		case 'd':
			decision_source = optarg;
			break;
		case 'p':
			get_parse_tree = true;
			break;
		}
	}
    
    if (optind >= argc) {
		fprintf(stderr, "%s: missing output files. (Use '-' for standard output)\n", bin_name);
        return 1;
    }

	// Main function
	int errors = 0;
	for (int arg = optind; arg < argc; arg++)
	{
		char *out = argv[arg];
		bool success = false;
		setup_input(decision_source);
		try
		{
			generate_file();
			success = true;
		}
		catch (int status)
		{
			delete_globals();
			if (status == 0)
				success = true;
		}
		catch (...)
		{
			delete_globals();
		}
		save_output(out);
		if (success)
			fprintf(stderr, "%s: %s created\n", bin_name, out);
		else
		{
			fprintf(stderr, "%s: %s failed\n", bin_name, out);
			errors++;
		}
	}

	return errors;
}

// fuzz - parse existing files
int parse(int argc, char **argv)
{
	const char *decision_sink = 0;

	// Process options
	while (1)
	{
		static struct option long_options[] =
			{
				{"help", no_argument, 0, 'h'},
				{"decisions", required_argument, 0, 'd'},
				{0, 0, 0, 0}};
		int option_index = 0;
		int c = getopt_long(argc, argv, "d:s",
							long_options, &option_index);

		// Detect the end of the options.
		if (c == -1)
			break;

		switch (c)
		{
		case 'h':
		case '?':
			fprintf(stderr, "parse: usage: parse [--decisions SINK] [FILES...|-]\n");
			fprintf(stderr, "Parses given FILES (or `-' for standard input).\n");
			fprintf(stderr, "Options:\n");
			fprintf(stderr, "--decisions SINK: Save parsing decisions in SINK (default: none)\n");
			return 0;

		case 'd':
			decision_sink = optarg;
			break;
		case 's':
			aflsmart_output = true;
			break;
		}
	}
    
    if (optind >= argc) {
		fprintf(stderr, "%s: missing input files. (Use '-' for standard input.)\n", bin_name);
        return 1;
    }

	int errors = 0;
	for (int arg = optind; arg < argc; arg++)
	{
		char *in = argv[arg];
		bool success = false;

		set_parser();
		if (!setup_input(in)) {
			errors++;
		}
		try
		{
			generate_file();
			success = true;
		}
		catch (int status)
		{
			delete_globals();
			if (status == 0)
				success = true;
		}
		catch (...)
		{
			delete_globals();
		}
		if (success)
			fprintf(stderr, "ok\n%s: %s parsed\n", bin_name, in);
		else
		{
			fprintf(stderr, "error %.2f\n%s: %s failed\n", 100.0 * get_validity(), bin_name, in);
			errors++;
		}

		if (decision_sink)
			save_output(decision_sink);
	}

	return errors;
}

extern "C" size_t ff_generate(unsigned char* data, size_t size, unsigned char** new_data);
extern "C" int ff_parse(unsigned char* data, size_t size, unsigned char** new_data, size_t* new_size);
extern bool print_errors;
extern std::unordered_map<std::string, std::string> variable_types;

unsigned copy_rand(unsigned char *dest);

extern const char* chunk_name;
extern const char* chunk_name2;
extern int file_index;

extern bool get_chunk;
extern bool get_all_chunks;
extern bool smart_mutation;
extern bool smart_abstraction;
extern bool smart_swapping;
extern unsigned chunk_start;
extern unsigned chunk_end;
extern unsigned rand_start;
extern unsigned rand_end;
extern unsigned rand_start2;
extern unsigned rand_end2;
extern bool is_optional;
extern bool is_delete;
extern bool following_is_optional;

extern unsigned char *following_rand_buffer;
extern unsigned following_rand_size;

extern unsigned char *rand_buffer;

/* Get unix time in microseconds */

static uint64_t get_cur_time_us(void) {

  struct timeval  tv;
  struct timezone tz;

  gettimeofday(&tv, &tz);

  return (tv.tv_sec * 1000000ULL) + tv.tv_usec;

}

void write_file(const char* filename, unsigned char* data, size_t size) {
	printf("Saving file %s\n", filename);
	int file_fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	ssize_t res = write(file_fd, data, size);
	assert((size_t) res == size);
	close(file_fd);
}

// smart_replace - apply a smart replacement
int smart_replace(int argc, char **argv)
{
	char *file_t = NULL;
	int start_t = -1;
	int end_t = -1;
	bool optional_t = false;
	const char* chunk_t;
	char *file_s = NULL;
	int start_s = -1;
	int end_s = -1;
	bool optional_s = false;
	const char* chunk_s;

	bool success_t = false;
	bool success_s = false;

	unsigned char *rand_t = new unsigned char[MAX_RAND_SIZE];
	unsigned char *rand_s = new unsigned char[MAX_RAND_SIZE];
	unsigned len_t;
	int rand_fd = open("/dev/urandom", O_RDONLY);
	ssize_t r = read(rand_fd, rand_t, MAX_RAND_SIZE);
	if (r != MAX_RAND_SIZE)
		printf("Read only %ld bytes from /dev/urandom\n", r);
	close(rand_fd);
	// Process options
	while (1)
	{
		static struct option long_options[] =
			{
				{"help", no_argument, 0, 'h'},
				{"targetfile", required_argument, 0, 1},
				{"targetstart", required_argument, 0, 2},
				{"targetend", required_argument, 0, 3},
				{"sourcefile", required_argument, 0, 4},
				{"sourcestart", required_argument, 0, 5},
				{"sourceend", required_argument, 0, 6},
				{0, 0, 0, 0}};
		int option_index = 0;
		int c = getopt_long(argc, argv, "",
							long_options, &option_index);

		// Detect the end of the options.
		if (c == -1)
			break;

		switch (c)
		{
		case 'h':
		case '?':
			fprintf(stderr, R"(replace: Smart Replacement
replace --targetfile file_t --targetstart start_t --targetend end_t
        --sourcefile file_s --sourcestart start_s --sourceend end_s OUTFILE
			
Apply a smart mutation which replaces one chunk from file_t (byte range
[start_t, end_t]) with another chunk from file_s (byte range [start_s, end_s]).
The resulting file should be similar to file_t, except with the source chunk
from file_s copied into the appropriate position of the target chunk from
file_t.  Moreover, the mutation is smarter than simple memmove() operations,
which should allow it to fix constraints implemented in the binary template,
such as lenght fields and checksums.  Command returns 0 if mutation worked as
expected or nonzero if it didn't work as expected.  This happens when the chunk
from file_s doesn't fit well in file_t because it required a larger or smaller
number of decision bytes in file_t than it did in file_s.
)");
			return 0;

		case 1:
			file_t = optarg;
			break;
		case 2:
			start_t = strtol(optarg, NULL, 0);
			break;
		case 3:
			end_t = strtol(optarg, NULL, 0);
			break;
		case 4:
			file_s = optarg;
			break;
		case 5:
			start_s = strtol(optarg, NULL, 0);
			break;
		case 6:
			end_s = strtol(optarg, NULL, 0);
			break;
		}
	}
    
	if (optind >= argc) {
		fprintf(stderr, "%s: missing output file.\n", bin_name);
		return -2;
	}
	if (!file_t || start_t == -1 || end_t == -1) {
		fprintf(stderr, "%s: missing required arguments for target file.\n", bin_name);
		return -2;
	}
	if (!file_s || start_s == -1 || end_s == -1) {
		fprintf(stderr, "%s: missing required arguments for source file.\n", bin_name);
		return -2;
	}

	// Main function
	char *out = argv[optind];

	printf("Parsing file %s\n\n", file_s);

	get_chunk = true;
	chunk_start = start_s;
	chunk_end = end_s;
	rand_start = rand_end = UINT_MAX;
	set_parser();
	setup_input(file_s);
	try
	{
		generate_file();
		success_s = true;
	}
	catch (int status)
	{
		delete_globals();
		if (status == 0)
			success_s = true;
	}
	catch (...)
	{
		delete_globals();
	}
	if (!success_s)
	{
		fprintf(stderr, "%s: Parsing %s failed\n", bin_name, file_s);
	}
	if (rand_start == UINT_MAX) {
		fprintf(stderr, "%s: Unable to find chunk in file %s\n", bin_name, file_s);
		return -2;
	}
	copy_rand(rand_s);
	start_s = rand_start;
	end_s = rand_end;
	optional_s = is_optional;
	chunk_s = chunk_name;


	printf("\nParsing file %s\n\n", file_t);

	get_chunk = true;
	chunk_start = start_t;
	chunk_end = end_t;
	rand_start = rand_end = UINT_MAX;
	set_parser();
	setup_input(file_t);
	try
	{
		generate_file();
		success_t = true;
	}
	catch (int status)
	{
		delete_globals();
		if (status == 0)
			success_t = true;
	}
	catch (...)
	{
		delete_globals();
	}
	if (!success_t)
	{
		fprintf(stderr, "%s: Parsing %s failed\n", bin_name, file_t);
	}
	if (end_t != -1 && rand_start == UINT_MAX) {
		fprintf(stderr, "%s: Unable to find chunk in file %s\n", bin_name, file_t);
		return -2;
	}
	len_t = copy_rand(rand_t);
	start_t = rand_start;
	end_t = rand_end;
	optional_t = is_optional;
	chunk_t = chunk_name;

	if (optional_t && !optional_s) {
		fprintf(stderr, "%s: Trying to copy non-optional chunk from file %s into optional chunk from file %s\n", bin_name, file_s, file_t);
		return -2;
	}
	if (!optional_t && optional_s) {
		fprintf(stderr, "%s: Trying to copy optional chunk from file %s into non-optional chunk from file %s\n", bin_name, file_s, file_t);
		return -2;
	}
	if (!optional_t && !optional_s && variable_types[chunk_t] != variable_types[chunk_s]) {
		fprintf(stderr, "%s: Trying to replace non-optional chunks of different types: %s, %s\n", bin_name, variable_types[chunk_t].c_str(), variable_types[chunk_s].c_str());
		return -2;
	}

	printf("\nGenerating file %s\n\n", out);

	unsigned rand_size = len_t + (end_s - start_s) - (end_t - start_t);
	assert(rand_size <= MAX_RAND_SIZE);
	memmove(rand_t + start_t + end_s + 1 - start_s, rand_t + end_t + 1, len_t - (end_t + 1));
	memcpy(rand_t + start_t, rand_s + start_s, end_s + 1 - start_s);

	get_chunk = false;
	smart_mutation = true;
	unsigned rand_end0 = rand_end = start_t + end_s - start_s;
	set_generator();

	unsigned char* file = NULL;
	unsigned file_size = ff_generate(rand_t, MAX_RAND_SIZE, &file);
	if (!file || !file_size) {
		printf("Failed to generate mutated file!\n");
		return -2;
	}
	save_output(out);
	if (rand_end0 < rand_end)
		fprintf(stderr, "Warning: Consumed %u more decision bytes than expected while generating chunk.\n", rand_end - rand_end0);
	if (rand_end0 > rand_end)
		fprintf(stderr, "Warning: Consumed %u less decision bytes than expected while generating chunk.\n", rand_end0 - rand_end);
	fprintf(stderr, "%s: %s created\n", bin_name, out);

	delete[] rand_t;
	delete[] rand_s;
	if (!success_s || !success_t)
		return -2;
	return (rand_end > rand_end0) - (rand_end < rand_end0);
}





// smart_delete - apply a smart deletion
int smart_delete(int argc, char **argv)
{
	char *file_t = NULL;
	int start_t = -1;
	int end_t = -1;
	bool optional_t = false;

	bool success = false;

	unsigned char *rand_t = new unsigned char[MAX_RAND_SIZE];
	unsigned len_t;
	int rand_fd = open("/dev/urandom", O_RDONLY);
	ssize_t r = read(rand_fd, rand_t, MAX_RAND_SIZE);
	if (r != MAX_RAND_SIZE)
		printf("Read only %ld bytes from /dev/urandom\n", r);
	close(rand_fd);
	// Process options
	while (1)
	{
		static struct option long_options[] =
			{
				{"help", no_argument, 0, 'h'},
				{"targetfile", required_argument, 0, 1},
				{"targetstart", required_argument, 0, 2},
				{"targetend", required_argument, 0, 3},
				{0, 0, 0, 0}};
		int option_index = 0;
		int c = getopt_long(argc, argv, "",
							long_options, &option_index);

		// Detect the end of the options.
		if (c == -1)
			break;

		switch (c)
		{
		case 'h':
		case '?':
			fprintf(stderr, R"(delete: Smart Deletion
delete --targetfile file_t --targetstart start_t --targetend end_t OUTFILE

Apply a smart deletion operation, removing one chunk from file_t (byte range
[start_t, end_t]).  This can only be applied if the chunk is optional and the
following chunk is also optional.  A chunk is optional if there are calls to
FEof() and/or lookahead functions such as ReadBytes() right before the start
of the chunk.  This smart deletion should also fix constraints implemented in
the binary template (such as length fields).
)");
			return 0;

		case 1:
			file_t = optarg;
			break;
		case 2:
			start_t = strtol(optarg, NULL, 0);
			break;
		case 3:
			end_t = strtol(optarg, NULL, 0);
			break;
		}
	}
    
	if (optind >= argc) {
		fprintf(stderr, "%s: missing output file.\n", bin_name);
		return -2;
	}
	if (!file_t || start_t == -1 || end_t == -1) {
		fprintf(stderr, "%s: missing required arguments for target file.\n", bin_name);
		return -2;
	}

	// Main function
	char *out = argv[optind];


	printf("\nParsing file %s\n\n", file_t);
	success = false;
	is_delete = true;

	get_chunk = true;
	chunk_start = start_t;
	chunk_end = end_t;
	rand_start = rand_end = UINT_MAX;
	set_parser();
	setup_input(file_t);
	try
	{
		generate_file();
		success = true;
	}
	catch (int status)
	{
		delete_globals();
		if (status == 0)
			success = true;
	}
	catch (...)
	{
		delete_globals();
	}
	if (!success)
	{
		fprintf(stderr, "%s: Parsing %s failed\n", bin_name, file_t);
	}
	if (rand_start == UINT_MAX) {
		fprintf(stderr, "%s: Unable to find chunk in file %s\n", bin_name, file_t);
		return -2;
	}
	len_t = copy_rand(rand_t);
	start_t = rand_start;
	end_t = rand_end;
	optional_t = is_optional;

	if (!optional_t) {
		fprintf(stderr, "%s: The target chunk is not optional.\n", bin_name);
		return -2;
	}
	if (!following_is_optional) {
		fprintf(stderr, "%s: The target chunk is not followed by an optional chunk.\n", bin_name);
		return -2;
	}

	printf("\nGenerating file %s\n\n", out);

	memmove(rand_t + start_t, rand_t + end_t + 1, len_t - (end_t + 1));

	get_chunk = false;
	set_generator();

	unsigned char* file = NULL;
	unsigned file_size = ff_generate(rand_t, MAX_RAND_SIZE, &file);
	if (!file || !file_size) {
		printf("Failed to generate mutated file!\n");
		return -2;
	}
	save_output(out);
	fprintf(stderr, "%s: %s created\n", bin_name, out);

	delete[] rand_t;
	return success ? 0 : -2;
}





// smart_insert - apply a smart insertion
int smart_insert(int argc, char **argv)
{
	char *file_t = NULL;
	int start_t = -1;
	char *file_s = NULL;
	int start_s = -1;
	int end_s = -1;
	bool optional_s = false;

	bool success_t = false;
	bool success_s = false;

	unsigned char *rand_t = new unsigned char[MAX_RAND_SIZE];
	unsigned char *rand_s = new unsigned char[MAX_RAND_SIZE];
	unsigned len_t;
	int rand_fd = open("/dev/urandom", O_RDONLY);
	ssize_t r = read(rand_fd, rand_t, MAX_RAND_SIZE);
	if (r != MAX_RAND_SIZE)
		printf("Read only %ld bytes from /dev/urandom\n", r);
	close(rand_fd);
	// Process options
	while (1)
	{
		static struct option long_options[] =
			{
				{"help", no_argument, 0, 'h'},
				{"targetfile", required_argument, 0, 1},
				{"targetstart", required_argument, 0, 2},
				{"sourcefile", required_argument, 0, 4},
				{"sourcestart", required_argument, 0, 5},
				{"sourceend", required_argument, 0, 6},
				{0, 0, 0, 0}};
		int option_index = 0;
		int c = getopt_long(argc, argv, "",
							long_options, &option_index);

		// Detect the end of the options.
		if (c == -1)
			break;

		switch (c)
		{
		case 'h':
		case '?':
			fprintf(stderr, R"(insert: Smart Insertion
insert --targetfile file_t --targetstart start_t
       --sourcefile file_s --sourcestart start_s --sourceend end_s OUTFILE

Apply a smart insertion operation, inserting one chunk from file_s (byte range
[start_s, end_s]) into file_t, with the first byte at start_t.  This can only
be applied if file_t originally had an optional chunk starting at start_t or
if start_t was the position right after the end of an appendable chunk.  A
chunk is optional if there are calls to FEof() and/or lookahead functions such
as ReadBytes() right before the start of the chunk.  A chunk is appendable if
there are calls to FEof() and/or lookahead functions such as ReadBytes() right
before the end of the chunk.  The source chunk from file_s must also be
optional.  This smart addition should also fix constraints implemented in the
binary template (such as length fields).  Command returns 0 if mutation worked
as expected or nonzero if it didn't work as expected.  This happens when the
chunk from file_s doesn't fit well in file_t because it required a larger or
smaller number of decision bytes in file_t than it did in file_s.
)");
			return 0;

		case 1:
			file_t = optarg;
			break;
		case 2:
			start_t = strtol(optarg, NULL, 0);
			break;
		case 4:
			file_s = optarg;
			break;
		case 5:
			start_s = strtol(optarg, NULL, 0);
			break;
		case 6:
			end_s = strtol(optarg, NULL, 0);
			break;
		}
	}
    
	if (optind >= argc) {
		fprintf(stderr, "%s: missing output file.\n", bin_name);
		return -2;
	}
	if (!file_t || start_t == -1) {
		fprintf(stderr, "%s: missing required arguments for target file.\n", bin_name);
		return -2;
	}
	if (!file_s || start_s == -1 || end_s == -1) {
		fprintf(stderr, "%s: missing required arguments for source file.\n", bin_name);
		return -2;
	}

	// Main function
	char *out = argv[optind];

	printf("Parsing file %s\n\n", file_s);

	get_chunk = true;
	chunk_start = start_s;
	chunk_end = end_s;
	rand_start = rand_end = UINT_MAX;
	set_parser();
	setup_input(file_s);
	try
	{
		generate_file();
		success_s = true;
	}
	catch (int status)
	{
		delete_globals();
		if (status == 0)
			success_s = true;
	}
	catch (...)
	{
		delete_globals();
	}
	if (!success_s)
	{
		fprintf(stderr, "%s: Parsing %s failed\n", bin_name, file_s);
	}
	if (rand_start == UINT_MAX) {
		fprintf(stderr, "%s: Unable to find chunk in file %s\n", bin_name, file_s);
		return -2;
	}
	copy_rand(rand_s);
	start_s = rand_start;
	end_s = rand_end;
	optional_s = is_optional;


	printf("\nParsing file %s\n\n", file_t);

	get_chunk = true;
	chunk_start = start_t;
	chunk_end = -1;
	rand_start = rand_end = UINT_MAX;
	set_parser();
	setup_input(file_t);
	try
	{
		generate_file();
		success_t = true;
	}
	catch (int status)
	{
		delete_globals();
		if (status == 0)
			success_t = true;
	}
	catch (...)
	{
		delete_globals();
	}
	if (!success_t)
	{
		fprintf(stderr, "%s: Parsing %s failed\n", bin_name, file_t);
	}
	len_t = copy_rand(rand_t);
	start_t = rand_start;

	if (rand_start == UINT_MAX) {
		fprintf(stderr, "%s: Invalid position for insertion into file %s.\n", bin_name, file_t);
		fprintf(stderr, "Insertion can only happen at the start of an optional chunk or after the end of an appendable chunk/file.\n");
		return -2;
	}
	if (!optional_s) {
		fprintf(stderr, "%s: Trying to insert non-optional chunk from file %s.\n", bin_name, file_s);
		return -2;
	}
	
	printf("\nGenerating file %s\n\n", out);

	unsigned rand_size = len_t + (end_s + 1 - start_s);
	assert(rand_size <= MAX_RAND_SIZE);
	memmove(rand_t + start_t + end_s + 1 - start_s, rand_t + start_t, len_t - start_t);
	memcpy(rand_t + start_t, rand_s + start_s, end_s + 1 - start_s);

	get_chunk = false;
	smart_mutation = true;
	is_optional = true;
	unsigned rand_end0 = rand_end = start_t + end_s - start_s;
	set_generator();

	unsigned char* file = NULL;
	unsigned file_size = ff_generate(rand_t, MAX_RAND_SIZE, &file);
	if (!file || !file_size) {
		printf("Failed to generate mutated file!\n");
		return -2;
	}
	save_output(out);
	if (rand_end0 < rand_end)
		fprintf(stderr, "Warning: Consumed %u more decision bytes than expected while generating chunk.\n", rand_end - rand_end0);
	if (rand_end0 > rand_end)
		fprintf(stderr, "Warning: Consumed %u less decision bytes than expected while generating chunk.\n", rand_end0 - rand_end);
	fprintf(stderr, "%s: %s created\n", bin_name, out);

	delete[] rand_t;
	delete[] rand_s;
	if (!success_s || !success_t)
		return -2;
	return (rand_end > rand_end0) - (rand_end < rand_end0);
}



// smart_abstract - randomize a chunk
int smart_abstract(int argc, char **argv)
{
	char *file_t = NULL;
	int start_t = -1;
	int end_t = -1;

	bool success = false;

	unsigned char *rand_t = new unsigned char[MAX_RAND_SIZE];
	unsigned len_t;
	int rand_fd = open("/dev/urandom", O_RDONLY);
	ssize_t r = read(rand_fd, rand_t, MAX_RAND_SIZE);
	if (r != MAX_RAND_SIZE)
		printf("Read only %ld bytes from /dev/urandom\n", r);

	// Process options
	while (1)
	{
		static struct option long_options[] =
			{
				{"help", no_argument, 0, 'h'},
				{"targetfile", required_argument, 0, 1},
				{"targetstart", required_argument, 0, 2},
				{"targetend", required_argument, 0, 3},
				{0, 0, 0, 0}};
		int option_index = 0;
		int c = getopt_long(argc, argv, "",
							long_options, &option_index);

		// Detect the end of the options.
		if (c == -1)
			break;

		switch (c)
		{
		case 'h':
		case '?':
			fprintf(stderr, R"(abstract: Smart Abstraction
abstract --targetfile file_t --targetstart start_t --targetend end_t OUTFILE

Apply a smart abstraction operation, randomizing one chunk from file_t (byte
range [start_t, end_t]).  The contents of the chunk will be randomly
generated, while trying to preserve decisions made before and after the
chunk.  This smart abstraction should also fix constraints implemented in
the binary template (such as length fields).
)");
			return 0;

		case 1:
			file_t = optarg;
			break;
		case 2:
			start_t = strtol(optarg, NULL, 0);
			break;
		case 3:
			end_t = strtol(optarg, NULL, 0);
			break;
		}
	}
    
	if (optind >= argc) {
		fprintf(stderr, "%s: missing output file.\n", bin_name);
		return -2;
	}
	if (!file_t || start_t == -1 || end_t == -1) {
		fprintf(stderr, "%s: missing required arguments for target file.\n", bin_name);
		return -2;
	}

	// Main function
	char *out = argv[optind];


	printf("\nParsing file %s\n\n", file_t);
	success = false;

	get_chunk = true;
	chunk_start = start_t;
	chunk_end = end_t;
	rand_start = rand_end = UINT_MAX;
	set_parser();
	setup_input(file_t);
	try
	{
		generate_file();
		success = true;
	}
	catch (int status)
	{
		delete_globals();
		if (status == 0)
			success = true;
	}
	catch (...)
	{
		delete_globals();
	}
	if (!success)
	{
		fprintf(stderr, "%s: Parsing %s failed\n", bin_name, file_t);
	}
	if (rand_start == UINT_MAX) {
		fprintf(stderr, "%s: Unable to find chunk in file %s\n", bin_name, file_t);
		return -2;
	}
	len_t = copy_rand(rand_t);
	start_t = rand_start;
	end_t = rand_end;

	printf("\nGenerating file %s\n\n", out);

	following_rand_size = len_t - (end_t + 1);
	following_rand_buffer = new unsigned char[following_rand_size];
	memcpy(following_rand_buffer, rand_t + end_t + 1, following_rand_size);

	r = read(rand_fd, rand_t + start_t, len_t - start_t);
	if (r != len_t - start_t)
		printf("Read only %ld bytes from /dev/urandom\n", r);
	close(rand_fd);

	get_chunk = false;
	smart_abstraction = true;
	set_generator();

	unsigned char* file = NULL;
	unsigned file_size = ff_generate(rand_t, MAX_RAND_SIZE, &file);
	if (!file || !file_size) {
		printf("Failed to generate mutated file!\n");
		return -2;
	}
	save_output(out);
	fprintf(stderr, "%s: %s created\n", bin_name, out);

	delete[] rand_t;
	delete[] following_rand_buffer;
	if (smart_abstraction) {
		printf("Abstracted chunk was not created!\n");
		return -1;
	}
	return success ? 0 : -2;
}


// smart_swap - apply a smart swap
int smart_swap(int argc, char **argv)
{
	char *file_t = NULL;
	int start_t = -1;
	int end_t = -1;
	bool optional_t = false;
	const char* chunk_t;
	int start_s = -1;
	int end_s = -1;
	bool optional_s = false;
	const char* chunk_s;

	bool success = false;

	unsigned char *rand_t = new unsigned char[MAX_RAND_SIZE];
	unsigned char *rand_s = new unsigned char[MAX_RAND_SIZE];
	unsigned len_t;
	int rand_fd = open("/dev/urandom", O_RDONLY);
	ssize_t r = read(rand_fd, rand_t, MAX_RAND_SIZE);
	if (r != MAX_RAND_SIZE)
		printf("Read only %ld bytes from /dev/urandom\n", r);
	close(rand_fd);
	// Process options
	while (1)
	{
		static struct option long_options[] =
			{
				{"help", no_argument, 0, 'h'},
				{"targetfile", required_argument, 0, 1},
				{"targetstart", required_argument, 0, 2},
				{"targetend", required_argument, 0, 3},
				{"sourcestart", required_argument, 0, 5},
				{"sourceend", required_argument, 0, 6},
				{0, 0, 0, 0}};
		int option_index = 0;
		int c = getopt_long(argc, argv, "",
							long_options, &option_index);

		// Detect the end of the options.
		if (c == -1)
			break;

		switch (c)
		{
		case 'h':
		case '?':
			fprintf(stderr, R"(swap: Smart Swap
swap --targetfile file_t --targetstart start_t --targetend end_t
                       [--sourcestart start_s] --sourceend end_s OUTFILE
			
Apply a smart swap operation which swaps the order of two chunks from file_t
(byte ranges [start_t, end_t] and [start_s, end_s]).  If start_s is not
specified, it is assumed to be equal to end_t + 1 (two consecutive chunks).
The mutation is smarter than simple memmove() operations, which should allow
it to fix constraints implemented in the binary template, such as lenght
fields and checksums.  Command returns 0 if mutation worked as expected or
nonzero if it didn't work as expected.  This happens when one chunk doesn't
fit well in the position of the other chunk because it required a larger or
smaller number of decision bytes.
)");
			return 0;

		case 1:
			file_t = optarg;
			break;
		case 2:
			start_t = strtol(optarg, NULL, 0);
			break;
		case 3:
			end_t = strtol(optarg, NULL, 0);
			break;
		case 5:
			start_s = strtol(optarg, NULL, 0);
			break;
		case 6:
			end_s = strtol(optarg, NULL, 0);
			break;
		}
	}
    
	if (optind >= argc) {
		fprintf(stderr, "%s: missing output file.\n", bin_name);
		return -2;
	}
	if (!file_t || start_t == -1 || end_t == -1 || end_s == -1) {
		fprintf(stderr, "%s: missing required arguments.\n", bin_name);
		return -2;
	}
	if (start_s == -1)
		start_s = end_t + 1;

	if (start_t > end_s) {
		int start_tmp = start_t;
		int end_tmp = end_t;
		start_t = start_s;
		end_t = end_s;
		start_s = start_tmp;
		end_s = end_tmp;
	}

	// Main function
	char *out = argv[optind];

	printf("Parsing file %s\n\n", file_t);
	success = false;

	get_chunk = true;
	chunk_start = start_s;
	chunk_end = end_s;
	rand_start = rand_end = UINT_MAX;
	set_parser();
	setup_input(file_t);
	try
	{
		generate_file();
		success = true;
	}
	catch (int status)
	{
		delete_globals();
		if (status == 0)
			success = true;
	}
	catch (...)
	{
		delete_globals();
	}
	if (!success)
	{
		fprintf(stderr, "%s: Parsing %s failed\n", bin_name, file_t);
	}
	if (rand_start == UINT_MAX) {
		fprintf(stderr, "%s: Unable to find source chunk in file %s\n", bin_name, file_t);
		return -2;
	}
	copy_rand(rand_s);
	start_s = rand_start;
	end_s = rand_end;
	optional_s = is_optional;
	chunk_s = chunk_name;


	printf("\nParsing file %s\n\n", file_t);
	success = false;

	get_chunk = true;
	chunk_start = start_t;
	chunk_end = end_t;
	rand_start = rand_end = UINT_MAX;
	set_parser();
	setup_input(file_t);
	try
	{
		generate_file();
		success = true;
	}
	catch (int status)
	{
		delete_globals();
		if (status == 0)
			success = true;
	}
	catch (...)
	{
		delete_globals();
	}
	if (!success)
	{
		fprintf(stderr, "%s: Parsing %s failed\n", bin_name, file_t);
	}
	if (end_t != -1 && rand_start == UINT_MAX) {
		fprintf(stderr, "%s: Unable to find target chunk in file %s\n", bin_name, file_t);
		return -2;
	}
	len_t = copy_rand(rand_t);
	start_t = rand_start;
	end_t = rand_end;
	optional_t = is_optional;
	chunk_t = chunk_name;

	if ((optional_t && !optional_s) || (!optional_t && optional_s)) {
		fprintf(stderr, "%s: Trying to swap optional and non-optional chunks from file %s\n", bin_name, file_t);
		return -2;
	}
	if (!optional_t && !optional_s && variable_types[chunk_t] != variable_types[chunk_s]) {
		fprintf(stderr, "%s: Trying to swap non-optional chunks of different types: %s, %s\n", bin_name, variable_types[chunk_t].c_str(), variable_types[chunk_s].c_str());
		return -2;
	}

	printf("\nGenerating file %s\n\n", out);

	unsigned rand_end20 = rand_end2 = 0;
	
	if (start_s > end_t) {
		memcpy(rand_t + start_t, rand_s + start_s, end_s + 1 - start_s);
		memcpy(rand_t + start_t + end_s + 1 - start_s, rand_s + end_t + 1, start_s - end_t - 1);
		memcpy(rand_t + start_t + end_s - end_t, rand_s + start_t, end_t + 1 - start_t);
		smart_swapping = true;
		chunk_name2 = chunk_s;
		rand_start2 = start_t + end_s - end_t;
		rand_end2 = end_s;
		rand_end20 = rand_end2;
	} else {
		memcpy(rand_t + start_t, rand_s + start_s, end_s + 1 - start_s);
		memcpy(rand_t + start_t + end_s + 1 - start_s, rand_s + end_t + 1, len_t - end_t - 1);
		if (end_t - start_t < end_s - start_s) {
			smart_swapping = true;
			chunk_name2 = chunk_s;
			rand_start2 = start_s;
			rand_end2 = end_s + (end_s - start_s) - (end_t - start_t);
			rand_end20 = rand_end2;
		}
	}

	get_chunk = false;
	smart_mutation = true;
	unsigned rand_end0 = rand_end = start_t + end_s - start_s;
	set_generator();

	unsigned char* file = NULL;
	unsigned file_size = ff_generate(rand_t, MAX_RAND_SIZE, &file);
	if (!file || !file_size) {
		printf("Failed to generate mutated file!\n");
		return -2;
	}
	save_output(out);
	if (rand_end0 < rand_end)
		fprintf(stderr, "Warning: Consumed %u more decision bytes than expected while generating chunk.\n", rand_end - rand_end0);
	if (rand_end0 > rand_end)
		fprintf(stderr, "Warning: Consumed %u less decision bytes than expected while generating chunk.\n", rand_end0 - rand_end);
	fprintf(stderr, "%s: %s created\n", bin_name, out);

	delete[] rand_t;
	delete[] rand_s;
	if (rand_end0 != rand_end)
		return success ? (rand_end > rand_end0) - (rand_end < rand_end0) : -2;

	if (rand_end20 < rand_end2)
		fprintf(stderr, "Warning: Consumed %u more decision bytes than expected while generating second chunk.\n", rand_end2 - rand_end20);
	if (rand_end20 > rand_end2)
		fprintf(stderr, "Warning: Consumed %u less decision bytes than expected while generating second chunk.\n", rand_end20 - rand_end2);
	return success ? (rand_end2 > rand_end20) - (rand_end2 < rand_end20) : -2;
}


extern "C" int process_file(const char *file_name, const char *rand_name) {
	rand_names.push_back(rand_name);
	insertion_points.push_back({});
	deletable_chunks.push_back({});
	non_optional_index.push_back({});
	bool success = false;

	get_all_chunks = true;
	set_parser();
	setup_input(file_name);
	debug_print = false;
	try
	{
		generate_file();
		success = true;
	}
	catch (int status)
	{
		delete_globals();
		if (status == 0)
			success = true;
	}
	catch (...)
	{
		delete_globals();
	}
	get_all_chunks = false;
	save_output(rand_name);
	++file_index;
	optional_index.push_back(optional_chunks.size());
	if (!success && debug_print)
	{
		fprintf(stderr, "%s: Parsing %s failed\n", bin_name, file_name);
	}
	return 100.0 * get_validity();

}

unsigned read_rand_file(const char* file_name, unsigned char* rand_buffer) {
	int file_fd = open(file_name, O_RDONLY);
	if (file_fd == -1) {
		perror(file_name);
		exit(1);
	}
	ssize_t size = read(file_fd, rand_buffer, MAX_RAND_SIZE);
	if (size < 0) {
		perror("Failed to read seed file");
		exit(1);
	}
	close(file_fd);
	return size;
}

char mutation_info[1024];
char* print_pos = mutation_info;
size_t buf_size = 1024;

void reset_info() {
	print_pos = mutation_info;
	buf_size = 1024;
}

void log_info(const char * fmt, ...) {
	va_list args;
	va_start(args,fmt);
	int printed = vsnprintf(print_pos, buf_size, fmt, args);
	va_end(args);
	assert((unsigned)printed < buf_size);
	print_pos += printed;
	buf_size -= printed;
}



extern "C" void generate_random_file(unsigned char** file, unsigned* file_size) {
	int rand_fd = open("/dev/urandom", O_RDONLY);
	ssize_t r = read(rand_fd, rand_buffer, MAX_RAND_SIZE);
	if (r != MAX_RAND_SIZE)
		printf("Read only %ld bytes from /dev/urandom\n", r);
	close(rand_fd);

	set_generator();
	*file_size = ff_generate(rand_buffer, MAX_RAND_SIZE, file);
}



extern "C" int one_smart_mutation(int target_file_index, unsigned char** file, unsigned* file_size) {
	static unsigned char *original_rand_t = NULL;
	static unsigned char *rand_t = NULL;
	static unsigned char *rand_s = NULL;
	if (!rand_t) {
		original_rand_t = new unsigned char[MAX_RAND_SIZE];
		rand_t = new unsigned char[MAX_RAND_SIZE];
		rand_s = new unsigned char[MAX_RAND_SIZE];
		int rand_fd = open("/dev/urandom", O_RDONLY);
		ssize_t r = read(rand_fd, rand_t, MAX_RAND_SIZE);
		if (r != MAX_RAND_SIZE)
			printf("Read only %ld bytes from /dev/urandom\n", r);
		close(rand_fd);
	}
	static int previous_file_index = -1;
	static unsigned len_t = 0;
	if (target_file_index != previous_file_index) {
		len_t = read_rand_file(rand_names[target_file_index].c_str(), original_rand_t);
		previous_file_index = target_file_index;
	}

	reset_info();
	bool old_debug_print = debug_print;
	switch (rand() % (deletable_chunks[target_file_index].size() ? 10 : 9)) {
	case 0:
	{
		if (non_optional_index[target_file_index].size() == 0)
			goto fail;
		NonOptional& no = non_optional_index[target_file_index][rand() % non_optional_index[target_file_index].size()];
		if (no.size == 0)
			goto fail;
		int chunk_index = no.start + rand() % no.size;
		Chunk& t = non_optional_chunks[no.type][chunk_index];
		if (non_optional_chunks[no.type].size() == 0)
			goto fail;
		Chunk& s = non_optional_chunks[no.type][rand() % non_optional_chunks[no.type].size()];
		log_info("Replacing: source non-optional chunk from file %d position %u %u %s %s\ninto target file %d non-optional chunk position %u %u %s %s\n", s.file_index, s.start, s.end, s.type, s.name, t.file_index, t.start, t.end, t.type, t.name);
		memcpy(rand_t, original_rand_t, len_t);
		read_rand_file(rand_names[s.file_index].c_str(), rand_s);

		unsigned rand_size = len_t + (s.end - s.start) - (t.end - t.start);
		if (rand_size > MAX_RAND_SIZE) {
			*file = NULL;
			*file_size = 0;
			if (debug_print)
				printf("rand_size insufficient for smart mutation\n");
			return -2;
		}
		memmove(rand_t + t.start + s.end + 1 - s.start, rand_t + t.end + 1, len_t - (t.end + 1));
		memcpy(rand_t + t.start, rand_s + s.start, s.end + 1 - s.start);

		smart_mutation = true;
		get_parse_tree = true;
		rand_start = t.start;
		is_optional = false;
		chunk_name = t.name;
		unsigned rand_end0 = rand_end = t.start + s.end - s.start;
		set_generator();

		*file = NULL;
		debug_print = false;
		*file_size = ff_generate(rand_t, MAX_RAND_SIZE, file);
		smart_mutation = false;
		get_parse_tree = false;
		debug_print = old_debug_print;
		if (!(*file) || !(*file_size)) {
			log_info("Failed to generate mutated file!\n");
			if (debug_print)
				printf("%s", mutation_info);
			return -2;
		}
		if (rand_end0 < rand_end)
			log_info("Warning: Consumed %u more decision bytes than expected while generating chunk.\n", rand_end - rand_end0);
		if (rand_end0 > rand_end)
			log_info("Warning: Consumed %u less decision bytes than expected while generating chunk.\n", rand_end0 - rand_end);
		if (debug_print)
			printf("%s", mutation_info);
		return (rand_end > rand_end0) - (rand_end < rand_end0);
	}
	case 1:
	case 2:
	{
		if ((optional_index[target_file_index+1] - optional_index[target_file_index]) == 0)
			goto fail;
		int chunk_index = optional_index[target_file_index] + rand() % (optional_index[target_file_index+1] - optional_index[target_file_index]);
		Chunk& t = optional_chunks[chunk_index];
		if (optional_chunks.size() == 0)
			goto fail;
		Chunk& s = optional_chunks[rand() % optional_chunks.size()];
		log_info("Replacing: source optional chunk from file %d position %u %u %s %s\ninto target file %d optional chunk position %u %u %s %s\n", s.file_index, s.start, s.end, s.type, s.name, t.file_index, t.start, t.end, t.type, t.name);
		memcpy(rand_t, original_rand_t, len_t);
		read_rand_file(rand_names[s.file_index].c_str(), rand_s);

		unsigned rand_size = len_t + (s.end - s.start) - (t.end - t.start);
		if (rand_size > MAX_RAND_SIZE) {
			*file = NULL;
			*file_size = 0;
			if (debug_print)
				printf("rand_size insufficient for smart mutation\n");
			return -2;
		}
		memmove(rand_t + t.start + s.end + 1 - s.start, rand_t + t.end + 1, len_t - (t.end + 1));
		memcpy(rand_t + t.start, rand_s + s.start, s.end + 1 - s.start);

		smart_mutation = true;
		get_parse_tree = true;
		rand_start = t.start;
		is_optional = true;
		chunk_name = t.name;
		unsigned rand_end0 = rand_end = t.start + s.end - s.start;
		set_generator();

		*file = NULL;
		debug_print = false;
		*file_size = ff_generate(rand_t, MAX_RAND_SIZE, file);
		smart_mutation = false;
		get_parse_tree = false;
		debug_print = old_debug_print;
		if (!(*file) || !(*file_size)) {
			log_info("Failed to generate mutated file!\n");
			if (debug_print)
				printf("%s", mutation_info);
			return -2;
		}
		if (rand_end0 < rand_end)
			log_info("Warning: Consumed %u more decision bytes than expected while generating chunk.\n", rand_end - rand_end0);
		if (rand_end0 > rand_end)
			log_info("Warning: Consumed %u less decision bytes than expected while generating chunk.\n", rand_end0 - rand_end);

		if (debug_print)
			printf("%s", mutation_info);
		return (rand_end > rand_end0) - (rand_end < rand_end0);
	}
	case 3:
	case 4:
	{
		if (insertion_points[target_file_index].size() == 0)
			goto fail;
		InsertionPoint& ip = insertion_points[target_file_index][rand() % insertion_points[target_file_index].size()];
		if (optional_chunks.size() == 0)
			goto fail;
		Chunk& s = optional_chunks[rand() % optional_chunks.size()];
		log_info("Inserting: source chunk from file %d position %u %u %s %s\ninto target file %d position %u %s %s\n", s.file_index, s.start, s.end, s.type, s.name, target_file_index, ip.pos, ip.type, ip.name);
		memcpy(rand_t, original_rand_t, len_t);
		read_rand_file(rand_names[s.file_index].c_str(), rand_s);

		unsigned rand_size = len_t + (s.end + 1 - s.start);
		if (rand_size > MAX_RAND_SIZE) {
			*file = NULL;
			*file_size = 0;
			if (debug_print)
				printf("rand_size insufficient for smart mutation\n");
			return -2;
		}
		memmove(rand_t + ip.pos + s.end + 1 - s.start, rand_t + ip.pos, len_t - ip.pos);
		memcpy(rand_t + ip.pos, rand_s + s.start, s.end + 1 - s.start);

		smart_mutation = true;
		get_parse_tree = true;
		rand_start = ip.pos;
		is_optional = true;
		chunk_name = s.name;
		unsigned rand_end0 = rand_end = ip.pos + s.end - s.start;
		set_generator();

		*file = NULL;
		debug_print = false;
		*file_size = ff_generate(rand_t, MAX_RAND_SIZE, file);
		smart_mutation = false;
		get_parse_tree = false;
		debug_print = old_debug_print;
		if (!(*file) || !(*file_size)) {
			log_info("Failed to generate mutated file!\n");
			if (debug_print)
				printf("%s", mutation_info);
			return -2;
		}
		if (rand_end0 < rand_end)
			log_info("Warning: Consumed %u more decision bytes than expected while generating chunk.\n", rand_end - rand_end0);
		if (rand_end0 > rand_end)
			log_info("Warning: Consumed %u less decision bytes than expected while generating chunk.\n", rand_end0 - rand_end);

		if (debug_print)
			printf("%s", mutation_info);
		return (rand_end > rand_end0) - (rand_end < rand_end0);
	}
	case 5:
	case 6:
	case 7:
	case 8:
	{
		int start_t = -1;
		int end_t = -1;
		if (rand() % 2) {
			if (non_optional_index[target_file_index].size() == 0)
				goto fail;
			NonOptional& no = non_optional_index[target_file_index][rand() % non_optional_index[target_file_index].size()];
			if (no.size == 0)
				goto fail;
			int chunk_index = no.start + rand() % no.size;
			Chunk& t = non_optional_chunks[no.type][chunk_index];
			log_info("Abstracting from file %d non-optional chunk %u %u %s %s\n", t.file_index, t.start, t.end, t.type, t.name);
			start_t = t.start;
			end_t = t.end;
			is_optional = false;
			chunk_name = t.name;
		} else {
			if ((optional_index[target_file_index+1] - optional_index[target_file_index]) == 0)
				goto fail;
			int chunk_index = optional_index[target_file_index] + rand() % (optional_index[target_file_index+1] - optional_index[target_file_index]);
			Chunk& t = optional_chunks[chunk_index];
			log_info("Abstracting from file %d optional chunk %u %u %s %s\n", t.file_index, t.start, t.end, t.type, t.name);
			start_t = t.start;
			end_t = t.end;
			is_optional = true;
			chunk_name = t.name;
		}
		memcpy(rand_t, original_rand_t, len_t);

		following_rand_size = len_t - (end_t + 1);
		following_rand_buffer = rand_s;
		memcpy(following_rand_buffer, rand_t + end_t + 1, following_rand_size);

		int rand_fd = open("/dev/urandom", O_RDONLY);
		ssize_t r = read(rand_fd, rand_t + start_t, len_t - start_t);
		if (r != len_t - start_t)
			printf("Read only %ld bytes from /dev/urandom\n", r);
		close(rand_fd);

		smart_abstraction = true;
		get_parse_tree = true;
		rand_start = start_t;
		set_generator();

		*file = NULL;
		debug_print = false;
		*file_size = ff_generate(rand_t, MAX_RAND_SIZE, file);
		get_parse_tree = false;
		debug_print = old_debug_print;
		if (smart_abstraction) {
			smart_abstraction = false;
			log_info("Abstracted chunk was not created!\n");
			if (debug_print)
				printf("%s", mutation_info);
			return -1;
		}
		if (!(*file) || !(*file_size)) {
			log_info("Failed to generate mutated file!\n");
			if (debug_print)
				printf("%s", mutation_info);
			return -2;
		}

		if (debug_print)
			printf("%s", mutation_info);
		return 0;
	}
	case 9:
	{
		if (deletable_chunks[target_file_index].size() == 0)
			goto fail;
		int index = rand() % deletable_chunks[target_file_index].size();
		Chunk& t = deletable_chunks[target_file_index][index];
		log_info("Deleting from file %d chunk %u %u %s %s\n", t.file_index, t.start, t.end, t.type, t.name);
		memcpy(rand_t, original_rand_t, len_t);

		memmove(rand_t + t.start, rand_t + t.end + 1, len_t - (t.end + 1));

		deletable_chunks[target_file_index].erase(deletable_chunks[target_file_index].begin() + index);

		set_generator();

		*file = NULL;
		debug_print = false;
		*file_size = ff_generate(rand_t, MAX_RAND_SIZE, file);
		debug_print = old_debug_print;
		if (!(*file) || !(*file_size)) {
			log_info("Failed to generate mutated file!\n");
			if (debug_print)
				printf("%s", mutation_info);
			return -2;
		}

		if (debug_print)
			printf("%s", mutation_info);
		return 0;
	}
	}
	return -2;
fail:
	*file = NULL;
	*file_size = 0;
	if (debug_print)
		printf("no chunk available\n");
	return -2;
}

int mutations(int argc, char **argv)
{
	srand(time(NULL));
	for (int i = 1; i < argc; ++i) {
		char *file_name = argv[i];
		std::string rand_name = std::string(file_name) + "-decisions";
		process_file(file_name, rand_name.c_str());
	}
	unsigned char* file;
	unsigned size;
	debug_print = true;
	print_errors = true;
	for (int i = 0; i < 10000; ++i) {
		int result = one_smart_mutation(i % rand_names.size(), &file, &size);
		if (debug_print)
			printf("%d\n", result);
	}
	return 0;
}


int test(int argc, char *argv[])
{
	print_errors = true;
	int rand_fd = open("/dev/urandom", O_RDONLY);
	unsigned char *data = new unsigned char[MAX_RAND_SIZE];
	ssize_t r = read(rand_fd, data, MAX_RAND_SIZE);
	if (r != MAX_RAND_SIZE)
		printf("Read only %ld bytes from /dev/urandom\n", r);
	unsigned char *contents = new unsigned char[MAX_FILE_SIZE];
	unsigned char* file = NULL;
	size_t file_size;
	unsigned char* rand = NULL;
	size_t rand_size;
	size_t new_file_size = 0;
	int generated = 0;
	int i;
	int iterations = 10000;
	uint64_t start = get_cur_time_us();
	uint64_t parse_time = 0;
	for (i = 0; i < iterations; ++i)
	{
		ssize_t r = read(rand_fd, data, 4096);
		assert(r == 4096);
		file_size = ff_generate(data, MAX_RAND_SIZE, &file);
		if (file_size && file) {
			generated += 1;
			uint64_t before = get_cur_time_us();
			bool parsed = ff_parse(file, file_size, &rand, &rand_size);
			uint64_t after = get_cur_time_us();
			parse_time += after - before;
			assert(file_size <= MAX_FILE_SIZE);
			memcpy(contents, file, file_size);
			memset(file, 0, file_size);
			file = NULL;
			if (!parsed) {
				printf("Failed to parse!\n");
				break;
			}
			new_file_size = ff_generate(rand, rand_size, &file);
			if (!file || !file_size) {
				printf("Failed to re-generate!\n");
				break;
			}
			if (file_size != new_file_size || memcmp(contents, file, file_size)) {
				printf("Re-generated file different from original file!\n");
				break;
			}
		}
	}
	if (i != iterations) {
		write_file("r0", data, MAX_RAND_SIZE);
		write_file("f0", contents, file_size);
		write_file("r1", rand, rand_size);
		if (file)
			write_file("f1", file, new_file_size);
	}
	uint64_t end = get_cur_time_us();
	double time = (end - start) / 1.0e6;
	double ptime = parse_time / 1.0e6;
	printf("Tested %d files from %d attempts in %f s (parsing speed %f / s).\n", generated, i, time, generated / ptime);
	delete[] data;
	delete[] contents;
	return 0;
}

int benchmark(int argc, char *argv[])
{
	int rand_fd = open("/dev/urandom", O_RDONLY);
	unsigned char *data =  new unsigned char[MAX_RAND_SIZE];
	ssize_t r = read(rand_fd, data, MAX_RAND_SIZE);
	if (r != MAX_RAND_SIZE)
		printf("Read only %ld bytes from /dev/urandom\n", r);
	unsigned char* new_data = NULL;
	int generated = 0;
	int valid = 0;
	uint64_t total_bytes = 0;
	int i;
	int iterations = 10000;
	std::unordered_map<int,int> status;
	std::string fmt = std::string(bin_name, strchr(bin_name, '-') - bin_name);
	std::string output = "out." + fmt;
	std::string checker = "checkers/" + fmt + ".sh";
	uint64_t start = get_cur_time_us();
	for (i = 0; i < iterations; ++i)
	{
		ssize_t r = read(rand_fd, data, 4096);
		assert(r == 4096);
		size_t new_size = ff_generate(data, MAX_RAND_SIZE, &new_data);
		if (new_size && new_data) {
			generated += 1;
			total_bytes += new_size;
			if (argc > 1) {
				save_output(output.c_str());
				int result = system(checker.c_str());
				if (WIFEXITED(result)) {
					++status[WEXITSTATUS(result)];
				}
				if (WIFSIGNALED(result)) {
					printf("killed by signal %d\n", WTERMSIG(result));
				}
				if (WIFEXITED(result) && WEXITSTATUS(result) == 0)
					++valid;
			}
		}
	}
	uint64_t end = get_cur_time_us();
	double time = (end - start) / 1.0e6;
	for (auto s : status)
		printf("status %d: %d\n", s.first, s.second);
	printf("Generated %d files from %d attempts in %f s.\n", generated, i, time);
	if (argc > 1)
		printf("Valid %d/%d = %f\n", valid, generated, (double)valid/(double)generated);
	if (generated)
		printf("Average file size %lu bytes.\n", total_bytes / generated);
	printf("Speed %f / s.\n", generated / time);
	delete[] data;
	return 0;
}

int version(int argc, char *argv[])
{
	fprintf(stderr, "This is FormatFuzzer 1.0\n");
	return 0;
}

// Dispatch commands
typedef struct
{
	const char *name;
	int (*fun)(int argc, char **argv);
	const char *desc;
} COMMAND;

COMMAND commands[] = {
	{"fuzz", fuzz, "Generate random inputs"},
	{"parse", parse, "Parse inputs"},
	{"replace", smart_replace, "Apply a smart replacement"},
	{"delete", smart_delete, "Apply a smart deletion"},
	{"insert", smart_insert, "Apply a smart insertion"},
	{"abstract", smart_abstract, "Apply a smart abstraction"},
	{"swap", smart_swap, "Apply a smart swap"},
	{"mutations", mutations, "Smart mutations"},
	{"test", test, "Test if fuzzer is working properly (sanity checks)"},
	{"benchmark", benchmark, "Benchmark fuzzing"},
	{"version", version, "Show version"},
};

int help(int argc, char *argv[])
{
	version(argc, argv);
	fprintf(stderr, "%s: usage: %s COMMAND [OPTIONS...] [ARGS...]\n", bin_name, bin_name);
	fprintf(stderr, "Commands:\n");
	for (unsigned i = 0; i < sizeof(commands) / sizeof(COMMAND); i++)
		fprintf(stderr, "%-10s - %s\n", commands[i].name, commands[i].desc);
	fprintf(stderr, "Use COMMAND --help to learn more\n");
	return 0;
}

int main(int argc, char **argv)
{
	bin_name = get_bin_name(argv[0]);
	if (argc <= 1)
		return help(argc, argv);

	char *cmd = argv[1];
	for (unsigned i = 0; i < sizeof(commands) / sizeof(COMMAND); i++)
	{
		if (strcmp(cmd, commands[i].name) == 0)
			return (*commands[i].fun)(argc - 1, argv + 1);
	}

	// Invalid command
	help(argc, argv);
	return -1;
}
