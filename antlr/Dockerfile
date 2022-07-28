FROM ubuntu:22.04
RUN apt update && apt install -y unzip build-essential cmake default-jre libpcap-dev uuid uuid-dev
COPY . /antlr
#COPY binary /antlr
#COPY antlr4Complete /antlr
#COPY antlr4-cpp-runtime-4.10.1-source.zip /antlr
WORKDIR /antlr
RUN unzip antlr4-cpp-runtime-4.10.1-source.zip -d antlr4cpp
WORKDIR antlr4cpp
RUN cmake -DCMAKE_BUILD_TYPE=Debug .
RUN make
WORKDIR ../binary/build
RUN cmake -DCMAKE_BUILD_TYPE=Debug ..
RUN make
#RUN ./parser <pcap>
