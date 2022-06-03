// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

using System.Collections.Generic;

namespace Kaitai
{
    public partial class DnsPacket : KaitaiStruct
    {
        public static DnsPacket FromFile(string fileName)
        {
            return new DnsPacket(new KaitaiStream(fileName));
        }


        public enum RrType
        {
            A = 1,
            Ns = 2,
            Cname = 5,
            Soa = 6,
            Aaaa = 28,
            Opt = 41,
            Ds = 43,
            Rrsig = 46,
            Key = 48,
            Nsec3 = 50,
        }
        public DnsPacket(KaitaiStream p__io, KaitaiStruct p__parent = null, DnsPacket p__root = null) : base(p__io)
        {
            m_parent = p__parent;
            m_root = p__root ?? this;
            _read();
        }
        private void _read()
        {
            _transactionId = m_io.ReadU2be();
            _flags = m_io.ReadU2be();
            _qdcount = m_io.ReadU2be();
            _ancount = m_io.ReadU2be();
            _nscount = m_io.ReadU2be();
            _arcount = m_io.ReadU2be();
            _queries = new List<Query>((int) (Qdcount));
            for (var i = 0; i < Qdcount; i++)
            {
                _queries.Add(new Query(m_io, this, m_root));
            }
            _answers = new List<ResourceRecord>((int) (Ancount));
            for (var i = 0; i < Ancount; i++)
            {
                _answers.Add(new ResourceRecord(m_io, this, m_root));
            }
            _authorities = new List<ResourceRecord>((int) (Nscount));
            for (var i = 0; i < Nscount; i++)
            {
                _authorities.Add(new ResourceRecord(m_io, this, m_root));
            }
            _additionals = new List<ResourceRecord>((int) (Arcount));
            for (var i = 0; i < Arcount; i++)
            {
                _additionals.Add(new ResourceRecord(m_io, this, m_root));
            }
        }
        public partial class Map : KaitaiStruct
        {
            public static Map FromFile(string fileName)
            {
                return new Map(new KaitaiStream(fileName));
            }

            public Map(KaitaiStream p__io, DnsPacket.RrBodyNsec3 p__parent = null, DnsPacket p__root = null) : base(p__io)
            {
                m_parent = p__parent;
                m_root = p__root;
                _read();
            }
            private void _read()
            {
                _mapNum = m_io.ReadU1();
                _length = m_io.ReadU1();
                _mapBits = System.Text.Encoding.GetEncoding("utf-8").GetString(m_io.ReadBytes(Length));
            }
            private byte _mapNum;
            private byte _length;
            private string _mapBits;
            private DnsPacket m_root;
            private DnsPacket.RrBodyNsec3 m_parent;
            public byte MapNum { get { return _mapNum; } }
            public byte Length { get { return _length; } }
            public string MapBits { get { return _mapBits; } }
            public DnsPacket M_Root { get { return m_root; } }
            public DnsPacket.RrBodyNsec3 M_Parent { get { return m_parent; } }
        }
        public partial class ResourceRecord : KaitaiStruct
        {
            public static ResourceRecord FromFile(string fileName)
            {
                return new ResourceRecord(new KaitaiStream(fileName));
            }

            public ResourceRecord(KaitaiStream p__io, DnsPacket p__parent = null, DnsPacket p__root = null) : base(p__io)
            {
                m_parent = p__parent;
                m_root = p__root;
                _read();
            }
            private void _read()
            {
                _name = new Domain(m_io, this, m_root);
                _type = ((DnsPacket.RrType) m_io.ReadU2be());
                switch (Type) {
                case DnsPacket.RrType.A: {
                    _body = new RrBodyA(m_io, this, m_root);
                    break;
                }
                case DnsPacket.RrType.Ds: {
                    _body = new RrBodyDs(m_io, this, m_root);
                    break;
                }
                case DnsPacket.RrType.Ns: {
                    _body = new RrBodyNs(m_io, this, m_root);
                    break;
                }
                case DnsPacket.RrType.Key: {
                    _body = new RrBodyKey(m_io, this, m_root);
                    break;
                }
                case DnsPacket.RrType.Cname: {
                    _body = new RrBodyCname(m_io, this, m_root);
                    break;
                }
                case DnsPacket.RrType.Opt: {
                    _body = new RrBodyOpt(m_io, this, m_root);
                    break;
                }
                case DnsPacket.RrType.Rrsig: {
                    _body = new RrBodyRrsig(m_io, this, m_root);
                    break;
                }
                case DnsPacket.RrType.Nsec3: {
                    _body = new RrBodyNsec3(m_io, this, m_root);
                    break;
                }
                case DnsPacket.RrType.Aaaa: {
                    _body = new RrBodyAaaa(m_io, this, m_root);
                    break;
                }
                case DnsPacket.RrType.Soa: {
                    _body = new RrBodySoa(m_io, this, m_root);
                    break;
                }
                }
            }
            private Domain _name;
            private RrType _type;
            private KaitaiStruct _body;
            private DnsPacket m_root;
            private DnsPacket m_parent;
            public Domain Name { get { return _name; } }
            public RrType Type { get { return _type; } }
            public KaitaiStruct Body { get { return _body; } }
            public DnsPacket M_Root { get { return m_root; } }
            public DnsPacket M_Parent { get { return m_parent; } }
        }
        public partial class RrBodyOpt : KaitaiStruct
        {
            public static RrBodyOpt FromFile(string fileName)
            {
                return new RrBodyOpt(new KaitaiStream(fileName));
            }

