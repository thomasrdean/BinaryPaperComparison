FROM ubuntu:22.04
RUN apt update && apt install -y build-essential clang libpcap-dev
COPY . /scl
WORKDIR /scl
RUN tar -xf 31304-txl10.8b.linux64.tar.gz
WORKDIR txl10.8b.linux64
RUN ./InstallTxl
WORKDIR ..
RUN tar -xf sclparsergenerator-RestructuredParser.tar.gz
RUN ./compile.sh
#RUN ./parser <pcap>
