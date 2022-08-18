To make SCL parse DNS, you need to:
install TXL:
https://www.txl.ca/txl-download.html
clone sclparsergenerator?
`sudo apt install clang` to get `cc`
`sudo apt-get install libpcap-dev` to get pcap.h
`touch my_trace_file; ./bin/pcapparse <pcap> -t my_trace_file`
