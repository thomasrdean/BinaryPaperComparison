from construct import *
from construct.lib import *

word = Select(
    "ref" / Struct(
        "first_byte" / Int8ub,
        Check(this.first_byte == 0xc0),
        "ref" / Int8ub,
    ),
    # `Select` tries subcons in order, so `label` is only tried if `ref` fails
    "label" / Struct(
        "length" / Int8ub,
        "letters" / Byte[this.length],
    ),
)

domain = RepeatUntil(lambda x,lst,cts: hasattr(x, "ref") or x.length == 0, word)

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

rrA = Struct(
  "names" / domain,
  "type" / Int16ub,
  Check(this.type == 0x01),
  "class_" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "address" / ipv4Address,
)
rrAAAA = Struct(
  "names" / domain,
  "type" / Int16ub,
  Check(this.type == 0x1c), # 28
  "class_" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "address" / ipv6Address,
)
rrCNAME = Struct(
  "names" / domain,
  "type" / Int16ub,
  Check(this.type == 0x05),
  "class_" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "cname" / domain,
)
rrSOA = Struct(
  "names" / domain,
  "type" / Int16ub,
  Check(this.type == 0x06),
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
rrOPT = Struct(
  "names" / domain,
  "type" / Int16ub,
  Check(this.type == 0x29), # 41
  "udpPayloadSize" / Int16ub,
  "higherBitsInExtendedRcode" / Int8ub,
  "EDNS0Version" / Int8ub,
  "z" / Int16ub,
  "dataLength" / Int16ub,
)
rrNS = Struct(
  "names" / domain,
  "type" / Int16ub,
  Check(this.type == 0x02),
  "class_" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "nameServer" / domain,
)
rrKEY = Struct(
  "names" / domain,
  "type" / Int16ub,
  Check(this.type == 0x30), # 48
  "class_" / Int16ub,
)
rrRRSIG = Struct(
  "names" / domain,
  "type" / Int16ub,
  Check(this.type == 0x2e), # 46
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
rrDS = Struct(
  "names" / domain,
  "type" / Int16ub,
  Check(this.type == 0x2b), # 43
  "class_" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "keyid" / Int16ub,
  "alg" / Int8ub,
  "digestType" / Int8ub,
  "digest" / Byte[32],
)
rrNSEC3 = Struct( # copied from Tom's SCL code, which he is unsure of
  "names" / domain,
  "type" / Int16ub,
  Check(this.type == 0x32), # 50
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

resource_record = Select(
    rrA,
    rrAAAA,
    rrCNAME,
    rrSOA,
    rrOPT,
    rrNS,
    rrKEY,
    rrRRSIG,
    rrDS,
    rrNSEC3,
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
