import kaitai_struct_nim_runtime
import options

type
  DnsPacket* = ref object of KaitaiStruct
    `transactionId`*: uint16
    `flags`*: uint16
    `qdcount`*: uint16
    `ancount`*: uint16
    `nscount`*: uint16
    `arcount`*: uint16
    `queries`*: seq[DnsPacket_Query]
    `answers`*: seq[DnsPacket_ResourceRecord]
    `authorities`*: seq[DnsPacket_ResourceRecord]
    `additionals`*: seq[DnsPacket_ResourceRecord]
    `parent`*: KaitaiStruct
  DnsPacket_RrType* = enum
    a = 1
    ns = 2
    cname = 5
    soa = 6
    aaaa = 28
    opt = 41
    ds = 43
    rrsig = 46
    key = 48
    nsec3 = 50
  DnsPacket_Map* = ref object of KaitaiStruct
    `mapNum`*: uint8
    `length`*: uint8
    `mapBits`*: string
    `parent`*: DnsPacket_RrBodyNsec3
  DnsPacket_ResourceRecord* = ref object of KaitaiStruct
    `name`*: DnsPacket_Domain
    `type`*: DnsPacket_RrType
    `body`*: KaitaiStruct
    `parent`*: DnsPacket
  DnsPacket_RrBodyOpt* = ref object of KaitaiStruct
    `udpPayloadSize`*: uint16
    `higherBitsInExtendedRcode`*: uint8
    `edns0version`*: uint8
    `z`*: uint16
    `dataLength`*: uint16
    `parent`*: DnsPacket_ResourceRecord
  DnsPacket_RrBodyKey* = ref object of KaitaiStruct
    `class`*: uint16
    `parent`*: DnsPacket_ResourceRecord
  DnsPacket_Domain* = ref object of KaitaiStruct
    `name`*: seq[DnsPacket_Word]
    `parent`*: KaitaiStruct
  DnsPacket_Ipv6Address* = ref object of KaitaiStruct
    `ipV6`*: seq[byte]
    `parent`*: DnsPacket_RrBodyAaaa
  DnsPacket_Query* = ref object of KaitaiStruct
    `name`*: DnsPacket_Domain
    `type`*: DnsPacket_RrType
    `queryClass`*: uint16
    `parent`*: DnsPacket
  DnsPacket_RrBodyRrsig* = ref object of KaitaiStruct
    `class`*: uint16
    `timeToLive`*: uint32
    `dataLength`*: uint16
    `typeCov`*: uint16
    `alg`*: uint8
    `labels`*: uint8
    `origTimeToLive`*: uint32
    `sigExp`*: uint32
    `sigInception`*: uint32
    `keyTag`*: uint16
    `signName`*: DnsPacket_Domain
    `signature`*: string
    `parent`*: DnsPacket_ResourceRecord
  DnsPacket_Ipv4Address* = ref object of KaitaiStruct
    `ip`*: seq[byte]
    `parent`*: DnsPacket_RrBodyA
  DnsPacket_RrBodyCname* = ref object of KaitaiStruct
    `class`*: uint16
    `timeToLive`*: uint32
    `dataLength`*: uint16
    `cname`*: DnsPacket_Domain
    `parent`*: DnsPacket_ResourceRecord
  DnsPacket_RrBodyAaaa* = ref object of KaitaiStruct
    `class`*: uint16
    `timeToLive`*: uint32
    `dataLength`*: uint16
    `address`*: DnsPacket_Ipv6Address
    `parent`*: DnsPacket_ResourceRecord
  DnsPacket_RrBodyNs* = ref object of KaitaiStruct
    `class`*: uint16
    `timeToLive`*: uint32
    `dataLength`*: uint16
    `nameServer`*: DnsPacket_Domain
    `parent`*: DnsPacket_ResourceRecord
  DnsPacket_RrBodyDs* = ref object of KaitaiStruct
    `class`*: uint16
    `timeToLive`*: uint32
    `dataLength`*: uint16
    `keyid`*: uint16
    `alg`*: uint8
    `digestType`*: uint8
    `digest`*: string
    `parent`*: DnsPacket_ResourceRecord
  DnsPacket_RrBodyNsec3* = ref object of KaitaiStruct
    `class`*: uint16
    `timeToLive`*: uint32
    `dataLength`*: uint16
    `alg`*: uint8
    `flags`*: uint8
    `iterations`*: uint16
    `saltLength`*: uint8
    `hashLength`*: uint8
    `nextHash`*: string
    `typeMap`*: DnsPacket_Map
    `parent`*: DnsPacket_ResourceRecord
  DnsPacket_RrBodyA* = ref object of KaitaiStruct
    `class`*: uint16
    `timeToLive`*: uint32
    `dataLength`*: uint16
    `address`*: DnsPacket_Ipv4Address
    `parent`*: DnsPacket_ResourceRecord
  DnsPacket_Word* = ref object of KaitaiStruct
    `length`*: uint8
    `ref`*: uint8
    `letters`*: string
    `parent`*: DnsPacket_Domain
    `isRefInst`*: bool
  DnsPacket_RrBodySoa* = ref object of KaitaiStruct
    `class`*: uint16
    `timeToLive`*: uint32
    `dataLength`*: uint16
    `primaryNameServer`*: DnsPacket_Domain
    `reponsibleAuthority`*: DnsPacket_Domain
    `serialNumber`*: uint32
    `refreshInterval`*: uint32
    `retryInterval`*: uint32
    `expireLimit`*: uint32
    `minimumTtl`*: uint32
    `parent`*: DnsPacket_ResourceRecord

