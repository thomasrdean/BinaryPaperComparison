FROM python:3
COPY . /formatFuzzer
WORKDIR /formatFuzzer
RUN apt update && apt install -y unzip libboost-all-dev
RUN unzip formatFuzzer.zip
#RUN python3 -m venv venv && source venv/bin/activate
RUN pip3 install -r FormatFuzzer-master/requirements.txt
RUN ./compile.sh dns.bt
RUN pip3 install -r requirements.txt
#RUN python3 parsePcap.py <your-file>.pcap
