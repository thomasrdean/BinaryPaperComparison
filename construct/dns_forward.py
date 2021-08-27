from construct import *
from construct.lib import *

string = Struct(
  "length" / Int8ub,
  "letters" / Byte[this.length],
)

word = Struct(
    "first_byte" / Peek(Byte),
    "is_ref" / Computed(this.first_byte == 0xc0),
    "label" / If(this.is_ref == False, string), # `not this.is_ref` isn't supported by the mechanism that let's us use `this`
    "ref" / If(this.is_ref, Int16ub),
)

domain = RepeatUntil(lambda x,lst,cts: x.is_ref or x.label.length == 0, word)

query_record = Struct(
    "name" / domain,
    "type" / Int16ub,
    "class" / Int16ub,
)

ipv4Address = Byte[4]
ipv6Address = Byte[16]

map_ = Struct(
  "mapNum" / Int8ub,
  "length" / Int8ub,
  "mapbits" / Byte[lambda ctx: ctx["length"]],
)

rrBodyA = Struct(
  "class_" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "address" / ipv4Address,
)
rrBodyAAAA = Struct(
  "class_" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "address" / ipv6Address,
)
rrBodyCNAME = Struct(
  "class_" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "cname" / domain,
)
rrBodySOA = Struct(
  "class_" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "primaryNameServer" / domain,
  "reponsibleAuthority" / domain,
  "serialNumber" / Int32ub,
  "refreshInterval" / Int32ub,
  "retryInterval" / Int32ub,
  "expireLimit" / Int32ub,
  "minimumTTL" / Int32ub,
)
rrBodyOPT = Struct(
  "udpPayloadSize" / Int16ub,
  "higherBitsInExtendedRcode" / Int8ub,
  "EDNS0Version" / Int8ub,
  "z" / Int16ub,
  "dataLength" / Int16ub,
)
rrBodyNS = Struct(
  "class_" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "nameServer" / domain,
)
rrBodyKEY = Struct(
  "class_" / Int16ub,
)
rrBodyRRSIG = Struct(
  "class_" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "typeCov" / Int16ub,
  "alg" / Int8ub,
  "labels" / Int8ub,
  "OrigtimeToLive" / Int32ub,
  "SigExp" / Int32ub,
  "SigInception" / Int32ub,
  "keyTag" / Int16ub,
  "signName" / domain,
  "signature" / Byte[256],
)
rrBodyDS = Struct(
  "class_" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "keyid" / Int16ub,
  "alg" / Int8ub,
  "digestType" / Int8ub,
  "digest" / Byte[32],
)
rrBodyNSEC3 = Struct( # copied from Tom's SCL code, which he is unsure of
  "class_" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "alg" / Int8ub,
  "flags" / Int8ub,
  "iterations" / Int16ub,
  "saltLength" / Int8ub,
  "hashlength" / Int8ub,
  "nexthash" / Byte[lambda ctx: ctx["hashlength"]],
  "typeMap" / map_,
)

resource_record = Struct(
    "names" / domain,
    "type" / Enum(Int16ub,
        TYPE_A=0x01,
        TYPE_AAAA=0x1c, # 28
        TYPE_CNAME=0x05,
        TYPE_SOA=0x06,
        TYPE_OPT=0x29, # 41
        TYPE_NS=0x02,
        TYPE_KEY=0x30, # 48
        TYPE_RRSIG=0x2e, # 46
        TYPE_DS=0x2b, # 43
        TYPE_NSEC3=0x32, # 50
    ),
    "body" / Switch(this.type,
        {
            "TYPE_A": rrBodyA,
            "TYPE_AAAA": rrBodyAAAA,
            "TYPE_CNAME": rrBodyCNAME,
            "TYPE_SOA": rrBodySOA,
            "TYPE_OPT": rrBodyOPT,
            "TYPE_NS": rrBodyNS,
            "TYPE_KEY": rrBodyKEY,
            "TYPE_RRSIG": rrBodyRRSIG,
            "TYPE_DS": rrBodyDS,
            "TYPE_NSEC3": rrBodyNSEC3,
        },
    ),
)

dns = Struct(
    "id" / Int16ub,
    "flags" / Int16ub,
    "question_count" / Int16ub,
    "answer_count" / Int16ub,
    "authority_count" / Int16ub,
    "additional_count" / Int16ub,
    "questions" / query_record[this.question_count],
    "answers" / resource_record[this.answer_count],
    "authorities" / resource_record[this.authority_count],
    "additionals" / resource_record[this.additional_count],
)