proc read*(_: typedesc[DnsPacket], io: KaitaiStream, root: KaitaiStruct, parent: KaitaiStruct): DnsPacket
proc read*(_: typedesc[DnsPacket_Map], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket_RrBodyNsec3): DnsPacket_Map
proc read*(_: typedesc[DnsPacket_ResourceRecord], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket): DnsPacket_ResourceRecord
proc read*(_: typedesc[DnsPacket_RrBodyOpt], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket_ResourceRecord): DnsPacket_RrBodyOpt
proc read*(_: typedesc[DnsPacket_RrBodyKey], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket_ResourceRecord): DnsPacket_RrBodyKey
proc read*(_: typedesc[DnsPacket_Domain], io: KaitaiStream, root: KaitaiStruct, parent: KaitaiStruct): DnsPacket_Domain
proc read*(_: typedesc[DnsPacket_Ipv6Address], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket_RrBodyAaaa): DnsPacket_Ipv6Address
proc read*(_: typedesc[DnsPacket_Query], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket): DnsPacket_Query
proc read*(_: typedesc[DnsPacket_RrBodyRrsig], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket_ResourceRecord): DnsPacket_RrBodyRrsig
proc read*(_: typedesc[DnsPacket_Ipv4Address], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket_RrBodyA): DnsPacket_Ipv4Address
proc read*(_: typedesc[DnsPacket_RrBodyCname], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket_ResourceRecord): DnsPacket_RrBodyCname
proc read*(_: typedesc[DnsPacket_RrBodyAaaa], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket_ResourceRecord): DnsPacket_RrBodyAaaa
proc read*(_: typedesc[DnsPacket_RrBodyNs], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket_ResourceRecord): DnsPacket_RrBodyNs
proc read*(_: typedesc[DnsPacket_RrBodyDs], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket_ResourceRecord): DnsPacket_RrBodyDs
proc read*(_: typedesc[DnsPacket_RrBodyNsec3], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket_ResourceRecord): DnsPacket_RrBodyNsec3
proc read*(_: typedesc[DnsPacket_RrBodyA], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket_ResourceRecord): DnsPacket_RrBodyA
proc read*(_: typedesc[DnsPacket_Word], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket_Domain): DnsPacket_Word
proc read*(_: typedesc[DnsPacket_RrBodySoa], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket_ResourceRecord): DnsPacket_RrBodySoa

proc isRef*(this: DnsPacket_Word): bool

