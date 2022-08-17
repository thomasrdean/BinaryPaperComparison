Optionally, create a virtual environment and activate it:
`python3 -m venv venv && source venv/bin/activate`

Install construct:
`pip3 install -r requirements.txt`

Run the parser:
`python3 parsePcap.py <your-file>.pcap`


Or, with docker:
`docker build -t construct_dns .`
`sudo docker run -it -v ~/msc/DNSpcaps:/DNSpcaps construct_dns python3 /construct/parsePcap.py /DNSpcaps/dns_all_rr_types_udp.pcap`
