-- This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild
--
-- This file is compatible with Lua 5.3

local class = require("class")
require("kaitaistruct")
local enum = require("enum")
local str_decode = require("string_decode")

DnsPacket = class.class(KaitaiStruct)

DnsPacket.RrType = enum.Enum {
  a = 1,
  ns = 2,
  cname = 5,
  soa = 6,
  aaaa = 28,
  opt = 41,
  ds = 43,
  rrsig = 46,
  key = 48,
  nsec3 = 50,
}

function DnsPacket:_init(io, parent, root)
  KaitaiStruct._init(self, io)
  self._parent = parent
  self._root = root or self
  self:_read()
end

function DnsPacket:_read()
  self.transaction_id = self._io:read_u2be()
  self.flags = self._io:read_u2be()
  self.qdcount = self._io:read_u2be()
  self.ancount = self._io:read_u2be()
  self.nscount = self._io:read_u2be()
  self.arcount = self._io:read_u2be()
  self.queries = {}
  for i = 0, self.qdcount - 1 do
    self.queries[i + 1] = DnsPacket.Query(self._io, self, self._root)
  end
  self.answers = {}
  for i = 0, self.ancount - 1 do
    self.answers[i + 1] = DnsPacket.ResourceRecord(self._io, self, self._root)
  end
  self.authorities = {}
  for i = 0, self.nscount - 1 do
    self.authorities[i + 1] = DnsPacket.ResourceRecord(self._io, self, self._root)
  end
  self.additionals = {}
  for i = 0, self.arcount - 1 do
    self.additionals[i + 1] = DnsPacket.ResourceRecord(self._io, self, self._root)
  end
end


DnsPacket.Map = class.class(KaitaiStruct)

function DnsPacket.Map:_init(io, parent, root)
  KaitaiStruct._init(self, io)
  self._parent = parent
  self._root = root or self
  self:_read()
end

function DnsPacket.Map:_read()
  self.map_num = self._io:read_u1()
  self.length = self._io:read_u1()
  self.map_bits = str_decode.decode(self._io:read_bytes(self.length), "utf-8")
end


DnsPacket.ResourceRecord = class.class(KaitaiStruct)

function DnsPacket.ResourceRecord:_init(io, parent, root)
  KaitaiStruct._init(self, io)
  self._parent = parent
  self._root = root or self
  self:_read()
end

function DnsPacket.ResourceRecord:_read()
  self.name = DnsPacket.Domain(self._io, self, self._root)
  self.type = DnsPacket.RrType(self._io:read_u2be())
  local _on = self.type
  if _on == DnsPacket.RrType.a then
    self.body = DnsPacket.RrBodyA(self._io, self, self._root)
  elseif _on == DnsPacket.RrType.ds then
    self.body = DnsPacket.RrBodyDs(self._io, self, self._root)
  elseif _on == DnsPacket.RrType.ns then
    self.body = DnsPacket.RrBodyNs(self._io, self, self._root)
  elseif _on == DnsPacket.RrType.key then
    self.body = DnsPacket.RrBodyKey(self._io, self, self._root)
  elseif _on == DnsPacket.RrType.cname then
    self.body = DnsPacket.RrBodyCname(self._io, self, self._root)
  elseif _on == DnsPacket.RrType.opt then
    self.body = DnsPacket.RrBodyOpt(self._io, self, self._root)
  elseif _on == DnsPacket.RrType.rrsig then
    self.body = DnsPacket.RrBodyRrsig(self._io, self, self._root)
  elseif _on == DnsPacket.RrType.nsec3 then
    self.body = DnsPacket.RrBodyNsec3(self._io, self, self._root)
  elseif _on == DnsPacket.RrType.aaaa then
    self.body = DnsPacket.RrBodyAaaa(self._io, self, self._root)
  elseif _on == DnsPacket.RrType.soa then
    self.body = DnsPacket.RrBodySoa(self._io, self, self._root)
  end
end


DnsPacket.RrBodyOpt = class.class(KaitaiStruct)

function DnsPacket.RrBodyOpt:_init(io, parent, root)
  KaitaiStruct._init(self, io)
  self._parent = parent
  self._root = root or self
  self:_read()