proc read*(_: typedesc[DnsPacket], io: KaitaiStream, root: KaitaiStruct, parent: KaitaiStruct): DnsPacket =
  template this: untyped = result
  this = new(DnsPacket)
  let root = if root == nil: cast[DnsPacket](this) else: cast[DnsPacket](root)
  this.io = io
  this.root = root
  this.parent = parent

  let transactionIdExpr = this.io.readU2be()
  this.transactionId = transactionIdExpr
  let flagsExpr = this.io.readU2be()
  this.flags = flagsExpr
  let qdcountExpr = this.io.readU2be()
  this.qdcount = qdcountExpr
  let ancountExpr = this.io.readU2be()
  this.ancount = ancountExpr
  let nscountExpr = this.io.readU2be()
  this.nscount = nscountExpr
  let arcountExpr = this.io.readU2be()
  this.arcount = arcountExpr
  for i in 0 ..< int(this.qdcount):
    let it = DnsPacket_Query.read(this.io, this.root, this)
    this.queries.add(it)
  for i in 0 ..< int(this.ancount):
    let it = DnsPacket_ResourceRecord.read(this.io, this.root, this)
    this.answers.add(it)
  for i in 0 ..< int(this.nscount):
    let it = DnsPacket_ResourceRecord.read(this.io, this.root, this)
    this.authorities.add(it)
  for i in 0 ..< int(this.arcount):
    let it = DnsPacket_ResourceRecord.read(this.io, this.root, this)
    this.additionals.add(it)

proc fromFile*(_: typedesc[DnsPacket], filename: string): DnsPacket =
  DnsPacket.read(newKaitaiFileStream(filename), nil, nil)

proc read*(_: typedesc[DnsPacket_Map], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket_RrBodyNsec3): DnsPacket_Map =
  template this: untyped = result
  this = new(DnsPacket_Map)
  let root = if root == nil: cast[DnsPacket](this) else: cast[DnsPacket](root)
  this.io = io
  this.root = root
  this.parent = parent

  let mapNumExpr = this.io.readU1()
  this.mapNum = mapNumExpr
  let lengthExpr = this.io.readU1()
  this.length = lengthExpr
  let mapBitsExpr = encode(this.io.readBytes(int(this.length)), "utf-8")
  this.mapBits = mapBitsExpr

proc fromFile*(_: typedesc[DnsPacket_Map], filename: string): DnsPacket_Map =
  DnsPacket_Map.read(newKaitaiFileStream(filename), nil, nil)

proc read*(_: typedesc[DnsPacket_ResourceRecord], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket): DnsPacket_ResourceRecord =
  template this: untyped = result
  this = new(DnsPacket_ResourceRecord)
  let root = if root == nil: cast[DnsPacket](this) else: cast[DnsPacket](root)
  this.io = io
  this.root = root
  this.parent = parent

  let nameExpr = DnsPacket_Domain.read(this.io, this.root, this)
  this.name = nameExpr
  let typeExpr = DnsPacket_RrType(this.io.readU2be())
  this.type = typeExpr
  block:
    let on = this.type
    if on == dns_packet.a:
      let bodyExpr = DnsPacket_RrBodyA.read(this.io, this.root, this)
      this.body = bodyExpr
    elif on == dns_packet.ds:
      let bodyExpr = DnsPacket_RrBodyDs.read(this.io, this.root, this)
      this.body = bodyExpr
    elif on == dns_packet.ns:
      let bodyExpr = DnsPacket_RrBodyNs.read(this.io, this.root, this)
      this.body = bodyExpr
    elif on == dns_packet.key:
      let bodyExpr = DnsPacket_RrBodyKey.read(this.io, this.root, this)
      this.body = bodyExpr
    elif on == dns_packet.cname:
      let bodyExpr = DnsPacket_RrBodyCname.read(this.io, this.root, this)
      this.body = bodyExpr
    elif on == dns_packet.opt:
      let bodyExpr = DnsPacket_RrBodyOpt.read(this.io, this.root, this)
      this.body = bodyExpr
    elif on == dns_packet.rrsig:
      let bodyExpr = DnsPacket_RrBodyRrsig.read(this.io, this.root, this)
      this.body = bodyExpr
    elif on == dns_packet.nsec3:
      let bodyExpr = DnsPacket_RrBodyNsec3.read(this.io, this.root, this)
      this.body = bodyExpr
    elif on == dns_packet.aaaa:
      let bodyExpr = DnsPacket_RrBodyAaaa.read(this.io, this.root, this)
      this.body = bodyExpr
    elif on == dns_packet.soa:
      let bodyExpr = DnsPacket_RrBodySoa.read(this.io, this.root, this)
      this.body = bodyExpr

