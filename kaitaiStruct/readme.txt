Install KaitaiStruct:
http://kaitai.io/#download
`sudo dpkg --install kaitai-struct-compiler_0.10_all.deb`

Compile the Kaitai Struct code into python:
`make`

Optional, create and activate a python virtual environment:
`python3 -m venv venv && source venv/bin/activate`

Install dependencies:
`pip3 install -r requirements.txt`

Run the parser:
`python3 parsePcap.py <your_file>.pcap`


Or, with docker:
`sudo docker build -t kaitai_struct_dns .`
`sudo docker run -it -v ~/msc/DNSpcaps:/DNSpcaps kaitai_struct_dns python3 /kaitai_struct/parsePcap.py /DNSpcaps/dns_all_rr_types_udp.pcap`
