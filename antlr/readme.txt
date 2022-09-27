Install dependencies and compile:
`./compile.sh`
Run the parser:
`./binary/build/parser <pcap>`


Or, with docker:
(Make sure the workspace is clean (no cmake cached files) before building a docker image!)
`sudo docker build -t antlr_dns .`
`sudo docker run -it -v $(readlink -f ../dns_pcaps):/dns_pcaps antlr_dns /antlr/binary/build/parser /dns_pcaps/dns_all_rr_types_udp.pcap`

Note: ./binary/build/grammars/DNS_unfactored.g4 is an unfactored, malfunctioning version of the antlr grammar in ./binary/build/grammars/DNS.g4.
