Install KaitaiStruct:
http://kaitai.io/#download
`sudo dpkg --install kaitai-struct-compiler_0.9_all.deb`

Compile the Kaitai Struct code into python:
`make`

Optional, create and activate a python virtual environment:
`python3 -m venv venv && source venv/bin/activate`

Install dependencies:
`pip3 install -r requirements.txt`

Run the parser:
`python3 parsePcap.py <your_file>.pcap`
