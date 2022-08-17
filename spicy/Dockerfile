FROM ubuntu:22.04
RUN apt update && apt install -y build-essential python3-pip
COPY . /spicy
WORKDIR /spicy
RUN dpkg --install spicy-dev.deb
RUN make
#RUN python3 -m venv venv && source venv/bin/activate
RUN pip3 install -r requirements.txt
#RUN python3 parsePcap.py