            public RrBodyOpt(KaitaiStream p__io, DnsPacket.ResourceRecord p__parent = null, DnsPacket p__root = null) : base(p__io)
            {
                m_parent = p__parent;
                m_root = p__root;
                _read();
            }
            private void _read()
            {
                _udpPayloadSize = m_io.ReadU2be();
                _higherBitsInExtendedRcode = m_io.ReadU1();
                _edns0version = m_io.ReadU1();
                _z = m_io.ReadU2be();
                _dataLength = m_io.ReadU2be();
            }
            private ushort _udpPayloadSize;
            private byte _higherBitsInExtendedRcode;
            private byte _edns0version;
            private ushort _z;
            private ushort _dataLength;
            private DnsPacket m_root;
            private DnsPacket.ResourceRecord m_parent;
            public ushort UdpPayloadSize { get { return _udpPayloadSize; } }
            public byte HigherBitsInExtendedRcode { get { return _higherBitsInExtendedRcode; } }
            public byte Edns0version { get { return _edns0version; } }
            public ushort Z { get { return _z; } }
            public ushort DataLength { get { return _dataLength; } }
            public DnsPacket M_Root { get { return m_root; } }
            public DnsPacket.ResourceRecord M_Parent { get { return m_parent; } }
        }
        public partial class RrBodyKey : KaitaiStruct
        {
            public static RrBodyKey FromFile(string fileName)
            {
                return new RrBodyKey(new KaitaiStream(fileName));
            }

            public RrBodyKey(KaitaiStream p__io, DnsPacket.ResourceRecord p__parent = null, DnsPacket p__root = null) : base(p__io)
            {
                m_parent = p__parent;
                m_root = p__root;
                _read();
            }
            private void _read()
            {
                _class = m_io.ReadU2be();
            }
            private ushort _class;
            private DnsPacket m_root;
            private DnsPacket.ResourceRecord m_parent;
            public ushort Class { get { return _class; } }
            public DnsPacket M_Root { get { return m_root; } }
            public DnsPacket.ResourceRecord M_Parent { get { return m_parent; } }
        }
        public partial class Domain : KaitaiStruct
        {
            public static Domain FromFile(string fileName)
            {
                return new Domain(new KaitaiStream(fileName));
            }

            public Domain(KaitaiStream p__io, KaitaiStruct p__parent = null, DnsPacket p__root = null) : base(p__io)
            {
                m_parent = p__parent;
                m_root = p__root;
                _read();
            }
            private void _read()
            {
                _name = new List<Word>();
                {
                    var i = 0;
                    Word M_;
                    do {
                        M_ = new Word(m_io, this, m_root);
                        _name.Add(M_);
                        i++;
                    } while (!( ((M_.Length == 0) || (M_.Length >= 192)) ));
                }
            }
            private List<Word> _name;
            private DnsPacket m_root;
            private KaitaiStruct m_parent;
            public List<Word> Name { get { return _name; } }
            public DnsPacket M_Root { get { return m_root; } }
            public KaitaiStruct M_Parent { get { return m_parent; } }
        }
        public partial class Ipv6Address : KaitaiStruct
        {
            public static Ipv6Address FromFile(string fileName)
            {
                return new Ipv6Address(new KaitaiStream(fileName));
            }

