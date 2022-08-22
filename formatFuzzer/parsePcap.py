import sys
import subprocess
import dpkt

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
    f = open('./tmp', 'wb')
    f.write(dns_bin)
    f.close()
    run_result = subprocess.run(["./dns", "parse", "tmp"], stdout=subprocess.PIPE)
    result = run_result.stdout.decode('ascii')
    assert run_result.returncode == 0
#    print("result:", result)
    num_parsed += 1

#    print(parsed_packet)
  except Exception as e:
    print(e)
    num_failed += 1

print("parsed:", num_parsed, "skipped:", num_skipped, "failed:", num_failed)
