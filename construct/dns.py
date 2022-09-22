from construct import *
from construct.lib import *

word = Select(
  "ref" / Struct(
    "first_byte" / Int8ub,
    Check(this.first_byte >= 0xc0),
    "ref" / Int8ub,
  ),
  "label" / Struct(
    "length" / Int8ub,
    Check(this.length < 0x40),
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
  "mapbits" / Byte[this.length],
)

rrA = Struct(
  "name" / domain,
  "type" / Int16ub,
  Check(this.type == 0x01),
  "class" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "address" / ipv4Address,
)
rrNS = Struct(
  "name" / domain,
  "type" / Int16ub,
  Check(this.type == 0x02),
  "class" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "nameerver" / domain,
)
rrCNAME = Struct(
  "name" / domain,
  "type" / Int16ub,
  Check(this.type == 0x05),
  "class" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "cname" / domain,
)
rrSOA = Struct(
  "name" / domain,
  "type" / Int16ub,
  Check(this.type == 0x06),
  "class" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "primarynameerver" / domain,
  "reponsibleAuthority" / domain,
  "serialNumber" / Int32ub,
  "refreshInterval" / Int32ub,
  "retryInterval" / Int32ub,
  "expireLimit" / Int32ub,
  "minimumTTL" / Int32ub,
)
rrPTR = Struct(
  "name" / domain,
  "type" / Int16ub,
  Check(this.type == 0x0c), # 12
  "class" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "domainName" / domain,
)
rrMX = Struct(
  "name" / domain,
  "type" / Int16ub,
  Check(this.type == 0x0f), # 15
  "class" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "preference" / Int16ub,
  "mailExchange" / domain,
)
rrTXT = Struct(
  "name" / domain,
  "type" / Int16ub,
  Check(this.type == 0x10), # 16
  "class" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "text" / Byte[this.dataLength],
)
rrAAAA = Struct(
  "name" / domain,
  "type" / Int16ub,
  Check(this.type == 0x1c), # 28
  "class" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "address" / ipv6Address,
)
rrOPT = Struct(
  "name" / domain,
  "type" / Int16ub,
  Check(this.type == 0x29), # 41
  "udpPayloadSize" / Int16ub,
  "extendedRCode" / Int8ub,
  "version" / Int8ub,
  "d0_z" / Int16ub,
  "dataLength" / Int16ub,
  "optRecords" / Byte[this.dataLength],
)
rrDS = Struct(
  "name" / domain,
  "type" / Int16ub,
  Check(this.type == 0x2b), # 43
  "class" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "keyid" / Int16ub,
  "alg" / Int8ub,
  "digestType" / Int8ub,
  "digest" / Byte[32],
)
def len_of_sig(ctx):
    return ctx.dataLength - (ctx._io.tell() - ctx.IOIndexBeforeData)
rrRRSIG = Struct(
  "name" / domain,
  "type" / Int16ub,
  Check(this.type == 0x2e), # 46
  "class" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "IOIndexBeforeData" / Computed(lambda ctx: ctx._io.tell()),
  "typeCov" / Int16ub,
  "alg" / Int8ub,
  "labels" / Int8ub,
  "OrigtimeToLive" / Int32ub,
  "SigExp" / Int32ub,
  "SigInception" / Int32ub,
  "keyTag" / Int16ub,
  "signName" / domain,
  "signature" / Byte[len_of_sig],
)
rrKEY = Struct(
  "name" / domain,
  "type" / Int16ub,
  Check(this.type == 0x30), # 48
  "class" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "flags" / Int16ub,
  "protocol" / Int8ub,
  "algorithm" / Int8ub,
  "key" / Byte[this.dataLength - 4],
)
rrNSEC3 = Struct(
  "name" / domain,
  "type" / Int16ub,
  Check(this.type == 0x32), # 50
  "class" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "alg" / Int8ub,
  "flags" / Int8ub,
  "iterations" / Int16ub,
  "saltLength" / Int8ub,
  "salt" / Byte[this.saltLength],
  "hashLength" / Int8ub,
  "nextHash" / Byte[this.hashLength],
  "typeMap" / map_,
)

resource_record = Select(
  rrA,
  rrNS,
  rrCNAME,
  rrSOA,
  rrPTR,
  rrMX,
  rrTXT,
  rrAAAA,
  rrOPT,
  rrDS,
  rrKEY,
  rrRRSIG,
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
  Terminated,
)
