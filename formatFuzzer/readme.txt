First, initialize and fetch the FormatFuzzer submodule:
`git submodule init FormatFuzzer; git submodule update FormatFuzzer`

Optionally, create a virtual environment:
`python3 -m venv venv && source venv/bin/activate`

Install dependencies:
`pip3 install -r FormatFuzzer/requirements.txt`
`pip3 install -r requirements.txt`
Compile the binary template:
`./compile.sh dns.bt`
Run the parser:
`python3 parsePcap.py <your_file>.pcap`

I had to `sudo apt-get install libboost-all-dev`
