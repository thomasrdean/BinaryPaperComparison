First, unzip format fuzzer code:
`unzip formatFuzzer.zip`

Optionally, create a virtual environment:
`python3 -m venv venv && source venv/bin/activate`

Install dependencies:
`sudo apt-get install libboost-all-dev`
`pip3 install -r FormatFuzzer/requirements.txt`
`pip3 install -r requirements.txt`
Compile the binary template:
`./compile.sh dns.bt`
Run the parser:
`python3 parsePcap.py <your_file>.pcap`

Or, with docker:
`sudo docker build -t formatfuzzer_dns .`
`sudo docker run -it -v ~/msc/DNSpcaps:/DNSpcaps formatfuzzer_dns python3 /formatFuzzer/parsePcap.py /DNSpcaps/dns_all_rr_types_udp.pcap`