proc fromFile*(_: typedesc[DnsPacket_ResourceRecord], filename: string): DnsPacket_ResourceRecord =
  DnsPacket_ResourceRecord.read(newKaitaiFileStream(filename), nil, nil)

proc read*(_: typedesc[DnsPacket_RrBodyOpt], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket_ResourceRecord): DnsPacket_RrBodyOpt =
  template this: untyped = result
  this = new(DnsPacket_RrBodyOpt)
  let root = if root == nil: cast[DnsPacket](this) else: cast[DnsPacket](root)
  this.io = io
  this.root = root
  this.parent = parent

  let udpPayloadSizeExpr = this.io.readU2be()
  this.udpPayloadSize = udpPayloadSizeExpr
  let higherBitsInExtendedRcodeExpr = this.io.readU1()
  this.higherBitsInExtendedRcode = higherBitsInExtendedRcodeExpr
  let edns0versionExpr = this.io.readU1()
  this.edns0version = edns0versionExpr
  let zExpr = this.io.readU2be()
  this.z = zExpr
  let dataLengthExpr = this.io.readU2be()
  this.dataLength = dataLengthExpr

proc fromFile*(_: typedesc[DnsPacket_RrBodyOpt], filename: string): DnsPacket_RrBodyOpt =
  DnsPacket_RrBodyOpt.read(newKaitaiFileStream(filename), nil, nil)

proc read*(_: typedesc[DnsPacket_RrBodyKey], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket_ResourceRecord): DnsPacket_RrBodyKey =
  template this: untyped = result
  this = new(DnsPacket_RrBodyKey)
  let root = if root == nil: cast[DnsPacket](this) else: cast[DnsPacket](root)
  this.io = io
  this.root = root
  this.parent = parent

  let classExpr = this.io.readU2be()
  this.class = classExpr

proc fromFile*(_: typedesc[DnsPacket_RrBodyKey], filename: string): DnsPacket_RrBodyKey =
  DnsPacket_RrBodyKey.read(newKaitaiFileStream(filename), nil, nil)

proc read*(_: typedesc[DnsPacket_Domain], io: KaitaiStream, root: KaitaiStruct, parent: KaitaiStruct): DnsPacket_Domain =
  template this: untyped = result
  this = new(DnsPacket_Domain)
  let root = if root == nil: cast[DnsPacket](this) else: cast[DnsPacket](root)
  this.io = io
  this.root = root
  this.parent = parent

  block:
    var i: int
    while true:
      let it = DnsPacket_Word.read(this.io, this.root, this)
      this.name.add(it)
      if  ((it.length == 0) or (it.length >= 192)) :
        break
      inc i

proc fromFile*(_: typedesc[DnsPacket_Domain], filename: string): DnsPacket_Domain =
  DnsPacket_Domain.read(newKaitaiFileStream(filename), nil, nil)

proc read*(_: typedesc[DnsPacket_Ipv6Address], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket_RrBodyAaaa): DnsPacket_Ipv6Address =
  template this: untyped = result
  this = new(DnsPacket_Ipv6Address)
  let root = if root == nil: cast[DnsPacket](this) else: cast[DnsPacket](root)
  this.io = io
  this.root = root
  this.parent = parent

  let ipV6Expr = this.io.readBytes(int(16))
  this.ipV6 = ipV6Expr

proc fromFile*(_: typedesc[DnsPacket_Ipv6Address], filename: string): DnsPacket_Ipv6Address =
  DnsPacket_Ipv6Address.read(newKaitaiFileStream(filename), nil, nil)

proc read*(_: typedesc[DnsPacket_Query], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket): DnsPacket_Query =
  template this: untyped = result
  this = new(DnsPacket_Query)
  let root = if root == nil: cast[DnsPacket](this) else: cast[DnsPacket](root)
  this.io = io
  this.root = root
  this.parent = parent

  let nameExpr = DnsPacket_Domain.read(this.io, this.root, this)
  this.name = nameExpr
  let typeExpr = DnsPacket_RrType(this.io.readU2be())
  this.type = typeExpr
  let queryClassExpr = this.io.readU2be()
  this.queryClass = queryClassExpr

