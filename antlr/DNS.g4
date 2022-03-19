grammar ARP;

@header {
#include <fstream>
typedef char macArray[8];
typedef unsigned int ipArray[4];

#include <iostream>
}

arp:
  transactionId=uint16
  flags=uint16
  numQuestion=uint16
  numAnswer=uint16
  numAuthority=uint16
  numAdditional=uint16
  question=query
  answer=sequenceOfResourceRecord[$numAnswer.val]
  authority=sequenceOfResourceRecord[$numAuthority.val]
  additional=sequenceOfResourceRecord[$numAdditional.val]
  ;

query:
  name=domain
  type=uint16
  class_=uint16 // change to "class"?
  ;

domain
locals [bool isTerminated = false;] // mutated in word rule
  : ( {!$isTerminated}? word {$isTerminated = $word.isTerminator;} )*
  ;

word
returns [bool isTerminator = false]
  : '\u0000' {$isTerminator = true;}
  | '\u00C0' reference=BYTE {$isTerminator = true;}
  | length=uint8 blob[$length.val]
  ;

sequenceOfResourceRecord [int n]
locals [int i =1; ]
    : ( {$i <= $n}? resourceRecord {$i++;} ) *
    ;

resourceRecord:
  name=domain
  type=uint16
  class_=uint16
  timeToLive=uint32
  dataLength=uint16
  data=blob[$dataLength.val]
  ;

blob [int n]
locals [int i =1; ]
    : ( {$i <= $n}? BYTE {$i++;} ) *
    ;

character returns [char val]:
  BYTE
  {$val = (char) $BYTE.int;}
  ;

uint8 returns [uint8_t val]:
  b0=BYTE
  {$val = $b0.int;}
  ;
uint16 returns [uint16_t val]:
  b0=BYTE b1=BYTE // assumes network (big endian) byte order
  {$val = $b0.int << 8 || $b1.int;}
  ;
uint32 returns [uint32_t val]:
  b0=BYTE b1=BYTE b2=BYTE b3=BYTE
  {$val = $b0.int << 24 || $b1.int << 16 || $b2.int << 8 || $b3.int;}
  ;

BYTE: data='\u0000'..'\u00FF' {fprintf(stderr, "%x", $data.int);};
