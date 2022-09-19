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
    virtual void sync(antlr4::Parser *recognizer) override;
};
void BailErrorStrategy::recover(antlr4::Parser *recognizer, std::exception_ptr e) {
  throw e;
}
antlr4::Token* BailErrorStrategy::recoverInline(antlr4::Parser *recognizer) {
  throw antlr4::InputMismatchException(recognizer);
}
void BailErrorStrategy::sync(antlr4::Parser *recognizer) {}
class BinaryErrorListener : public antlr4::BaseErrorListener {
  public:
    virtual void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line,
    size_t charPositionInLine, const std::string &msg, std::exception_ptr e) override;
};

void BinaryErrorListener::syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line,
size_t charPositionInLine, const std::string &msg, std::exception_ptr e) {
  fprintf(stderr, "Error!\n");
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
        //fprintf(stderr, "parsing packet number: %llu\n", pduCount);
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
        // dnsParser->getInterpreter<antlr4::atn::ParserATNSimulator>()->setPredictionMode(antlr4::atn::PredictionMode::LL_EXACT_AMBIG_DETECTION);
        // dnsParser->setTrace(true);
        BinaryErrorListener listener = BinaryErrorListener();
        // dnsParser->addErrorListener(new antlr4::DiagnosticErrorListener());
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
        delete bytesFromPacket;
        delete dnsLexer;
        delete dnsTokens;
        delete dnsParser;
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
        // dnsParser->getInterpreter<antlr4::atn::ParserATNSimulator>()->setPredictionMode(antlr4::atn::PredictionMode::LL_EXACT_AMBIG_DETECTION);
        // dnsParser->setTrace(true);
        BinaryErrorListener listener = BinaryErrorListener();
        dnsParser->addErrorListener(&listener);
        // dnsParser->addErrorListener(new antlr4::DiagnosticErrorListener());
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
        delete bytesFromPacket;
        delete dnsLexer;
        delete dnsTokens;
        delete dnsParser;
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

