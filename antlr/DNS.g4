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
  class_=uint16 // change to "class"?
  ;

sequenceOfResourceRecord [n]
locals [i = 0]
    : ( {$i < $n}? resourceRecord {$i += 1} ) * {$i == $n}?
    ;

// This approach seems to work
// "parsed: 493 skipped: 16 failed: 0" in exactly 40 seconds
resourceRecord:
  name=domain
  body=rrBody
  ;
rrBody
  : resourceRecordA
  | resourceRecordAAAA
  | resourceRecordCNAME
  | resourceRecordSOA
  | resourceRecordOPT
  | resourceRecordNS
  | resourceRecordKEY
  | resourceRecordRRSIG
  | resourceRecordDS
  | resourceRecordNSEC3
  ;
resourceRecordA:
  type_=typeA
  class_=uint16
  timeToLive=uint32
  dataLength=uint16
  address=ipv4Address
  ;
resourceRecordAAAA:
  type_=typeAAAA
  class_=uint16
  timeToLive=uint32
  dataLength=uint16
  address=ipv6Address
  ;
resourceRecordCNAME:
  type_=typeCNAME
  class_=uint16
  timeToLive=uint32
  dataLength=uint16
  cname=domain
  ;
resourceRecordSOA:
  type_=typeSOA
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
resourceRecordOPT:
  type_=typeOPT
  udpPayloadSize=uint16
  higherBitsInExtendedRcode=uint8
  EDNS0Version=uint8
  z=uint16
  dataLength=uint16
  ;
resourceRecordNS:
  type_=typeNS
  class_=uint16
  timeToLive=uint32
  dataLength=uint16
  nameServer=domain
  ;
resourceRecordKEY:
  type_=typeKEY
  class_=uint16
  ;
resourceRecordRRSIG:
  type_=typeRRSIG
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
resourceRecordDS:
  type_=typeDS
  class_=uint16
  timeToLive=uint32
  dataLength=uint16
  keyid=uint16
  alg=uint8
  digestType=uint8
  digest=string[32]
  ;
resourceRecordNSEC3: // copied from Tom's SCL code, which he is unsure of
  type_=typeNSEC3
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
  | refByte reference=byte {$isTerminator = True}
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

// Note that we can use '\u0000' safely (without screwing up the byte rule because it acts as an alias for BYTE
typeA: '\u0000' data=TYPE_A {print("eating: type ", ord($data.text[0]))} ;
typeAAAA: '\u0000' data=TYPE_AAAA {print("eating: type ", ord($data.text[0]))} ;
typeCNAME: '\u0000' data=TYPE_CNAME {print("eating: type ", ord($data.text[0]))} ;
typeSOA: '\u0000' data=TYPE_SOA {print("eating: type ", ord($data.text[0]))} ;
typeOPT: '\u0000' data=TYPE_OPT {print("eating: type ", ord($data.text[0]))} ;
typeNS: '\u0000' data=TYPE_NS {print("eating: type ", ord($data.text[0]))} ;
typeKEY: '\u0000' data=TYPE_KEY {print("eating: type ", ord($data.text[0]))} ;
typeRRSIG: '\u0000' data=TYPE_RRSIG {print("eating: type ", ord($data.text[0]))} ;
typeDS: '\u0000' data=TYPE_DS {print("eating: type ", ord($data.text[0]))} ;
typeNSEC3: '\u0000' data=TYPE_NSEC3 {print("eating: type ", ord($data.text[0]))} ;

byte returns [val]
  : data=allTerminals
  {
$val = ord($data.text[0])
print("eating:", hex($val))
  };

allTerminals
  : NULL_BYTE 
  | REF_BYTE

  | TYPE_A
  | TYPE_AAAA
  | TYPE_CNAME
  | TYPE_SOA
  | TYPE_OPT
  | TYPE_NS
  | TYPE_KEY
  | TYPE_RRSIG
  | TYPE_DS
  | TYPE_NSEC3

  | BYTE
  ;

NULL_BYTE: '\u0000';
REF_BYTE: '\u00c0';

TYPE_A: '\u0001';
TYPE_AAAA: '\u001c'; // 28
TYPE_CNAME: '\u0005';
TYPE_SOA: '\u0006';
TYPE_OPT: '\u0029'; // 41
TYPE_NS: '\u0002';
TYPE_KEY: '\u0030'; // 48
TYPE_RRSIG: '\u002e'; // 46
TYPE_DS: '\u002b'; // 43
TYPE_NSEC3: '\u0032'; // 50

BYTE: '\u0000'..'\u00FF';