proc fromFile*(_: typedesc[DnsPacket_Query], filename: string): DnsPacket_Query =
  DnsPacket_Query.read(newKaitaiFileStream(filename), nil, nil)

proc read*(_: typedesc[DnsPacket_RrBodyRrsig], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket_ResourceRecord): DnsPacket_RrBodyRrsig =
  template this: untyped = result
  this = new(DnsPacket_RrBodyRrsig)
  let root = if root == nil: cast[DnsPacket](this) else: cast[DnsPacket](root)
  this.io = io
  this.root = root
  this.parent = parent

  let classExpr = this.io.readU2be()
  this.class = classExpr
  let timeToLiveExpr = this.io.readU4be()
  this.timeToLive = timeToLiveExpr
  let dataLengthExpr = this.io.readU2be()
  this.dataLength = dataLengthExpr
  let typeCovExpr = this.io.readU2be()
  this.typeCov = typeCovExpr
  let algExpr = this.io.readU1()
  this.alg = algExpr
  let labelsExpr = this.io.readU1()
  this.labels = labelsExpr
  let origTimeToLiveExpr = this.io.readU4be()
  this.origTimeToLive = origTimeToLiveExpr
  let sigExpExpr = this.io.readU4be()
  this.sigExp = sigExpExpr
  let sigInceptionExpr = this.io.readU4be()
  this.sigInception = sigInceptionExpr
  let keyTagExpr = this.io.readU2be()
  this.keyTag = keyTagExpr
  let signNameExpr = DnsPacket_Domain.read(this.io, this.root, this)
  this.signName = signNameExpr
  let signatureExpr = encode(this.io.readBytes(int(256)), "utf-8")
  this.signature = signatureExpr

proc fromFile*(_: typedesc[DnsPacket_RrBodyRrsig], filename: string): DnsPacket_RrBodyRrsig =
  DnsPacket_RrBodyRrsig.read(newKaitaiFileStream(filename), nil, nil)

proc read*(_: typedesc[DnsPacket_Ipv4Address], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket_RrBodyA): DnsPacket_Ipv4Address =
  template this: untyped = result
  this = new(DnsPacket_Ipv4Address)
  let root = if root == nil: cast[DnsPacket](this) else: cast[DnsPacket](root)
  this.io = io
  this.root = root
  this.parent = parent

  let ipExpr = this.io.readBytes(int(4))
  this.ip = ipExpr

proc fromFile*(_: typedesc[DnsPacket_Ipv4Address], filename: string): DnsPacket_Ipv4Address =
  DnsPacket_Ipv4Address.read(newKaitaiFileStream(filename), nil, nil)

proc read*(_: typedesc[DnsPacket_RrBodyCname], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket_ResourceRecord): DnsPacket_RrBodyCname =
  template this: untyped = result
  this = new(DnsPacket_RrBodyCname)
  let root = if root == nil: cast[DnsPacket](this) else: cast[DnsPacket](root)
  this.io = io
  this.root = root
  this.parent = parent

  let classExpr = this.io.readU2be()
  this.class = classExpr
  let timeToLiveExpr = this.io.readU4be()
  this.timeToLive = timeToLiveExpr
  let dataLengthExpr = this.io.readU2be()
  this.dataLength = dataLengthExpr
  let cnameExpr = DnsPacket_Domain.read(this.io, this.root, this)
  this.cname = cnameExpr

proc fromFile*(_: typedesc[DnsPacket_RrBodyCname], filename: string): DnsPacket_RrBodyCname =
  DnsPacket_RrBodyCname.read(newKaitaiFileStream(filename), nil, nil)

