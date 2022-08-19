Optionally, create a virtual environment and activate it:
`python3 -m venv venv && source venv/bin/activate`

Install Spicy from:
https://docs.zeek.org/projects/spicy/en/latest/installation.html

Install dependencies:
`pip3 install -r requirements.txt`

Compile the grammar:
`make`

Run the parser:
`python3 parsePcap.py <your-file>.pcap`


Or, with docker:
`sudo docker build -t spicy_dns .`
`sudo docker run -it -v $(readlink -f ../dns_pcaps):/dns_pcaps spicy_dns python3 /spicy/parsePcap.py /dns_pcaps/dns_all_rr_types_udp.pcap`