            public Ipv6Address(KaitaiStream p__io, DnsPacket.RrBodyAaaa p__parent = null, DnsPacket p__root = null) : base(p__io)
            {
                m_parent = p__parent;
                m_root = p__root;
                _read();
            }
            private void _read()
            {
                _ipV6 = m_io.ReadBytes(16);
            }
            private byte[] _ipV6;
            private DnsPacket m_root;
            private DnsPacket.RrBodyAaaa m_parent;
            public byte[] IpV6 { get { return _ipV6; } }
            public DnsPacket M_Root { get { return m_root; } }
            public DnsPacket.RrBodyAaaa M_Parent { get { return m_parent; } }
        }
        public partial class Query : KaitaiStruct
        {
            public static Query FromFile(string fileName)
            {
                return new Query(new KaitaiStream(fileName));
            }

            public Query(KaitaiStream p__io, DnsPacket p__parent = null, DnsPacket p__root = null) : base(p__io)
            {
                m_parent = p__parent;
                m_root = p__root;
                _read();
            }
            private void _read()
            {
                _name = new Domain(m_io, this, m_root);
                _type = ((DnsPacket.RrType) m_io.ReadU2be());
                _queryClass = m_io.ReadU2be();
            }
            private Domain _name;
            private RrType _type;
            private ushort _queryClass;
            private DnsPacket m_root;
            private DnsPacket m_parent;
            public Domain Name { get { return _name; } }
            public RrType Type { get { return _type; } }
            public ushort QueryClass { get { return _queryClass; } }
            public DnsPacket M_Root { get { return m_root; } }
            public DnsPacket M_Parent { get { return m_parent; } }
        }
        public partial class RrBodyRrsig : KaitaiStruct
        {
            public static RrBodyRrsig FromFile(string fileName)
            {
                return new RrBodyRrsig(new KaitaiStream(fileName));
            }

            public RrBodyRrsig(KaitaiStream p__io, DnsPacket.ResourceRecord p__parent = null, DnsPacket p__root = null) : base(p__io)
            {
                m_parent = p__parent;
                m_root = p__root;
                _read();
            }
            private void _read()
            {
                _class = m_io.ReadU2be();
                _timeToLive = m_io.ReadU4be();
                _dataLength = m_io.ReadU2be();
                _typeCov = m_io.ReadU2be();
                _alg = m_io.ReadU1();
                _labels = m_io.ReadU1();
                _origTimeToLive = m_io.ReadU4be();
                _sigExp = m_io.ReadU4be();
                _sigInception = m_io.ReadU4be();
                _keyTag = m_io.ReadU2be();
                _signName = new Domain(m_io, this, m_root);
                _signature = System.Text.Encoding.GetEncoding("utf-8").GetString(m_io.ReadBytes(256));
            }
            private ushort _class;
            private uint _timeToLive;
            private ushort _dataLength;
            private ushort _typeCov;
            private byte _alg;
            private byte _labels;
            private uint _origTimeToLive;
            private uint _sigExp;
            private uint _sigInception;
            private ushort _keyTag;
            private Domain _signName;
            private string _signature;
            private DnsPacket m_root;
            private DnsPacket.ResourceRecord m_parent;
            public ushort Class { get { return _class; } }
            public uint TimeToLive { get { return _timeToLive; } }
            public ushort DataLength { get { return _dataLength; } }
            public ushort TypeCov { get { return _typeCov; } }
            public byte Alg { get { return _alg; } }
            public byte Labels { get { return _labels; } }
            public uint OrigTimeToLive { get { return _origTimeToLive; } }
            public uint SigExp { get { return _sigExp; } }
            public uint SigInception { get { return _sigInception; } }
            public ushort KeyTag { get { return _keyTag; } }
            public Domain SignName { get { return _signName; } }
            public string Signature { get { return _signature; } }
            public DnsPacket M_Root { get { return m_root; } }
            public DnsPacket.ResourceRecord M_Parent { get { return m_parent; } }
        }
        public partial class Ipv4Address : KaitaiStruct
        {
            public static Ipv4Address FromFile(string fileName)
            {
                return new Ipv4Address(new KaitaiStream(fileName));
            }

            public Ipv4Address(KaitaiStream p__io, DnsPacket.RrBodyA p__parent = null, DnsPacket p__root = null) : base(p__io)
            {
                m_parent = p__parent;
                m_root = p__root;
                _read();
            }
            private void _read()
            {
                _ip = m_io.ReadBytes(4);
            }
            private byte[] _ip;
            private DnsPacket m_root;
            private DnsPacket.RrBodyA m_parent;
            public byte[] Ip { get { return _ip; } }
            public DnsPacket M_Root { get { return m_root; } }
            public DnsPacket.RrBodyA M_Parent { get { return m_parent; } }
        }
        public partial class RrBodyCname : KaitaiStruct
        {
            public static RrBodyCname FromFile(string fileName)
            {
                return new RrBodyCname(new KaitaiStream(fileName));
            }

