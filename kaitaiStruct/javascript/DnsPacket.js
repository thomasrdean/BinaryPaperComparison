// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

(function (root, factory) {
  if (typeof define === 'function' && define.amd) {
    define(['kaitai-struct/KaitaiStream'], factory);
  } else if (typeof module === 'object' && module.exports) {
    module.exports = factory(require('kaitai-struct/KaitaiStream'));
  } else {
    root.DnsPacket = factory(root.KaitaiStream);
  }
}(this, function (KaitaiStream) {
var DnsPacket = (function() {
  DnsPacket.RrType = Object.freeze({
    A: 1,
    NS: 2,
    CNAME: 5,
    SOA: 6,
    AAAA: 28,
    OPT: 41,
    DS: 43,
    RRSIG: 46,
    KEY: 48,
    NSEC3: 50,

    1: "A",
    2: "NS",
    5: "CNAME",
    6: "SOA",
    28: "AAAA",
    41: "OPT",
    43: "DS",
    46: "RRSIG",
    48: "KEY",
    50: "NSEC3",
  });

  function DnsPacket(_io, _parent, _root) {
    this._io = _io;
    this._parent = _parent;
    this._root = _root || this;

    this._read();
  }
  DnsPacket.prototype._read = function() {
    this.transactionId = this._io.readU2be();
    this.flags = this._io.readU2be();
    this.qdcount = this._io.readU2be();
    this.ancount = this._io.readU2be();
    this.nscount = this._io.readU2be();
    this.arcount = this._io.readU2be();
    this.queries = new Array(this.qdcount);
    for (var i = 0; i < this.qdcount; i++) {
      this.queries[i] = new Query(this._io, this, this._root);
    }
    this.answers = new Array(this.ancount);
    for (var i = 0; i < this.ancount; i++) {
      this.answers[i] = new ResourceRecord(this._io, this, this._root);
    }
    this.authorities = new Array(this.nscount);
    for (var i = 0; i < this.nscount; i++) {
      this.authorities[i] = new ResourceRecord(this._io, this, this._root);
    }
    this.additionals = new Array(this.arcount);
    for (var i = 0; i < this.arcount; i++) {
      this.additionals[i] = new ResourceRecord(this._io, this, this._root);
    }
  }

  var Map = DnsPacket.Map = (function() {
    function Map(_io, _parent, _root) {
      this._io = _io;
      this._parent = _parent;
      this._root = _root || this;

      this._read();
    }
    Map.prototype._read = function() {
      this.mapNum = this._io.readU1();
      this.length = this._io.readU1();
      this.mapBits = KaitaiStream.bytesToStr(this._io.readBytes(this.length), "utf-8");
    }

    return Map;
  })();

  var ResourceRecord = DnsPacket.ResourceRecord = (function() {
    function ResourceRecord(_io, _parent, _root) {
      this._io = _io;
      this._parent = _parent;
      this._root = _root || this;

      this._read();
    }
    ResourceRecord.prototype._read = function() {
      this.name = new Domain(this._io, this, this._root);
      this.type = this._io.readU2be();
      switch (this.type) {
      case DnsPacket.RrType.A:
        this.body = new RrBodyA(this._io, this, this._root);
        break;
      case DnsPacket.RrType.DS:
        this.body = new RrBodyDs(this._io, this, this._root);
        break;
      case DnsPacket.RrType.NS:
        this.body = new RrBodyNs(this._io, this, this._root);
        break;
      case DnsPacket.RrType.KEY:
        this.body = new RrBodyKey(this._io, this, this._root);
        break;
      case DnsPacket.RrType.CNAME:
        this.body = new RrBodyCname(this._io, this, this._root);
        break;
      case DnsPacket.RrType.OPT:
        this.body = new RrBodyOpt(this._io, this, this._root);
        break;
      case DnsPacket.RrType.RRSIG:
        this.body = new RrBodyRrsig(this._io, this, this._root);
        break;
      case DnsPacket.RrType.NSEC3:
        this.body = new RrBodyNsec3(this._io, this, this._root);
        break;
      case DnsPacket.RrType.AAAA:
        this.body = new RrBodyAaaa(this._io, this, this._root);
        break;
      case DnsPacket.RrType.SOA:
        this.body = new RrBodySoa(this._io, this, this._root);
        break;
      }
    }

    return ResourceRecord;
  })();

  var RrBodyOpt = DnsPacket.RrBodyOpt = (function() {
    function RrBodyOpt(_io, _parent, _root) {
      this._io = _io;
      this._parent = _parent;
      this._root = _root || this;

      this._read();
    }
    RrBodyOpt.prototype._read = function() {
      this.udpPayloadSize = this._io.readU2be();
      this.higherBitsInExtendedRcode = this._io.readU1();
      this.edns0version = this._io.readU1();
      this.z = this._io.readU2be();
      this.dataLength = this._io.readU2be();
    }

    return RrBodyOpt;
  })();

  var RrBodyKey = DnsPacket.RrBodyKey = (function() {
    function RrBodyKey(_io, _parent, _root) {
      this._io = _io;
      this._parent = _parent;
      this._root = _root || this;

      this._read();
    }
    RrBodyKey.prototype._read = function() {
      this.class = this._io.readU2be();
    }

    return RrBodyKey;
  })();

  var Domain = DnsPacket.Domain = (function() {
    function Domain(_io, _parent, _root) {
      this._io = _io;
      this._parent = _parent;
      this._root = _root || this;

      this._read();
    }
    Domain.prototype._read = function() {
      this.name = []
      var i = 0;
      do {
        var _ = new Word(this._io, this, this._root);
        this.name.push(_);
        i++;
      } while (!( ((_.length == 0) || (_.length >= 192)) ));
    }

    return Domain;
  })();

  var Ipv6Address = DnsPacket.Ipv6Address = (function() {
    function Ipv6Address(_io, _parent, _root) {
      this._io = _io;
      this._parent = _parent;
      this._root = _root || this;

      this._read();
    }
    Ipv6Address.prototype._read = function() {
      this.ipV6 = this._io.readBytes(16);
    }

    return Ipv6Address;
  })();

  var Query = DnsPacket.Query = (function() {
    function Query(_io, _parent, _root) {
      this._io = _io;
      this._parent = _parent;
      this._root = _root || this;

      this._read();
    }
    Query.prototype._read = function() {
      this.name = new Domain(this._io, this, this._root);
      this.type = this._io.readU2be();
      this.queryClass = this._io.readU2be();
    }

    return Query;
  })();

  var RrBodyRrsig = DnsPacket.RrBodyRrsig = (function() {
    function RrBodyRrsig(_io, _parent, _root) {
      this._io = _io;
      this._parent = _parent;
      this._root = _root || this;

      this._read();
    }
    RrBodyRrsig.prototype._read = function() {
      this.class = this._io.readU2be();
      this.timeToLive = this._io.readU4be();
      this.dataLength = this._io.readU2be();
      this.typeCov = this._io.readU2be();
      this.alg = this._io.readU1();
      this.labels = this._io.readU1();
      this.origTimeToLive = this._io.readU4be();
      this.sigExp = this._io.readU4be();
      this.sigInception = this._io.readU4be();
      this.keyTag = this._io.readU2be();
      this.signName = new Domain(this._io, this, this._root);
      this.signature = KaitaiStream.bytesToStr(this._io.readBytes(256), "utf-8");
    }

    return RrBodyRrsig;
  })();

  var Ipv4Address = DnsPacket.Ipv4Address = (function() {
    function Ipv4Address(_io, _parent, _root) {
      this._io = _io;
      this._parent = _parent;
      this._root = _root || this;

      this._read();
    }
    Ipv4Address.prototype._read = function() {
      this.ip = this._io.readBytes(4);
    }

    return Ipv4Address;
  })();

  var RrBodyCname = DnsPacket.RrBodyCname = (function() {
    function RrBodyCname(_io, _parent, _root) {
      this._io = _io;
      this._parent = _parent;
      this._root = _root || this;

      this._read();
    }
    RrBodyCname.prototype._read = function() {
      this.class = this._io.readU2be();
      this.timeToLive = this._io.readU4be();
      this.dataLength = this._io.readU2be();
      this.cname = new Domain(this._io, this, this._root);
    }

    return RrBodyCname;
  })();

  var RrBodyAaaa = DnsPacket.RrBodyAaaa = (function() {
    function RrBodyAaaa(_io, _parent, _root) {
      this._io = _io;
      this._parent = _parent;
      this._root = _root || this;

      this._read();
    }
    RrBodyAaaa.prototype._read = function() {
      this.class = this._io.readU2be();
      this.timeToLive = this._io.readU4be();
      this.dataLength = this._io.readU2be();
      this.address = new Ipv6Address(this._io, this, this._root);
    }

    return RrBodyAaaa;
  })();

  var RrBodyNs = DnsPacket.RrBodyNs = (function() {
    function RrBodyNs(_io, _parent, _root) {
      this._io = _io;
      this._parent = _parent;
      this._root = _root || this;

      this._read();
    }
    RrBodyNs.prototype._read = function() {
      this.class = this._io.readU2be();
      this.timeToLive = this._io.readU4be();
      this.dataLength = this._io.readU2be();
      this.nameServer = new Domain(this._io, this, this._root);
    }

    return RrBodyNs;
  })();

  var RrBodyDs = DnsPacket.RrBodyDs = (function() {
    function RrBodyDs(_io, _parent, _root) {
      this._io = _io;
      this._parent = _parent;
      this._root = _root || this;

      this._read();
    }
    RrBodyDs.prototype._read = function() {
      this.class = this._io.readU2be();
      this.timeToLive = this._io.readU4be();
      this.dataLength = this._io.readU2be();
      this.keyid = this._io.readU2be();
      this.alg = this._io.readU1();
      this.digestType = this._io.readU1();
      this.digest = KaitaiStream.bytesToStr(this._io.readBytes(32), "utf-8");
    }

    return RrBodyDs;
  })();

  var RrBodyNsec3 = DnsPacket.RrBodyNsec3 = (function() {
    function RrBodyNsec3(_io, _parent, _root) {
      this._io = _io;
      this._parent = _parent;
      this._root = _root || this;

      this._read();
    }
    RrBodyNsec3.prototype._read = function() {
      this.class = this._io.readU2be();
      this.timeToLive = this._io.readU4be();
      this.dataLength = this._io.readU2be();
      this.alg = this._io.readU1();
      this.flags = this._io.readU1();
      this.iterations = this._io.readU2be();
      this.saltLength = this._io.readU1();
      this.hashLength = this._io.readU1();
      this.nextHash = KaitaiStream.bytesToStr(this._io.readBytes(this.hashLength), "utf-8");
      this.typeMap = new Map(this._io, this, this._root);
    }

    return RrBodyNsec3;
  })();

  var RrBodyA = DnsPacket.RrBodyA = (function() {
    function RrBodyA(_io, _parent, _root) {
      this._io = _io;
      this._parent = _parent;
      this._root = _root || this;

      this._read();
    }
    RrBodyA.prototype._read = function() {
      this.class = this._io.readU2be();
      this.timeToLive = this._io.readU4be();
      this.dataLength = this._io.readU2be();
      this.address = new Ipv4Address(this._io, this, this._root);
    }

    return RrBodyA;
  })();

  var Word = DnsPacket.Word = (function() {
    function Word(_io, _parent, _root) {
      this._io = _io;
      this._parent = _parent;
      this._root = _root || this;

      this._read();
    }
    Word.prototype._read = function() {
      this.length = this._io.readU1();
      if (this.isRef) {
        this.ref = this._io.readU1();
      }
      if (!(this.isRef)) {
        this.letters = KaitaiStream.bytesToStr(this._io.readBytes(this.length), "utf-8");
      }
    }
    Object.defineProperty(Word.prototype, 'isRef', {
      get: function() {
        if (this._m_isRef !== undefined)
          return this._m_isRef;
        this._m_isRef = this.length == 192;
        return this._m_isRef;
      }
    });

    return Word;
  })();

  var RrBodySoa = DnsPacket.RrBodySoa = (function() {
    function RrBodySoa(_io, _parent, _root) {
      this._io = _io;
      this._parent = _parent;
      this._root = _root || this;

      this._read();
    }
    RrBodySoa.prototype._read = function() {
      this.class = this._io.readU2be();
      this.timeToLive = this._io.readU4be();
      this.dataLength = this._io.readU2be();
      this.primaryNameServer = new Domain(this._io, this, this._root);
      this.reponsibleAuthority = new Domain(this._io, this, this._root);
      this.serialNumber = this._io.readU4be();
      this.refreshInterval = this._io.readU4be();
      this.retryInterval = this._io.readU4be();
      this.expireLimit = this._io.readU4be();
      this.minimumTtl = this._io.readU4be();
    }

    return RrBodySoa;
  })();

  return DnsPacket;
})();
return DnsPacket;
}));
