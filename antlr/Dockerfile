FROM ubuntu:22.04
RUN apt update && apt install -y unzip build-essential cmake default-jre libpcap-dev uuid uuid-dev
COPY . /antlr
WORKDIR /antlr
RUN ./compile.sh
#RUN ./parser <pcap>
