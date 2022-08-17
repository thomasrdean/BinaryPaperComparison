FROM ubuntu:22.04
COPY . /kaitai_struct
WORKDIR /kaitai_struct
#RUN apt-get update -y && apt-get install -y java8-runtime-headless
RUN apt-get update -y && apt-get install -y openjdk-8-jre-headless build-essential python3-pip
RUN dpkg --install kaitai-struct-compiler_0.10_all.deb
RUN make
#RUN python3 -m venv venv && source venv/bin/activate
RUN pip3 install -r requirements.txt
#RUN python3 parsePcap.py <your-file>.pcap
