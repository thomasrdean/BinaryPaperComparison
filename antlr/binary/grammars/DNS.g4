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
  EOF
  ;

sequenceOfQuery [int n]
locals [int i = 0]
    : ( {$i < $n}? query {$i++;} ) * {$i == $n}?
    ;

query:
  name=domain
  type_=uint16
  class=uint16
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
  | resourceRecordNS
  | resourceRecordCNAME
  | resourceRecordSOA
  | resourceRecordPTR
  | resourceRecordMX
  | resourceRecordTXT
  | resourceRecordAAAA
  | resourceRecordOPT
  | resourceRecordDS
  | resourceRecordRRSIG
  | resourceRecordKEY
  | resourceRecordNSEC3
  ;
resourceRecordA:
  type_=typeA
  class=uint16
  timeToLive=uint32
  dataLength=uint16
  address=ipv4Address
  ;
resourceRecordNS:
  type_=typeNS
  class=uint16
  timeToLive=uint32
  dataLength=uint16
  nameServer=domain
  ;
resourceRecordCNAME:
  type_=typeCNAME
  class=uint16
  timeToLive=uint32
  dataLength=uint16
  cname=domain
  ;
resourceRecordSOA:
  type_=typeSOA
  class=uint16
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
resourceRecordPTR:
  type_=typePTR
  class=uint16
  timeToLive=uint32
  dataLength=uint16
  domainName=domain
  ;
resourceRecordMX:
  type_=typeMX
  class=uint16
  timeToLive=uint32
  dataLength=uint16
  preference=uint16
  mailExchange=domain
  ;
resourceRecordTXT:
  type_=typeTXT
  class=uint16
  timeToLive=uint32
  dataLength=uint16
  text=string[$dataLength.val]
  ;
resourceRecordAAAA:
  type_=typeAAAA
  class=uint16
  timeToLive=uint32
  dataLength=uint16
  address=ipv6Address
  ;
resourceRecordOPT:
  type_=typeOPT
  udpPayloadSize=uint16
  extendedRCode=uint8
  version=uint8
  d0_z=uint16
  dataLength=uint16
  optRecords=string[$dataLength.val]
  ;
resourceRecordDS:
  type_=typeDS
  class=uint16
  timeToLive=uint32
  dataLength=uint16
  keyid=uint16
  alg=uint8
  digestType=uint8
  digest=string[32]
  ;
resourceRecordRRSIG:
  type_=typeRRSIG
  class=uint16
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
  signature=string[$dataLength.val - ($signName.stop->getStopIndex() + 1 - $typeCov.start->getStartIndex())]
  ;
resourceRecordKEY:
  type_=typeKEY
  class=uint16
  timeToLive=uint32
  dataLength=uint16
  flags=uint16
  protocol=uint8
  algorithm=uint8
  key=string[$dataLength.val - 4]
  ;
resourceRecordNSEC3:
  type_=typeNSEC3
  class=uint16
  timeToLive=uint32
  dataLength=uint16
  alg=uint8
  flags=uint8
  iterations=uint16
  saltLength=uint8
  salt=string[$saltLength.val]
  hashLength=uint8
  nextHash=string[$hashLength.val]
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
  | length=letterLength string[$length.val]
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

// Note that we can use '\u0000' safely (without screwing up the byte rule because it acts as an alias for BYTE
typeA: '\u0000' data=TYPE_A;
typeNS: '\u0000' data=TYPE_NS;
typeCNAME: '\u0000' data=TYPE_CNAME;
typeSOA: '\u0000' data=TYPE_SOA;
typePTR: '\u0000' data=TYPE_PTR;
typeMX: '\u0000' data=TYPE_MX;
typeTXT: '\u0000' data=TYPE_TXT;
typeAAAA: '\u0000' data=TYPE_AAAA;
typeOPT: '\u0000' data=TYPE_OPT;
typeDS: '\u0000' data=TYPE_DS;
typeRRSIG: '\u0000' data=TYPE_RRSIG;
typeKEY: '\u0000' data=TYPE_KEY;
typeNSEC3: '\u0000' data=TYPE_NSEC3;

byte returns [uint8_t val]
  : data=allTerminals
  {
$val = $data.text[0];
  };

// Writing both lexer and parser rules is necesary because tokens are classified without knowledge of the parsing context and there is overlap between parser rules (e.g. a nullByte is also a letterByte).
nullByte: NULL_BYTE;
letterLength returns [uint8_t val]
  : data=letterByte
  {
$val = $data.text[0];
  };
letterByte:
  LETTER_LENGTH_BYTE
  | TYPE_A
  | TYPE_NS
  | TYPE_CNAME
  | TYPE_SOA
  | TYPE_PTR
  | TYPE_MX
  | TYPE_TXT
  | TYPE_AAAA
  | TYPE_OPT
  | TYPE_DS
  | TYPE_RRSIG
  | TYPE_KEY
  | TYPE_NSEC3
  ;
refByte: REF_BYTE;

allTerminals
  : NULL_BYTE

  | TYPE_A
  | TYPE_NS
  | TYPE_CNAME
  | TYPE_SOA
  | TYPE_PTR
  | TYPE_MX
  | TYPE_TXT
  | TYPE_AAAA
  | TYPE_OPT
  | TYPE_DS
  | TYPE_RRSIG
  | TYPE_KEY
  | TYPE_NSEC3

  | LETTER_LENGTH_BYTE
  | REF_BYTE

  | BYTE
  ;

// A byte is classified by considering each of the following lexer rules in order.
// So, a byte will only be classified as a BYTE if it is not classified as any of the other tokens.
NULL_BYTE: '\u0000';

TYPE_A: '\u0001';
TYPE_NS: '\u0002';
TYPE_CNAME: '\u0005';
TYPE_SOA: '\u0006';
TYPE_PTR: '\u000c'; // 12
TYPE_MX: '\u000f'; // 15
TYPE_TXT: '\u0010'; // 16
TYPE_AAAA: '\u001c'; // 28
TYPE_OPT: '\u0029'; // 41
TYPE_DS: '\u002b'; // 43
TYPE_RRSIG: '\u002e'; // 46
TYPE_KEY: '\u0030'; // 48
TYPE_NSEC3: '\u0032'; // 50

LETTER_LENGTH_BYTE: '\u0000' .. '\u0040';
REF_BYTE: '\u00c0'..'\u00ff';

BYTE: '\u0000'..'\u00ff';
