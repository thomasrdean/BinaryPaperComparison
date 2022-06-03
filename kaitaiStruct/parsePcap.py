import sys
import dpkt

import dns_packet

if len(sys.argv) != 2:
  print("Please provide one arg (a pcap file).")
  sys.exit()

pcap_file = sys.argv[1]
f = open(pcap_file, "rb")
pcap = dpkt.pcapng.Reader(f)
pcap_elements = list(pcap)
f.close()

num_parsed = 0
num_skipped = 0
num_failed = 0

def pcap_element_to_dns(pcap_element):
  ts, buf = pcap_element
  eth = dpkt.ethernet.Ethernet(buf)
  ip = eth.data
  udp = ip.data
  dns = udp.data
  return dns

for pcap_element in pcap_elements:
  dns_bin = pcap_element_to_dns(pcap_element)
  
  try:
    if dns_bin == b'':
      num_skipped += 1
      continue
    dns_bin = pcap_element_to_dns(pcap_element)
    parsed_packet = dns_packet.DnsPacket.from_bytes(dns_bin)
    num_parsed += 1

#    print(parsed_packet)
  except Exception as e:
    print(e)
    num_failed += 1

print("parsed:", num_parsed, "skipped:", num_skipped, "failed:", num_failed)
