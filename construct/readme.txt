Optionally, create a virtual environment and activate it:
`python3 -m venv venv && source venv/bin/activate`

Install construct:
`pip3 install -r requirements.txt`

Run the parser:
`python3 parsePcap.py <your-file>.pcap`


Or, with docker:
`sudo docker build -t construct_dns .`
`sudo docker run -it -v $(readlink -f ../dns_pcaps):/dns_pcaps construct_dns python3 /construct/parsePcap.py /dns_pcaps/dns_all_rr_types_udp.pcap`

Note: dns_switch.py is a different version of dns.py, which uses `Switch` instead of `Select`.
