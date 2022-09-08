SCL uses TXL (https://www.txl.ca/) to transform SCL grammars into c code that is able to parse and serialize the protocol specified by the grammar.

Install dependencies:
`sudo apt install clang libpcap-dev`
Install TXL:
https://www.txl.ca/txl-download.html
`tar -xf 31304-txl10.8b.linux64.tar.gz`
Install SCL:
`tar -xf sclparsergenerator-RestructuredParser.tar.gz`
Compile the grammar:
`./compile.sh`
Run the parser:
`touch my_trace_file; ./BUILD/bin/pcapparse <pcap> -t my_trace_file`


Or, with docker:
`sudo docker build -t scl_dns .`
`sudo docker run -it -v $(readlink -f ../dns_pcaps):/dns_pcaps scl_dns /scl/BUILD/bin/pcapparse /dns_pcaps/dns_all_rr_types_udp.pcap`
