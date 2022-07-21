# This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

from pkg_resources import parse_version
import kaitaistruct
from kaitaistruct import KaitaiStruct, KaitaiStream, BytesIO
from enum import Enum


if parse_version(kaitaistruct.__version__) < parse_version('0.9'):
    raise Exception("Incompatible Kaitai Struct Python API: 0.9 or later is required, but you have %s" % (kaitaistruct.__version__))

class DnsPacket(KaitaiStruct):

    class RrType(Enum):
        a = 1
        ns = 2
        cname = 5
        soa = 6
        ptr = 12
        mx = 15
        txt = 16
        aaaa = 28
        opt = 41
        ds = 43
        rrsig = 46
        key = 48
        nsec3 = 50
    def __init__(self, _io, _parent=None, _root=None):
        self._io = _io
        self._parent = _parent
        self._root = _root if _root else self
        self._read()

    def _read(self):
        self.transaction_id = self._io.read_u2be()
        self.flags = self._io.read_u2be()
        self.qdcount = self._io.read_u2be()
        self.ancount = self._io.read_u2be()
        self.nscount = self._io.read_u2be()
        self.arcount = self._io.read_u2be()
        self.queries = [None] * (self.qdcount)
        for i in range(self.qdcount):
            self.queries[i] = DnsPacket.Query(self._io, self, self._root)

        self.answers = [None] * (self.ancount)
        for i in range(self.ancount):
            self.answers[i] = DnsPacket.ResourceRecord(self._io, self, self._root)

        self.authorities = [None] * (self.nscount)
        for i in range(self.nscount):
            self.authorities[i] = DnsPacket.ResourceRecord(self._io, self, self._root)

        self.additionals = [None] * (self.arcount)
        for i in range(self.arcount):
            self.additionals[i] = DnsPacket.ResourceRecord(self._io, self, self._root)

        if not (self._io.is_eof()):
            self.extra_bytes = DnsPacket.Fail(self._io, self, self._root)


    class Map(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.map_num = self._io.read_u1()
            self.length = self._io.read_u1()
            self.map_bits = self._io.read_bytes(self.length)


    class RrBodyTxt(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.class_ = self._io.read_u2be()
            self.time_to_live = self._io.read_u4be()
            self.data_length = self._io.read_u2be()
            self.text = (self._io.read_bytes(self.data_length)).decode(u"utf-8")


    class Fail(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.eat_bytes = self._io.read_bytes_full()
            self.fail_to_eat_another = self._io.read_bytes(1)


    class ResourceRecord(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.name = DnsPacket.Domain(self._io, self, self._root)
            self.type = KaitaiStream.resolve_enum(DnsPacket.RrType, self._io.read_u2be())
            _on = self.type
            if _on == DnsPacket.RrType.a:
                self.body = DnsPacket.RrBodyA(self._io, self, self._root)
            elif _on == DnsPacket.RrType.ds:
                self.body = DnsPacket.RrBodyDs(self._io, self, self._root)
            elif _on == DnsPacket.RrType.ns:
                self.body = DnsPacket.RrBodyNs(self._io, self, self._root)
            elif _on == DnsPacket.RrType.key:
                self.body = DnsPacket.RrBodyKey(self._io, self, self._root)
            elif _on == DnsPacket.RrType.txt:
                self.body = DnsPacket.RrBodyTxt(self._io, self, self._root)
            elif _on == DnsPacket.RrType.cname:
                self.body = DnsPacket.RrBodyCname(self._io, self, self._root)
            elif _on == DnsPacket.RrType.opt:
                self.body = DnsPacket.RrBodyOpt(self._io, self, self._root)
            elif _on == DnsPacket.RrType.rrsig:
                self.body = DnsPacket.RrBodyRrsig(self._io, self, self._root)
            elif _on == DnsPacket.RrType.ptr:
                self.body = DnsPacket.RrBodyPtr(self._io, self, self._root)
            elif _on == DnsPacket.RrType.mx:
                self.body = DnsPacket.RrBodyMx(self._io, self, self._root)
            elif _on == DnsPacket.RrType.nsec3:
                self.body = DnsPacket.RrBodyNsec3(self._io, self, self._root)
            elif _on == DnsPacket.RrType.aaaa:
                self.body = DnsPacket.RrBodyAaaa(self._io, self, self._root)
            elif _on == DnsPacket.RrType.soa:
                self.body = DnsPacket.RrBodySoa(self._io, self, self._root)
            else:
                self.body = DnsPacket.Unknown(self._io, self, self._root)


    class RrBodyMx(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.class_ = self._io.read_u2be()
            self.time_to_live = self._io.read_u4be()
            self.data_length = self._io.read_u2be()
            self.preference = self._io.read_u2be()
            self.mail_exchange = DnsPacket.Domain(self._io, self, self._root)


    class RrBodyOpt(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.udp_payload_size = self._io.read_u2be()
            self.extended_r_code = self._io.read_u1()
            self.version = self._io.read_u1()
            self.d0_z = self._io.read_u2be()
            self.data_length = self._io.read_u2be()
            self.opt_records = self._io.read_bytes(self.data_length)


    class RrBodyKey(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.class_ = self._io.read_u2be()
            self.time_to_live = self._io.read_u4be()
            self.data_length = self._io.read_u2be()
            self.flags = self._io.read_u2be()
            self.protocol = self._io.read_u1()
            self.algorithm = self._io.read_u1()
            self.key = self._io.read_bytes((self.data_length - 4))


    class Domain(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.name = []
            i = 0
            while True:
                _ = DnsPacket.Word(self._io, self, self._root)
                self.name.append(_)
                if  ((_.length == 0) or (_.length >= 192)) :
                    break
                i += 1


    class Ipv6Address(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.ip_v6 = self._io.read_bytes(16)


    class Query(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.name = DnsPacket.Domain(self._io, self, self._root)
            self.type = KaitaiStream.resolve_enum(DnsPacket.RrType, self._io.read_u2be())
            self.query_class = self._io.read_u2be()


    class Unknown(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.class_ = self._io.read_u2be()
            self.time_to_live = self._io.read_u4be()
            self.data_length = self._io.read_u2be()
            self.data = self._io.read_bytes(self.data_length)


    class RrBodyRrsig(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.class_ = self._io.read_u2be()
            self.time_to_live = self._io.read_u4be()
            self.data_length = self._io.read_u2be()
            self.data = self._io.read_bytes(self.data_length)


    class Ipv4Address(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.ip = self._io.read_bytes(4)


    class RrBodyCname(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.class_ = self._io.read_u2be()
            self.time_to_live = self._io.read_u4be()
            self.data_length = self._io.read_u2be()
            self.cname = DnsPacket.Domain(self._io, self, self._root)


    class RrBodyAaaa(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.class_ = self._io.read_u2be()
            self.time_to_live = self._io.read_u4be()
            self.data_length = self._io.read_u2be()
            self.address = DnsPacket.Ipv6Address(self._io, self, self._root)


    class RrBodyNs(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.class_ = self._io.read_u2be()
            self.time_to_live = self._io.read_u4be()
            self.data_length = self._io.read_u2be()
            self.name_server = DnsPacket.Domain(self._io, self, self._root)


    class RrBodyDs(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.class_ = self._io.read_u2be()
            self.time_to_live = self._io.read_u4be()
            self.data_length = self._io.read_u2be()
            self.keyid = self._io.read_u2be()
            self.alg = self._io.read_u1()
            self.digest_type = self._io.read_u1()
            self.digest = self._io.read_bytes(32)


    class RrBodyNsec3(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.class_ = self._io.read_u2be()
            self.time_to_live = self._io.read_u4be()
            self.data_length = self._io.read_u2be()
            self.alg = self._io.read_u1()
            self.flags = self._io.read_u1()
            self.iterations = self._io.read_u2be()
            self.salt_length = self._io.read_u1()
            self.hash_length = self._io.read_u1()
            self.next_hash = self._io.read_bytes(self.hash_length)
            self.type_map = DnsPacket.Map(self._io, self, self._root)


    class RrBodyPtr(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.class_ = self._io.read_u2be()
            self.time_to_live = self._io.read_u4be()
            self.data_length = self._io.read_u2be()
            self.domain_name = DnsPacket.Domain(self._io, self, self._root)


    class RrBodyA(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.class_ = self._io.read_u2be()
            self.time_to_live = self._io.read_u4be()
            self.data_length = self._io.read_u2be()
            self.address = DnsPacket.Ipv4Address(self._io, self, self._root)


    class Word(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.length = self._io.read_u1()
            if self.is_ref:
                self.ref = self._io.read_u1()

            if not (self.is_ref):
                self.letters = (self._io.read_bytes(self.length)).decode(u"utf-8")


        @property
        def is_ref(self):
            if hasattr(self, '_m_is_ref'):
                return self._m_is_ref if hasattr(self, '_m_is_ref') else None

            self._m_is_ref = self.length >= 192
            return self._m_is_ref if hasattr(self, '_m_is_ref') else None


    class RrBodySoa(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.class_ = self._io.read_u2be()
            self.time_to_live = self._io.read_u4be()
            self.data_length = self._io.read_u2be()
            self.primary_name_server = DnsPacket.Domain(self._io, self, self._root)
            self.reponsible_authority = DnsPacket.Domain(self._io, self, self._root)
            self.serial_number = self._io.read_u4be()
            self.refresh_interval = self._io.read_u4be()
            self.retry_interval = self._io.read_u4be()
            self.expire_limit = self._io.read_u4be()
            self.minimum_ttl = self._io.read_u4be()