            public RrBodyCname(KaitaiStream p__io, DnsPacket.ResourceRecord p__parent = null, DnsPacket p__root = null) : base(p__io)
            {
                m_parent = p__parent;
                m_root = p__root;
                _read();
            }
            private void _read()
            {
                _class = m_io.ReadU2be();
                _timeToLive = m_io.ReadU4be();
                _dataLength = m_io.ReadU2be();
                _cname = new Domain(m_io, this, m_root);
            }
            private ushort _class;
            private uint _timeToLive;
            private ushort _dataLength;
            private Domain _cname;
            private DnsPacket m_root;
            private DnsPacket.ResourceRecord m_parent;
            public ushort Class { get { return _class; } }
            public uint TimeToLive { get { return _timeToLive; } }
            public ushort DataLength { get { return _dataLength; } }
            public Domain Cname { get { return _cname; } }
            public DnsPacket M_Root { get { return m_root; } }
            public DnsPacket.ResourceRecord M_Parent { get { return m_parent; } }
        }
        public partial class RrBodyAaaa : KaitaiStruct
        {
            public static RrBodyAaaa FromFile(string fileName)
            {
                return new RrBodyAaaa(new KaitaiStream(fileName));
            }

            public RrBodyAaaa(KaitaiStream p__io, DnsPacket.ResourceRecord p__parent = null, DnsPacket p__root = null) : base(p__io)
            {
                m_parent = p__parent;
                m_root = p__root;
                _read();
            }
            private void _read()
            {
                _class = m_io.ReadU2be();
                _timeToLive = m_io.ReadU4be();
                _dataLength = m_io.ReadU2be();
                _address = new Ipv6Address(m_io, this, m_root);
            }
            private ushort _class;
            private uint _timeToLive;
            private ushort _dataLength;
            private Ipv6Address _address;
            private DnsPacket m_root;
            private DnsPacket.ResourceRecord m_parent;
            public ushort Class { get { return _class; } }
            public uint TimeToLive { get { return _timeToLive; } }
            public ushort DataLength { get { return _dataLength; } }
            public Ipv6Address Address { get { return _address; } }
            public DnsPacket M_Root { get { return m_root; } }
            public DnsPacket.ResourceRecord M_Parent { get { return m_parent; } }
        }
        public partial class RrBodyNs : KaitaiStruct
        {
            public static RrBodyNs FromFile(string fileName)
            {
                return new RrBodyNs(new KaitaiStream(fileName));
            }

            public RrBodyNs(KaitaiStream p__io, DnsPacket.ResourceRecord p__parent = null, DnsPacket p__root = null) : base(p__io)
            {
                m_parent = p__parent;
                m_root = p__root;
                _read();
            }
            private void _read()
            {
                _class = m_io.ReadU2be();
                _timeToLive = m_io.ReadU4be();
                _dataLength = m_io.ReadU2be();
                _nameServer = new Domain(m_io, this, m_root);
            }
            private ushort _class;
            private uint _timeToLive;
            private ushort _dataLength;
            private Domain _nameServer;
            private DnsPacket m_root;
            private DnsPacket.ResourceRecord m_parent;
            public ushort Class { get { return _class; } }
            public uint TimeToLive { get { return _timeToLive; } }
            public ushort DataLength { get { return _dataLength; } }
            public Domain NameServer { get { return _nameServer; } }
            public DnsPacket M_Root { get { return m_root; } }
            public DnsPacket.ResourceRecord M_Parent { get { return m_parent; } }
        }
        public partial class RrBodyDs : KaitaiStruct
        {
            public static RrBodyDs FromFile(string fileName)
            {
                return new RrBodyDs(new KaitaiStream(fileName));
            }

