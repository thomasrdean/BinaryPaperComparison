grammar DNS;

// This grammar is really fast: "real    0m12.463s"
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
  EOF
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
  class_=uint16 // change to "class"?
  ;

sequenceOfResourceRecord [int n]
locals [int i = 0]
    : ( {$i < $n}? resourceRecord {$i++;} ) * {$i == $n}?
    ;

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

// Note that we can use '\u0000' safely (without screwing up the byte rule because it acts as an alias for BYTE
typeA: '\u0000' data=TYPE_A {fprintf(stderr, "eating: type A\n");} ;
typeAAAA: '\u0000' data=TYPE_AAAA {fprintf(stderr, "eating: type AAAA\n");} ;
typeCNAME: '\u0000' data=TYPE_CNAME {fprintf(stderr, "eating: type CNAME\n");} ;
typeSOA: '\u0000' data=TYPE_SOA {fprintf(stderr, "eating: type SOA\n");} ;
typeOPT: '\u0000' data=TYPE_OPT {fprintf(stderr, "eating: type OPT\n");} ;
typeNS: '\u0000' data=TYPE_NS {fprintf(stderr, "eating: type NS\n");} ;
typeKEY: '\u0000' data=TYPE_KEY {fprintf(stderr, "eating: type KEY\n");} ;
typeRRSIG: '\u0000' data=TYPE_RRSIG {fprintf(stderr, "eating: type RRSIG\n");} ;
typeDS: '\u0000' data=TYPE_DS {fprintf(stderr, "eating: type DS");} ;
typeNSEC3: '\u0000' data=TYPE_NSEC3 {fprintf(stderr, "eating: type NSEC3\n");} ;

byte returns [int val]
  : data=allTerminals
  {
$val = $data.text[0];
fprintf(stderr, "eating: %x\n", $val);
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