proc read*(_: typedesc[DnsPacket_RrBodyAaaa], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket_ResourceRecord): DnsPacket_RrBodyAaaa =
  template this: untyped = result
  this = new(DnsPacket_RrBodyAaaa)
  let root = if root == nil: cast[DnsPacket](this) else: cast[DnsPacket](root)
  this.io = io
  this.root = root
  this.parent = parent

  let classExpr = this.io.readU2be()
  this.class = classExpr
  let timeToLiveExpr = this.io.readU4be()
  this.timeToLive = timeToLiveExpr
  let dataLengthExpr = this.io.readU2be()
  this.dataLength = dataLengthExpr
  let addressExpr = DnsPacket_Ipv6Address.read(this.io, this.root, this)
  this.address = addressExpr

proc fromFile*(_: typedesc[DnsPacket_RrBodyAaaa], filename: string): DnsPacket_RrBodyAaaa =
  DnsPacket_RrBodyAaaa.read(newKaitaiFileStream(filename), nil, nil)

proc read*(_: typedesc[DnsPacket_RrBodyNs], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket_ResourceRecord): DnsPacket_RrBodyNs =
  template this: untyped = result
  this = new(DnsPacket_RrBodyNs)
  let root = if root == nil: cast[DnsPacket](this) else: cast[DnsPacket](root)
  this.io = io
  this.root = root
  this.parent = parent

  let classExpr = this.io.readU2be()
  this.class = classExpr
  let timeToLiveExpr = this.io.readU4be()
  this.timeToLive = timeToLiveExpr
  let dataLengthExpr = this.io.readU2be()
  this.dataLength = dataLengthExpr
  let nameServerExpr = DnsPacket_Domain.read(this.io, this.root, this)
  this.nameServer = nameServerExpr

proc fromFile*(_: typedesc[DnsPacket_RrBodyNs], filename: string): DnsPacket_RrBodyNs =
  DnsPacket_RrBodyNs.read(newKaitaiFileStream(filename), nil, nil)

proc read*(_: typedesc[DnsPacket_RrBodyDs], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket_ResourceRecord): DnsPacket_RrBodyDs =
  template this: untyped = result
  this = new(DnsPacket_RrBodyDs)
  let root = if root == nil: cast[DnsPacket](this) else: cast[DnsPacket](root)
  this.io = io
  this.root = root
  this.parent = parent

  let classExpr = this.io.readU2be()
  this.class = classExpr
  let timeToLiveExpr = this.io.readU4be()
  this.timeToLive = timeToLiveExpr
  let dataLengthExpr = this.io.readU2be()
  this.dataLength = dataLengthExpr
  let keyidExpr = this.io.readU2be()
  this.keyid = keyidExpr
  let algExpr = this.io.readU1()
  this.alg = algExpr
  let digestTypeExpr = this.io.readU1()
  this.digestType = digestTypeExpr
  let digestExpr = encode(this.io.readBytes(int(32)), "utf-8")
  this.digest = digestExpr

proc fromFile*(_: typedesc[DnsPacket_RrBodyDs], filename: string): DnsPacket_RrBodyDs =
  DnsPacket_RrBodyDs.read(newKaitaiFileStream(filename), nil, nil)

proc read*(_: typedesc[DnsPacket_RrBodyNsec3], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket_ResourceRecord): DnsPacket_RrBodyNsec3 =
  template this: untyped = result
  this = new(DnsPacket_RrBodyNsec3)
  let root = if root == nil: cast[DnsPacket](this) else: cast[DnsPacket](root)
  this.io = io
  this.root = root
  this.parent = parent

  let classExpr = this.io.readU2be()
  this.class = classExpr
  let timeToLiveExpr = this.io.readU4be()
  this.timeToLive = timeToLiveExpr
  let dataLengthExpr = this.io.readU2be()
  this.dataLength = dataLengthExpr
  let algExpr = this.io.readU1()
  this.alg = algExpr
  let flagsExpr = this.io.readU1()
  this.flags = flagsExpr
  let iterationsExpr = this.io.readU2be()
  this.iterations = iterationsExpr
  let saltLengthExpr = this.io.readU1()
  this.saltLength = saltLengthExpr
  let hashLengthExpr = this.io.readU1()
  this.hashLength = hashLengthExpr
  let nextHashExpr = encode(this.io.readBytes(int(this.hashLength)), "utf-8")
  this.nextHash = nextHashExpr
  let typeMapExpr = DnsPacket_Map.read(this.io, this.root, this)
  this.typeMap = typeMapExpr

