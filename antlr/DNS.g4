grammar DNS;

dns:
  transactionId=uint16
  flags=uint16
  numQuestion=uint16
  numAnswer=uint16
  numAuthority=uint16
  numAdditional=uint16
  question=sequenceOfQuery[$numQuestion.val]
  answer=sequenceOfResourceRecord[$numAnswer.val]
  authority=sequenceOfResourceRecord[$numAuthority.val]
  additional=sequenceOfResourceRecord[$numAdditional.val]
  {
print("Successfully Parsed DNS Packet!!!")
  }
  ;

sequenceOfQuery [n]
locals [i = 0]
    : ( {$i < $n}? query {$i += 1} ) * {$i == $n}?
    ;

query:
  name=domain
  type_=uint16
  class_=uint16
  ;

sequenceOfResourceRecord [n]
locals [i = 0]
    : ( {$i < $n}? resourceRecord {$i += 1} ) * {$i == $n}?
    ;

resourceRecord:
  name=domain
  type_=uint16
  body=rrBody[$type_.val]
  ;
// this method is working (I manually verified all the fields in the first packet of dns.pcap
// It is a bit slow: parses ~1 packet per second
// "parsed: 493 skipped: 16 failed: 0"
rrBody [type_]
  :
  {$type_ == 1}? rrBodyA
  | {$type_ == 28}? rrBodyAAAA
  | {$type_ == 5}? rrBodyCNAME
  | {$type_ == 6}? rrBodySOA
  | {$type_ == 41}? rrBodyOPT
  | {$type_ == 2}? rrBodyNS
  | {$type_ == 48}? rrBodyKEY
  | {$type_ == 46}? rrBodyRRSIG
  | {$type_ == 43}? rrBodyDS
  | {$type_ == 50}? rrBodyNSEC3
  ;

rrBodyA:
  class_=uint16
  timeToLive=uint32
  dataLength=uint16
  address=ipv4Address
  ;
rrBodyAAAA:
  class_=uint16
  timeToLive=uint32
  dataLength=uint16
  address=ipv6Address
  ;
rrBodyCNAME:
  class_=uint16
  timeToLive=uint32
  dataLength=uint16
  cname=domain
  ;
rrBodySOA:
  class_=uint16
  timeToLive=uint32
  dataLength=uint16
  primaryNameServer=domain
  reponsibleAuthority=domain
  serialNumber=uint32
  refreshInterval=uint32
  retryInterval=uint32
  expireLimit=uint32
  minimumTTL=uint32
  ;
rrBodyOPT:
  udpPayloadSize=uint16
  higherBitsInExtendedRcode=uint8
  EDNS0Version=uint8
  z=uint16
  dataLength=uint16
  ;
rrBodyNS:
  class_=uint16
  timeToLive=uint32
  dataLength=uint16
  nameServer=domain
  ;
rrBodyKEY:
  class_=uint16
  ;
rrBodyRRSIG:
  class_=uint16
  timeToLive=uint32
  dataLength=uint16
  typeCov=uint16
  alg=uint8
  labels=uint8
  OrigtimeToLive=uint32
  SigExp=uint32
  SigInception=uint32
  keyTag=uint16
  signName=domain
  signature=string[256]
  ;
rrBodyDS:
  class_=uint16
  timeToLive=uint32
  dataLength=uint16
  keyid=uint16
  alg=uint8
  digestType=uint8
  digest=string[32]
  ;
rrBodyNSEC3: // copied from Tom's SCL code, which he is unsure of
  class_=uint16
  timeToLive=uint32
  dataLength=uint16
  alg=uint8
  flags=uint8
  iterations=uint16
  saltLength=uint8
  hashlength=uint8
  nexthash=string[$hashlength.val]
  typeMap=map_
  ;

map_:
  mapNum=uint8
  length=uint8
  mapbits=string[$length.val]
  ;

domain
locals [isTerminated = False]
  : ( {not $isTerminated}? word {$isTerminated = $word.isTerminator} )+ { $isTerminated }?
  ;

word
returns [isTerminator = False]
  : nullByte {$isTerminator = True}
  | refByte reference=byte {$isTerminator = True} // if I comment this line then I get "parsed: 297 skipped: 16 failed: 196" in ~12 seconds!
  // ^ so this line makes everything slow!!!!
  | length=uint8 string[$length.val]
  ;

string [n]
locals [i = 0]
    : ( {$i < $n}? character {$i += 1} ) * {$i == $n}?
    ;

character returns [val]:
  byte
  {$val = chr($byte.val)}
  ;

ipv4Address: blob[4];

ipv6Address: blob[16];

blob [n]
locals [i = 0]
    : ( {$i < $n}? byte {$i += 1} ) * {$i == $n}?
    ;

uint8 returns [val]:
  b0=byte
  {$val = $b0.val}
  ;
uint16 returns [val]:
  b0=byte b1=byte // assumes network (big endian) byte order
  {$val = $b0.val << 8 | $b1.val}
  ;
uint32 returns [val]:
  b0=byte b1=byte b2=byte b3=byte
  {$val = $b0.val << 24 | $b1.val << 16 | $b2.val << 8 | $b3.val}
  ;

nullByte: NULL_BYTE {print("eating: null byte")} ;
refByte: REF_BYTE {print("eating: ref marker")} ;

byte returns [val]
  : data=allTerminals
  {
$val = ord($data.text[0])
print("eating:", hex($val))
  };

allTerminals
  : NULL_BYTE 
  | REF_BYTE
  | BYTE
  ;

NULL_BYTE: '\u0000';
REF_BYTE: '\u00c0';
BYTE: '\u0000'..'\u00FF';
