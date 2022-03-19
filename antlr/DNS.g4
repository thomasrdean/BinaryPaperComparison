grammar DNS;

// This grammar is slow: "real    6m35.411s"
// "DNS Packets Parsed: 493" "Total Packets: 509"

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
fprintf(stderr, "Successfully Parsed DNS Packet!!!\n");
  }
  ;

sequenceOfQuery [int n]
locals [int i = 0]
    : ( {$i < $n}? query {$i++;} ) * {$i == $n}?
    ;

query:
  name=domain
  type_=uint16
  class_=uint16
  ;

sequenceOfResourceRecord [int n]
locals [int i = 0]
    : ( {$i < $n}? resourceRecord {$i++;} ) * {$i == $n}?
    ;

resourceRecord:
  name=domain
  type_=uint16
  body=rrBody[$type_.val]
  ;
rrBody [int type_]
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
locals [bool isTerminated = false]
  : ( {!$isTerminated}? word {$isTerminated = $word.isTerminator;} )+ { $isTerminated }?
  ;

word
returns [bool isTerminator = false]
  : nullByte {$isTerminator = true;}
  | refByte reference=byte {$isTerminator = true;}
  | length=uint8 string[$length.val]
  ;

string [int n]
locals [int i = 0]
    : ( {$i < $n}? character {$i++;} ) * {$i == $n}?
    ;

character returns [char val]:
  byte
  {$val = (char) $byte.val;}
  ;

ipv4Address: blob[4];

ipv6Address: blob[16];

blob [int n]
locals [int i = 0]
    : ( {$i < $n}? byte {$i++;} ) * {$i == $n}?
    ;

uint8 returns [uint8_t val]:
  b0=byte
  {$val = $b0.val;}
  ;
uint16 returns [uint16_t val]:
  b0=byte b1=byte // assumes network (big endian) byte order
  {$val = $b0.val << 8 | $b1.val;}
  ;
uint32 returns [uint32_t val]:
  b0=byte b1=byte b2=byte b3=byte
  {$val = $b0.val << 24 | $b1.val << 16 | $b2.val << 8 | $b3.val;}
  ;

nullByte: NULL_BYTE {fprintf(stderr, "eating: null byte\n");} ;
refByte: REF_BYTE {fprintf(stderr, "eating: ref marker\n");} ;

byte returns [uint8_t val]
  : data=allTerminals
  {
$val = (int) $data.text[0];
fprintf(stderr, "eating: %x\n", $val);
  };

allTerminals
  : NULL_BYTE 
  | REF_BYTE
  | BYTE
  ;

NULL_BYTE: '\u0000';
REF_BYTE: '\u00c0';
BYTE: '\u0000'..'\u00FF';
