import sys
import io
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
  if isinstance(ip.data, bytes):
      tcp_data = ip.data
      return tcp_data
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
    run_result = subprocess.run(["spicy-driver", "dns.hlto"], stdout=subprocess.PIPE, input=dns_bin)
    result = run_result.stdout.decode('ascii')
    assert run_result.returncode == 0
    if result != "":
      print("result:", result)
    num_parsed += 1
  except Exception as e:
    print(e)
    num_failed += 1

print("parsed:", num_parsed, "skipped:", num_skipped, "failed:", num_failed)