end

function DnsPacket.RrBodyOpt:_read()
  self.udp_payload_size = self._io:read_u2be()
  self.higher_bits_in_extended_rcode = self._io:read_u1()
  self.edns0version = self._io:read_u1()
  self.z = self._io:read_u2be()
  self.data_length = self._io:read_u2be()
end


DnsPacket.RrBodyKey = class.class(KaitaiStruct)

function DnsPacket.RrBodyKey:_init(io, parent, root)
  KaitaiStruct._init(self, io)
  self._parent = parent
  self._root = root or self
  self:_read()
end

function DnsPacket.RrBodyKey:_read()
  self.class_ = self._io:read_u2be()
end


DnsPacket.Domain = class.class(KaitaiStruct)

function DnsPacket.Domain:_init(io, parent, root)
  KaitaiStruct._init(self, io)
  self._parent = parent
  self._root = root or self
  self:_read()
end

function DnsPacket.Domain:_read()
  self.name = {}
  local i = 0
  while true do
    _ = DnsPacket.Word(self._io, self, self._root)
    self.name[i + 1] = _
    if  ((_.length == 0) or (_.length >= 192))  then
      break
    end
    i = i + 1
  end
end


DnsPacket.Ipv6Address = class.class(KaitaiStruct)

function DnsPacket.Ipv6Address:_init(io, parent, root)
KaitaiStruct._init(self, io)
self._parent = parent
self._root = root or self
self:_read()
end

function DnsPacket.Ipv6Address:_read()
self.ip_v6 = self._io:read_bytes(16)
end


DnsPacket.Query = class.class(KaitaiStruct)

function DnsPacket.Query:_init(io, parent, root)
KaitaiStruct._init(self, io)
self._parent = parent
self._root = root or self
self:_read()
end

function DnsPacket.Query:_read()
self.name = DnsPacket.Domain(self._io, self, self._root)
self.type = DnsPacket.RrType(self._io:read_u2be())
self.query_class = self._io:read_u2be()
end


DnsPacket.RrBodyRrsig = class.class(KaitaiStruct)

function DnsPacket.RrBodyRrsig:_init(io, parent, root)
KaitaiStruct._init(self, io)
self._parent = parent
self._root = root or self
self:_read()
end

function DnsPacket.RrBodyRrsig:_read()
self.class_ = self._io:read_u2be()
self.time_to_live = self._io:read_u4be()
self.data_length = self._io:read_u2be()
self.type_cov = self._io:read_u2be()
self.alg = self._io:read_u1()
self.labels = self._io:read_u1()
self.orig_time_to_live = self._io:read_u4be()
self.sig_exp = self._io:read_u4be()
self.sig_inception = self._io:read_u4be()
self.key_tag = self._io:read_u2be()
self.sign_name = DnsPacket.Domain(self._io, self, self._root)
self.signature = str_decode.decode(self._io:read_bytes(256), "utf-8")
end


DnsPacket.Ipv4Address = class.class(KaitaiStruct)

function DnsPacket.Ipv4Address:_init(io, parent, root)
KaitaiStruct._init(self, io)
self._parent = parent
self._root = root or self
self:_read()
end

function DnsPacket.Ipv4Address:_read()
self.ip = self._io:read_bytes(4)
end


DnsPacket.RrBodyCname = class.class(KaitaiStruct)

function DnsPacket.RrBodyCname:_init(io, parent, root)
KaitaiStruct._init(self, io)
self._parent = parent
self._root = root or self
self:_read()
end

function DnsPacket.RrBodyCname:_read()
self.class_ = self._io:read_u2be()
self.time_to_live = self._io:read_u4be()
self.data_length = self._io:read_u2be()
self.cname = DnsPacket.Domain(self._io, self, self._root)
end


DnsPacket.RrBodyAaaa = class.class(KaitaiStruct)

function DnsPacket.RrBodyAaaa:_init(io, parent, root)
KaitaiStruct._init(self, io)
self._parent = parent
self._root = root or self
self:_read()
end

function DnsPacket.RrBodyAaaa:_read()
self.class_ = self._io:read_u2be()
self.time_to_live = self._io:read_u4be()
self.data_length = self._io:read_u2be()
self.address = DnsPacket.Ipv6Address(self._io, self, self._root)
end