            public RrBodyDs(KaitaiStream p__io, DnsPacket.ResourceRecord p__parent = null, DnsPacket p__root = null) : base(p__io)
            {
                m_parent = p__parent;
                m_root = p__root;
                _read();
            }
            private void _read()
            {
                _class = m_io.ReadU2be();
                _timeToLive = m_io.ReadU4be();
                _dataLength = m_io.ReadU2be();
                _keyid = m_io.ReadU2be();
                _alg = m_io.ReadU1();
                _digestType = m_io.ReadU1();
                _digest = System.Text.Encoding.GetEncoding("utf-8").GetString(m_io.ReadBytes(32));
            }
            private ushort _class;
            private uint _timeToLive;
            private ushort _dataLength;
            private ushort _keyid;
            private byte _alg;
            private byte _digestType;
            private string _digest;
            private DnsPacket m_root;
            private DnsPacket.ResourceRecord m_parent;
            public ushort Class { get { return _class; } }
            public uint TimeToLive { get { return _timeToLive; } }
            public ushort DataLength { get { return _dataLength; } }
            public ushort Keyid { get { return _keyid; } }
            public byte Alg { get { return _alg; } }
            public byte DigestType { get { return _digestType; } }
            public string Digest { get { return _digest; } }
            public DnsPacket M_Root { get { return m_root; } }
            public DnsPacket.ResourceRecord M_Parent { get { return m_parent; } }
        }
        public partial class RrBodyNsec3 : KaitaiStruct
        {
            public static RrBodyNsec3 FromFile(string fileName)
            {
                return new RrBodyNsec3(new KaitaiStream(fileName));
            }

            public RrBodyNsec3(KaitaiStream p__io, DnsPacket.ResourceRecord p__parent = null, DnsPacket p__root = null) : base(p__io)
            {
                m_parent = p__parent;
                m_root = p__root;
                _read();
            }
            private void _read()
            {
                _class = m_io.ReadU2be();
                _timeToLive = m_io.ReadU4be();
                _dataLength = m_io.ReadU2be();
                _alg = m_io.ReadU1();
                _flags = m_io.ReadU1();
                _iterations = m_io.ReadU2be();
                _saltLength = m_io.ReadU1();
                _hashLength = m_io.ReadU1();
                _nextHash = System.Text.Encoding.GetEncoding("utf-8").GetString(m_io.ReadBytes(HashLength));
                _typeMap = new Map(m_io, this, m_root);
            }
            private ushort _class;
            private uint _timeToLive;
            private ushort _dataLength;
            private byte _alg;
            private byte _flags;
            private ushort _iterations;
            private byte _saltLength;
            private byte _hashLength;
            private string _nextHash;
            private Map _typeMap;
            private DnsPacket m_root;
            private DnsPacket.ResourceRecord m_parent;
            public ushort Class { get { return _class; } }
            public uint TimeToLive { get { return _timeToLive; } }
            public ushort DataLength { get { return _dataLength; } }
            public byte Alg { get { return _alg; } }
            public byte Flags { get { return _flags; } }
            public ushort Iterations { get { return _iterations; } }
            public byte SaltLength { get { return _saltLength; } }
            public byte HashLength { get { return _hashLength; } }
            public string NextHash { get { return _nextHash; } }
            public Map TypeMap { get { return _typeMap; } }
            public DnsPacket M_Root { get { return m_root; } }
            public DnsPacket.ResourceRecord M_Parent { get { return m_parent; } }
        }
        public partial class RrBodyA : KaitaiStruct
        {
            public static RrBodyA FromFile(string fileName)
            {
                return new RrBodyA(new KaitaiStream(fileName));
            }

            public RrBodyA(KaitaiStream p__io, DnsPacket.ResourceRecord p__parent = null, DnsPacket p__root = null) : base(p__io)
            {
                m_parent = p__parent;
                m_root = p__root;
                _read();
            }
            private void _read()
            {
                _class = m_io.ReadU2be();
                _timeToLive = m_io.ReadU4be();
                _dataLength = m_io.ReadU2be();
                _address = new Ipv4Address(m_io, this, m_root);
            }
            private ushort _class;
            private uint _timeToLive;
            private ushort _dataLength;
            private Ipv4Address _address;
            private DnsPacket m_root;
            private DnsPacket.ResourceRecord m_parent;
            public ushort Class { get { return _class; } }
            public uint TimeToLive { get { return _timeToLive; } }
            public ushort DataLength { get { return _dataLength; } }
            public Ipv4Address Address { get { return _address; } }
            public DnsPacket M_Root { get { return m_root; } }
            public DnsPacket.ResourceRecord M_Parent { get { return m_parent; } }
        }
        public partial class Word : KaitaiStruct
        {
            public static Word FromFile(string fileName)
            {
                return new Word(new KaitaiStream(fileName));
            }