proc fromFile*(_: typedesc[DnsPacket_RrBodyNsec3], filename: string): DnsPacket_RrBodyNsec3 =
  DnsPacket_RrBodyNsec3.read(newKaitaiFileStream(filename), nil, nil)

proc read*(_: typedesc[DnsPacket_RrBodyA], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket_ResourceRecord): DnsPacket_RrBodyA =
  template this: untyped = result
  this = new(DnsPacket_RrBodyA)
  let root = if root == nil: cast[DnsPacket](this) else: cast[DnsPacket](root)
  this.io = io
  this.root = root
  this.parent = parent

  let classExpr = this.io.readU2be()
  this.class = classExpr
  let timeToLiveExpr = this.io.readU4be()
  this.timeToLive = timeToLiveExpr
  let dataLengthExpr = this.io.readU2be()
  this.dataLength = dataLengthExpr
  let addressExpr = DnsPacket_Ipv4Address.read(this.io, this.root, this)
  this.address = addressExpr

proc fromFile*(_: typedesc[DnsPacket_RrBodyA], filename: string): DnsPacket_RrBodyA =
  DnsPacket_RrBodyA.read(newKaitaiFileStream(filename), nil, nil)

proc read*(_: typedesc[DnsPacket_Word], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket_Domain): DnsPacket_Word =
  template this: untyped = result
  this = new(DnsPacket_Word)
  let root = if root == nil: cast[DnsPacket](this) else: cast[DnsPacket](root)
  this.io = io
  this.root = root
  this.parent = parent

  let lengthExpr = this.io.readU1()
  this.length = lengthExpr
  if this.isRef:
    let refExpr = this.io.readU1()
    this.ref = refExpr
  if not(this.isRef):
    let lettersExpr = encode(this.io.readBytes(int(this.length)), "utf-8")
    this.letters = lettersExpr

proc isRef(this: DnsPacket_Word): bool = 
  if this.isRefInst != nil:
    return this.isRefInst
  let isRefInstExpr = bool(this.length == 192)
  this.isRefInst = isRefInstExpr
  if this.isRefInst != nil:
    return this.isRefInst

proc fromFile*(_: typedesc[DnsPacket_Word], filename: string): DnsPacket_Word =
  DnsPacket_Word.read(newKaitaiFileStream(filename), nil, nil)

proc read*(_: typedesc[DnsPacket_RrBodySoa], io: KaitaiStream, root: KaitaiStruct, parent: DnsPacket_ResourceRecord): DnsPacket_RrBodySoa =
  template this: untyped = result
  this = new(DnsPacket_RrBodySoa)
  let root = if root == nil: cast[DnsPacket](this) else: cast[DnsPacket](root)
  this.io = io
  this.root = root
  this.parent = parent

  let classExpr = this.io.readU2be()
  this.class = classExpr
  let timeToLiveExpr = this.io.readU4be()
  this.timeToLive = timeToLiveExpr
  let dataLengthExpr = this.io.readU2be()
  this.dataLength = dataLengthExpr
  let primaryNameServerExpr = DnsPacket_Domain.read(this.io, this.root, this)
  this.primaryNameServer = primaryNameServerExpr
  let reponsibleAuthorityExpr = DnsPacket_Domain.read(this.io, this.root, this)
  this.reponsibleAuthority = reponsibleAuthorityExpr
  let serialNumberExpr = this.io.readU4be()
  this.serialNumber = serialNumberExpr
  let refreshIntervalExpr = this.io.readU4be()
  this.refreshInterval = refreshIntervalExpr
  let retryIntervalExpr = this.io.readU4be()
  this.retryInterval = retryIntervalExpr
  let expireLimitExpr = this.io.readU4be()
  this.expireLimit = expireLimitExpr
  let minimumTtlExpr = this.io.readU4be()
  this.minimumTtl = minimumTtlExpr

proc fromFile*(_: typedesc[DnsPacket_RrBodySoa], filename: string): DnsPacket_RrBodySoa =
  DnsPacket_RrBodySoa.read(newKaitaiFileStream(filename), nil, nil)

