grammar DNS;

@header {
#include <fstream>
typedef char macArray[8];
typedef unsigned int ipArray[4];

#include <iostream>
}

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
  { fprintf(stderr, "Successfully Parsed DNS Packet!!!\n"); }
  ;

sequenceOfQuery [int n]
locals [int i =1; ]
    : ( {$i <= $n}? query {$i++;} ) * {$i == $n}?
    ;

query:
  name=domain
  type=uint16
  class_=uint16 // change to "class"?
  ;

domain
locals [bool isTerminated = false;] // mutated in word rule
  : ( {!$isTerminated}? word {$isTerminated = $word.isTerminator;} )+ { $isTerminated }?
  ;

word
returns [bool isTerminator = false]
  : nullByte {$isTerminator = true;}
  | refByte reference=byte {$isTerminator = true;}
  | length=uint8 blob[$length.val]
  ;

sequenceOfResourceRecord [int n]
locals [int i =1; ]
    : ( {$i <= $n}? resourceRecord {$i++;} ) * {$i == $n}?
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
    : ( {$i <= $n}? byte {$i++;} ) * {$i == $n}?
    ;

character returns [char val]:
  byte
  {$val = (char) $byte.val;}
  ;

uint8 returns [uint8_t val]:
  b0=byte
  {$val = $b0.val;}
  ;
uint16 returns [uint16_t val]:
  b0=byte b1=byte // assumes network (big endian) byte order
  {$val = $b0.val << 8 || $b1.val;}
  ;
uint32 returns [uint32_t val]:
  b0=byte b1=byte b2=byte b3=byte
  {$val = $b0.val << 24 || $b1.val << 16 || $b2.val << 8 || $b3.val;}
  ;

byte returns [int val]:
  data=BYTE {
    $val = $data->getText()[0];
    /* fprintf(stderr, "eating: %x\n", $data->getText()[0]); */
  };

nullByte: BYTE {$BYTE->getText()[0] == 0x00}? { /* fprintf(stderr, "recognizing null byte\n"); */ } ;
refByte: BYTE {$BYTE->getText()[0] == 0xc0}? ;

BYTE: '\u0000'..'\u00FF';