DnsPacket.RrBodyNs = class.class(KaitaiStruct)

function DnsPacket.RrBodyNs:_init(io, parent, root)
KaitaiStruct._init(self, io)
self._parent = parent
self._root = root or self
self:_read()
end

function DnsPacket.RrBodyNs:_read()
self.class_ = self._io:read_u2be()
self.time_to_live = self._io:read_u4be()
self.data_length = self._io:read_u2be()
self.name_server = DnsPacket.Domain(self._io, self, self._root)
end


DnsPacket.RrBodyDs = class.class(KaitaiStruct)

function DnsPacket.RrBodyDs:_init(io, parent, root)
KaitaiStruct._init(self, io)
self._parent = parent
self._root = root or self
self:_read()
end

function DnsPacket.RrBodyDs:_read()
self.class_ = self._io:read_u2be()
self.time_to_live = self._io:read_u4be()
self.data_length = self._io:read_u2be()
self.keyid = self._io:read_u2be()
self.alg = self._io:read_u1()
self.digest_type = self._io:read_u1()
self.digest = str_decode.decode(self._io:read_bytes(32), "utf-8")
end


DnsPacket.RrBodyNsec3 = class.class(KaitaiStruct)

function DnsPacket.RrBodyNsec3:_init(io, parent, root)
KaitaiStruct._init(self, io)
self._parent = parent
self._root = root or self
self:_read()
end

function DnsPacket.RrBodyNsec3:_read()
self.class_ = self._io:read_u2be()
self.time_to_live = self._io:read_u4be()
self.data_length = self._io:read_u2be()
self.alg = self._io:read_u1()
self.flags = self._io:read_u1()
self.iterations = self._io:read_u2be()
self.salt_length = self._io:read_u1()
self.hash_length = self._io:read_u1()
self.next_hash = str_decode.decode(self._io:read_bytes(self.hash_length), "utf-8")
self.type_map = DnsPacket.Map(self._io, self, self._root)
end


DnsPacket.RrBodyA = class.class(KaitaiStruct)

function DnsPacket.RrBodyA:_init(io, parent, root)
KaitaiStruct._init(self, io)
self._parent = parent
self._root = root or self
self:_read()
end

function DnsPacket.RrBodyA:_read()
self.class_ = self._io:read_u2be()
self.time_to_live = self._io:read_u4be()
self.data_length = self._io:read_u2be()
self.address = DnsPacket.Ipv4Address(self._io, self, self._root)
end


DnsPacket.Word = class.class(KaitaiStruct)

function DnsPacket.Word:_init(io, parent, root)
KaitaiStruct._init(self, io)
self._parent = parent
self._root = root or self
self:_read()
end

function DnsPacket.Word:_read()
self.length = self._io:read_u1()
if self.is_ref then
  self.ref = self._io:read_u1()
end
if not(self.is_ref) then
  self.letters = str_decode.decode(self._io:read_bytes(self.length), "utf-8")
end
end

DnsPacket.Word.property.is_ref = {}
function DnsPacket.Word.property.is_ref:get()
if self._m_is_ref ~= nil then
  return self._m_is_ref
end

self._m_is_ref = self.length == 192
return self._m_is_ref
end


DnsPacket.RrBodySoa = class.class(KaitaiStruct)

function DnsPacket.RrBodySoa:_init(io, parent, root)
KaitaiStruct._init(self, io)
self._parent = parent
self._root = root or self
self:_read()
end

function DnsPacket.RrBodySoa:_read()
self.class_ = self._io:read_u2be()
self.time_to_live = self._io:read_u4be()
self.data_length = self._io:read_u2be()
self.primary_name_server = DnsPacket.Domain(self._io, self, self._root)
self.reponsible_authority = DnsPacket.Domain(self._io, self, self._root)
self.serial_number = self._io:read_u4be()
self.refresh_interval = self._io:read_u4be()
self.retry_interval = self._io:read_u4be()
self.expire_limit = self._io:read_u4be()
self.minimum_ttl = self._io:read_u4be()
end


