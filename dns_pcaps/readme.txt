During the development and testing of the DNS grammar for each framework, pcap files were used to ensure completeness and correctness.

We concatenated a file from wiki.wireshark.org with traffic we recorded to create a pcap file that contains every resource record type present in our grammars.
We also used a pcapng file from packetlife.net to test how parsers handle extra bytes at the end of a packet.

A simple bash script was used to verify that all resource record types are in the pcap file.
This was done by removing alternative structures from the SCL DNS grammar and observing whether or not all packets in the pcap file as parsed without errors.
dns.cap (https://wiki.wireshark.org/uploads/__moin_import__/attachments/SampleCaptures/dns.cap)
from https://wiki.wireshark.org/SampleCaptures
contains 38 packets with a wide variety of resource records and network configurations, so it provided a good starting point.
We were able to increase the coverage of the grammar by concatenating dns.cap with another pcap file that our research group had previously created by recording a demonstration of the RTPS protocol which was then filtered for only UDP DNS packets.
(The only alternative that is not excersized is OptRecord, whose usage is not specified by the DNS protocol specification (RFC6891). Additionally, we were not able to find packets that used a non-empty salt field in NSEC3 resource records, but it is the same concept as used in other parts of the grammar that are tested.)
We called the resulting packet dns_all_rr_types_udp.pcap.

dns-zone-transfer-ixfr.pcapng (https://packetlife.net/media/captures/dns-zone-transfer-ixfr.cap) from https://packetlife.net/captures/protocol/dns/ contains a packet with 2 extra bytes, so it was used to test how parsers handle extra bytes at the end of a packet.