            public Word(KaitaiStream p__io, DnsPacket.Domain p__parent = null, DnsPacket p__root = null) : base(p__io)
            {
                m_parent = p__parent;
                m_root = p__root;
                f_isRef = false;
                _read();
            }
            private void _read()
            {
                _length = m_io.ReadU1();
                if (IsRef) {
                    _ref = m_io.ReadU1();
                }
                if (!(IsRef)) {
                    _letters = System.Text.Encoding.GetEncoding("utf-8").GetString(m_io.ReadBytes(Length));
                }
            }
            private bool f_isRef;
            private bool _isRef;
            public bool IsRef
            {
                get
                {
                    if (f_isRef)
                        return _isRef;
                    _isRef = (bool) (Length == 192);
                    f_isRef = true;
                    return _isRef;
                }
            }
            private byte _length;
            private byte? _ref;
            private string _letters;
            private DnsPacket m_root;
            private DnsPacket.Domain m_parent;
            public byte Length { get { return _length; } }
            public byte? Ref { get { return _ref; } }
            public string Letters { get { return _letters; } }
            public DnsPacket M_Root { get { return m_root; } }
            public DnsPacket.Domain M_Parent { get { return m_parent; } }
        }
        public partial class RrBodySoa : KaitaiStruct
        {
            public static RrBodySoa FromFile(string fileName)
            {
                return new RrBodySoa(new KaitaiStream(fileName));
            }

            public RrBodySoa(KaitaiStream p__io, DnsPacket.ResourceRecord p__parent = null, DnsPacket p__root = null) : base(p__io)
            {
                m_parent = p__parent;
                m_root = p__root;
                _read();
            }
            private void _read()
            {
                _class = m_io.ReadU2be();
                _timeToLive = m_io.ReadU4be();
                _dataLength = m_io.ReadU2be();
                _primaryNameServer = new Domain(m_io, this, m_root);
                _reponsibleAuthority = new Domain(m_io, this, m_root);
                _serialNumber = m_io.ReadU4be();
                _refreshInterval = m_io.ReadU4be();
                _retryInterval = m_io.ReadU4be();
                _expireLimit = m_io.ReadU4be();
                _minimumTtl = m_io.ReadU4be();
            }
            private ushort _class;
            private uint _timeToLive;
            private ushort _dataLength;
            private Domain _primaryNameServer;
            private Domain _reponsibleAuthority;
            private uint _serialNumber;
            private uint _refreshInterval;
            private uint _retryInterval;
            private uint _expireLimit;
            private uint _minimumTtl;
            private DnsPacket m_root;
            private DnsPacket.ResourceRecord m_parent;
            public ushort Class { get { return _class; } }
            public uint TimeToLive { get { return _timeToLive; } }
            public ushort DataLength { get { return _dataLength; } }
            public Domain PrimaryNameServer { get { return _primaryNameServer; } }
            public Domain ReponsibleAuthority { get { return _reponsibleAuthority; } }
            public uint SerialNumber { get { return _serialNumber; } }
            public uint RefreshInterval { get { return _refreshInterval; } }
            public uint RetryInterval { get { return _retryInterval; } }
            public uint ExpireLimit { get { return _expireLimit; } }
            public uint MinimumTtl { get { return _minimumTtl; } }
            public DnsPacket M_Root { get { return m_root; } }
            public DnsPacket.ResourceRecord M_Parent { get { return m_parent; } }
        }
        private ushort _transactionId;
        private ushort _flags;
        private ushort _qdcount;
        private ushort _ancount;
        private ushort _nscount;
        private ushort _arcount;
        private List<Query> _queries;
        private List<ResourceRecord> _answers;
        private List<ResourceRecord> _authorities;
        private List<ResourceRecord> _additionals;
        private DnsPacket m_root;
        private KaitaiStruct m_parent;
        public ushort TransactionId { get { return _transactionId; } }
        public ushort Flags { get { return _flags; } }
        public ushort Qdcount { get { return _qdcount; } }
        public ushort Ancount { get { return _ancount; } }
        public ushort Nscount { get { return _nscount; } }
        public ushort Arcount { get { return _arcount; } }
        public List<Query> Queries { get { return _queries; } }
        public List<ResourceRecord> Answers { get { return _answers; } }
        public List<ResourceRecord> Authorities { get { return _authorities; } }
        public List<ResourceRecord> Additionals { get { return _additionals; } }
        public DnsPacket M_Root { get { return m_root; } }
        public KaitaiStruct M_Parent { get { return m_parent; } }
    }
}
