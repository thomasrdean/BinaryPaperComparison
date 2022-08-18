Install dependencies and compile:
`./compile.sh`
Run the parser:
`./parser <pcap>`


Or, with docker:
(Make sure the workspace is clean (no cmake cached files) before building a docker image!)
`sudo docker build -t antlr_dns .`
`sudo docker run -it -v ~/msc/DNSpcaps:/DNSpcaps antlr_dns /antlr/binary/build/parser /DNSpcaps/dns_all_rr_types_udp.pcap`
