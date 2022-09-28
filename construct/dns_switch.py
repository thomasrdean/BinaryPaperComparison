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
  "class" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "address" / ipv4Address,
)
rrNS = Struct(
  "class" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "nameServer" / domain,
)
rrCNAME = Struct(
  "class" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "cname" / domain,
)
rrSOA = Struct(
  "class" / Int16ub,
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
rrPTR = Struct(
  "class" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "domainName" / domain,
)
rrMX = Struct(
  "class" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "preference" / Int16ub,
  "mailExchange" / domain,
)
rrTXT = Struct(
  "class" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "text" / Byte[this.dataLength],
)
rrAAAA = Struct(
  "class" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "address" / ipv6Address,
)
rrOPT = Struct(
  "udpPayloadSize" / Int16ub,
  "extendedRCode" / Int8ub,
  "version" / Int8ub,
  "d0_z" / Int16ub,
  "dataLength" / Int16ub,
  "optRecords" / Byte[this.dataLength],
)
rrDS = Struct(
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
  "class" / Int16ub,
  "timeToLive" / Int32ub,
  "dataLength" / Int16ub,
  "flags" / Int16ub,
  "protocol" / Int8ub,
  "algorithm" / Int8ub,
  "key" / Byte[this.dataLength - 4],
)
rrNSEC3 = Struct(
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

resource_record = Struct(
  "name" / domain,
  "type" / Int16ub,
  Switch(this.type, {
    1: rrA,
    2: rrNS,
    5: rrCNAME,
    6: rrSOA,
    12: rrPTR,
    15: rrMX,
    16: rrTXT,
    28: rrAAAA,
    41: rrOPT,
    43: rrDS,
    46: rrRRSIG,
    48: rrKEY,
    50: rrNSEC3,
  })
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
