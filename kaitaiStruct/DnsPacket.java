// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

import io.kaitai.struct.ByteBufferKaitaiStream;
import io.kaitai.struct.KaitaiStruct;
import io.kaitai.struct.KaitaiStream;
import java.io.IOException;
import java.util.Map;
import java.util.HashMap;
import java.util.ArrayList;
import java.nio.charset.Charset;

public class DnsPacket extends KaitaiStruct {
    public static DnsPacket fromFile(String fileName) throws IOException {
        return new DnsPacket(new ByteBufferKaitaiStream(fileName));
    }

    public enum RrType {
        A(1),
        NS(2),
        CNAME(5),
        SOA(6),
        AAAA(28),
        OPT(41),
        DS(43),
        RRSIG(46),
        KEY(48),
        NSEC3(50);

        private final long id;
        RrType(long id) { this.id = id; }
        public long id() { return id; }
        private static final Map<Long, RrType> byId = new HashMap<Long, RrType>(10);
        static {
            for (RrType e : RrType.values())
                byId.put(e.id(), e);
        }
        public static RrType byId(long id) { return byId.get(id); }
    }

    public DnsPacket(KaitaiStream _io) {
        this(_io, null, null);
    }

    public DnsPacket(KaitaiStream _io, KaitaiStruct _parent) {
        this(_io, _parent, null);
    }

    public DnsPacket(KaitaiStream _io, KaitaiStruct _parent, DnsPacket _root) {
        super(_io);
        this._parent = _parent;
        this._root = _root == null ? this : _root;
        _read();
    }
    private void _read() {
        this.transactionId = this._io.readU2be();
        this.flags = this._io.readU2be();
        this.qdcount = this._io.readU2be();
        this.ancount = this._io.readU2be();
        this.nscount = this._io.readU2be();
        this.arcount = this._io.readU2be();
        queries = new ArrayList<Query>(((Number) (qdcount())).intValue());
        for (int i = 0; i < qdcount(); i++) {
            this.queries.add(new Query(this._io, this, _root));
        }
        answers = new ArrayList<ResourceRecord>(((Number) (ancount())).intValue());
        for (int i = 0; i < ancount(); i++) {
            this.answers.add(new ResourceRecord(this._io, this, _root));
        }
        authorities = new ArrayList<ResourceRecord>(((Number) (nscount())).intValue());
        for (int i = 0; i < nscount(); i++) {
            this.authorities.add(new ResourceRecord(this._io, this, _root));
        }
        additionals = new ArrayList<ResourceRecord>(((Number) (arcount())).intValue());
        for (int i = 0; i < arcount(); i++) {
            this.additionals.add(new ResourceRecord(this._io, this, _root));
        }
    }
    public static class Map extends KaitaiStruct {
        public static Map fromFile(String fileName) throws IOException {
            return new Map(new ByteBufferKaitaiStream(fileName));
        }

        public Map(KaitaiStream _io) {
            this(_io, null, null);
        }

        public Map(KaitaiStream _io, DnsPacket.RrBodyNsec3 _parent) {
            this(_io, _parent, null);
        }

        public Map(KaitaiStream _io, DnsPacket.RrBodyNsec3 _parent, DnsPacket _root) {
            super(_io);
            this._parent = _parent;
            this._root = _root;
            _read();
        }
        private void _read() {
            this.mapNum = this._io.readU1();
            this.length = this._io.readU1();
            this.mapBits = new String(this._io.readBytes(length()), Charset.forName("utf-8"));
        }
        private int mapNum;
        private int length;
        private String mapBits;
        private DnsPacket _root;
        private DnsPacket.RrBodyNsec3 _parent;
        public int mapNum() { return mapNum; }
        public int length() { return length; }
        public String mapBits() { return mapBits; }
        public DnsPacket _root() { return _root; }
        public DnsPacket.RrBodyNsec3 _parent() { return _parent; }
    }
    public static class ResourceRecord extends KaitaiStruct {
        public static ResourceRecord fromFile(String fileName) throws IOException {
            return new ResourceRecord(new ByteBufferKaitaiStream(fileName));
        }

        public ResourceRecord(KaitaiStream _io) {
            this(_io, null, null);
        }

        public ResourceRecord(KaitaiStream _io, DnsPacket _parent) {
            this(_io, _parent, null);
        }

        public ResourceRecord(KaitaiStream _io, DnsPacket _parent, DnsPacket _root) {
            super(_io);
            this._parent = _parent;
            this._root = _root;
            _read();
        }
        private void _read() {
            this.name = new Domain(this._io, this, _root);
            this.type = DnsPacket.RrType.byId(this._io.readU2be());
            {
                RrType on = type();
                if (on != null) {
                    switch (type()) {
                    case A: {
                        this.body = new RrBodyA(this._io, this, _root);
                        break;
                    }
                    case DS: {
                        this.body = new RrBodyDs(this._io, this, _root);
                        break;
                    }
                    case NS: {
                        this.body = new RrBodyNs(this._io, this, _root);
                        break;
                    }
                    case KEY: {
                        this.body = new RrBodyKey(this._io, this, _root);
                        break;
                    }
                    case CNAME: {
                        this.body = new RrBodyCname(this._io, this, _root);
                        break;
                    }
                    case OPT: {
                        this.body = new RrBodyOpt(this._io, this, _root);
                        break;
                    }
                    case RRSIG: {
                        this.body = new RrBodyRrsig(this._io, this, _root);
                        break;
                    }
                    case NSEC3: {
                        this.body = new RrBodyNsec3(this._io, this, _root);
                        break;
                    }
                    case AAAA: {
                        this.body = new RrBodyAaaa(this._io, this, _root);
                        break;
                    }
                    case SOA: {
                        this.body = new RrBodySoa(this._io, this, _root);
                        break;
                    }
                    }
                }
            }
        }
        private Domain name;
        private RrType type;
        private KaitaiStruct body;
        private DnsPacket _root;
        private DnsPacket _parent;
        public Domain name() { return name; }
        public RrType type() { return type; }
        public KaitaiStruct body() { return body; }
        public DnsPacket _root() { return _root; }
        public DnsPacket _parent() { return _parent; }
    }
    public static class RrBodyOpt extends KaitaiStruct {
        public static RrBodyOpt fromFile(String fileName) throws IOException {
            return new RrBodyOpt(new ByteBufferKaitaiStream(fileName));
        }

        public RrBodyOpt(KaitaiStream _io) {
            this(_io, null, null);
        }

        public RrBodyOpt(KaitaiStream _io, DnsPacket.ResourceRecord _parent) {
            this(_io, _parent, null);
        }

        public RrBodyOpt(KaitaiStream _io, DnsPacket.ResourceRecord _parent, DnsPacket _root) {
            super(_io);
            this._parent = _parent;
            this._root = _root;
            _read();
        }
        private void _read() {
            this.udpPayloadSize = this._io.readU2be();
            this.higherBitsInExtendedRcode = this._io.readU1();
            this.edns0version = this._io.readU1();
            this.z = this._io.readU2be();
            this.dataLength = this._io.readU2be();
        }
        private int udpPayloadSize;
        private int higherBitsInExtendedRcode;
        private int edns0version;
        private int z;
        private int dataLength;
        private DnsPacket _root;
        private DnsPacket.ResourceRecord _parent;
        public int udpPayloadSize() { return udpPayloadSize; }
        public int higherBitsInExtendedRcode() { return higherBitsInExtendedRcode; }
        public int edns0version() { return edns0version; }
        public int z() { return z; }
        public int dataLength() { return dataLength; }
        public DnsPacket _root() { return _root; }
        public DnsPacket.ResourceRecord _parent() { return _parent; }
    }
    public static class RrBodyKey extends KaitaiStruct {
        public static RrBodyKey fromFile(String fileName) throws IOException {
            return new RrBodyKey(new ByteBufferKaitaiStream(fileName));
        }

        public RrBodyKey(KaitaiStream _io) {
            this(_io, null, null);
        }

        public RrBodyKey(KaitaiStream _io, DnsPacket.ResourceRecord _parent) {
            this(_io, _parent, null);
        }

        public RrBodyKey(KaitaiStream _io, DnsPacket.ResourceRecord _parent, DnsPacket _root) {
            super(_io);
            this._parent = _parent;
            this._root = _root;
            _read();
        }
        private void _read() {
            this.class = this._io.readU2be();
        }
        private int class;
        private DnsPacket _root;
        private DnsPacket.ResourceRecord _parent;
        public int class() { return class; }
        public DnsPacket _root() { return _root; }
        public DnsPacket.ResourceRecord _parent() { return _parent; }
    }
    public static class Domain extends KaitaiStruct {
        public static Domain fromFile(String fileName) throws IOException {
            return new Domain(new ByteBufferKaitaiStream(fileName));
        }

        public Domain(KaitaiStream _io) {
            this(_io, null, null);
        }

        public Domain(KaitaiStream _io, KaitaiStruct _parent) {
            this(_io, _parent, null);
        }

        public Domain(KaitaiStream _io, KaitaiStruct _parent, DnsPacket _root) {
            super(_io);
            this._parent = _parent;
            this._root = _root;
            _read();
        }
        private void _read() {
            this.name = new ArrayList<Word>();
            {
                Word _it;
                int i = 0;
                do {
                    _it = new Word(this._io, this, _root);
                    this.name.add(_it);
                    i++;
                } while (!( ((_it.length() == 0) || (_it.length() >= 192)) ));
            }
        }
        private ArrayList<Word> name;
        private DnsPacket _root;
        private KaitaiStruct _parent;
        public ArrayList<Word> name() { return name; }
        public DnsPacket _root() { return _root; }
        public KaitaiStruct _parent() { return _parent; }
    }
    public static class Ipv6Address extends KaitaiStruct {
        public static Ipv6Address fromFile(String fileName) throws IOException {
            return new Ipv6Address(new ByteBufferKaitaiStream(fileName));
        }

        public Ipv6Address(KaitaiStream _io) {
            this(_io, null, null);
        }

        public Ipv6Address(KaitaiStream _io, DnsPacket.RrBodyAaaa _parent) {
            this(_io, _parent, null);
        }

        public Ipv6Address(KaitaiStream _io, DnsPacket.RrBodyAaaa _parent, DnsPacket _root) {
            super(_io);
            this._parent = _parent;
            this._root = _root;
            _read();
        }
        private void _read() {
            this.ipV6 = this._io.readBytes(16);
        }
        private byte[] ipV6;
        private DnsPacket _root;
        private DnsPacket.RrBodyAaaa _parent;
        public byte[] ipV6() { return ipV6; }
        public DnsPacket _root() { return _root; }
        public DnsPacket.RrBodyAaaa _parent() { return _parent; }
    }
    public static class Query extends KaitaiStruct {
        public static Query fromFile(String fileName) throws IOException {
            return new Query(new ByteBufferKaitaiStream(fileName));
        }

        public Query(KaitaiStream _io) {
            this(_io, null, null);
        }

        public Query(KaitaiStream _io, DnsPacket _parent) {
            this(_io, _parent, null);
        }

        public Query(KaitaiStream _io, DnsPacket _parent, DnsPacket _root) {
            super(_io);
            this._parent = _parent;
            this._root = _root;
            _read();
        }
        private void _read() {
            this.name = new Domain(this._io, this, _root);
            this.type = DnsPacket.RrType.byId(this._io.readU2be());
            this.queryClass = this._io.readU2be();
        }
        private Domain name;
        private RrType type;
        private int queryClass;
        private DnsPacket _root;
        private DnsPacket _parent;
        public Domain name() { return name; }
        public RrType type() { return type; }
        public int queryClass() { return queryClass; }
        public DnsPacket _root() { return _root; }
        public DnsPacket _parent() { return _parent; }
    }
    public static class RrBodyRrsig extends KaitaiStruct {
        public static RrBodyRrsig fromFile(String fileName) throws IOException {
            return new RrBodyRrsig(new ByteBufferKaitaiStream(fileName));
        }

        public RrBodyRrsig(KaitaiStream _io) {
            this(_io, null, null);
        }

        public RrBodyRrsig(KaitaiStream _io, DnsPacket.ResourceRecord _parent) {
            this(_io, _parent, null);
        }

        public RrBodyRrsig(KaitaiStream _io, DnsPacket.ResourceRecord _parent, DnsPacket _root) {
            super(_io);
            this._parent = _parent;
            this._root = _root;
            _read();
        }
        private void _read() {
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
            this.signName = new Domain(this._io, this, _root);
            this.signature = new String(this._io.readBytes(256), Charset.forName("utf-8"));
        }
        private int class;
        private long timeToLive;
        private int dataLength;
        private int typeCov;
        private int alg;
        private int labels;
        private long origTimeToLive;
        private long sigExp;
        private long sigInception;
        private int keyTag;
        private Domain signName;
        private String signature;
        private DnsPacket _root;
        private DnsPacket.ResourceRecord _parent;
        public int class() { return class; }
        public long timeToLive() { return timeToLive; }
        public int dataLength() { return dataLength; }
        public int typeCov() { return typeCov; }
        public int alg() { return alg; }
        public int labels() { return labels; }
        public long origTimeToLive() { return origTimeToLive; }
        public long sigExp() { return sigExp; }
        public long sigInception() { return sigInception; }
        public int keyTag() { return keyTag; }
        public Domain signName() { return signName; }
        public String signature() { return signature; }
        public DnsPacket _root() { return _root; }
        public DnsPacket.ResourceRecord _parent() { return _parent; }
    }
    public static class Ipv4Address extends KaitaiStruct {
        public static Ipv4Address fromFile(String fileName) throws IOException {
            return new Ipv4Address(new ByteBufferKaitaiStream(fileName));
        }

        public Ipv4Address(KaitaiStream _io) {
            this(_io, null, null);
        }

        public Ipv4Address(KaitaiStream _io, DnsPacket.RrBodyA _parent) {
            this(_io, _parent, null);
        }

        public Ipv4Address(KaitaiStream _io, DnsPacket.RrBodyA _parent, DnsPacket _root) {
            super(_io);
            this._parent = _parent;
            this._root = _root;
            _read();
        }
        private void _read() {
            this.ip = this._io.readBytes(4);
        }
        private byte[] ip;
        private DnsPacket _root;
        private DnsPacket.RrBodyA _parent;
        public byte[] ip() { return ip; }
        public DnsPacket _root() { return _root; }
        public DnsPacket.RrBodyA _parent() { return _parent; }
    }
    public static class RrBodyCname extends KaitaiStruct {
        public static RrBodyCname fromFile(String fileName) throws IOException {
            return new RrBodyCname(new ByteBufferKaitaiStream(fileName));
        }

        public RrBodyCname(KaitaiStream _io) {
            this(_io, null, null);
        }

        public RrBodyCname(KaitaiStream _io, DnsPacket.ResourceRecord _parent) {
            this(_io, _parent, null);
        }

        public RrBodyCname(KaitaiStream _io, DnsPacket.ResourceRecord _parent, DnsPacket _root) {
            super(_io);
            this._parent = _parent;
            this._root = _root;
            _read();
        }
        private void _read() {
            this.class = this._io.readU2be();
            this.timeToLive = this._io.readU4be();
            this.dataLength = this._io.readU2be();
            this.cname = new Domain(this._io, this, _root);
        }
        private int class;
        private long timeToLive;
        private int dataLength;
        private Domain cname;
        private DnsPacket _root;
        private DnsPacket.ResourceRecord _parent;
        public int class() { return class; }
        public long timeToLive() { return timeToLive; }
        public int dataLength() { return dataLength; }
        public Domain cname() { return cname; }
        public DnsPacket _root() { return _root; }
        public DnsPacket.ResourceRecord _parent() { return _parent; }
    }
    public static class RrBodyAaaa extends KaitaiStruct {
        public static RrBodyAaaa fromFile(String fileName) throws IOException {
            return new RrBodyAaaa(new ByteBufferKaitaiStream(fileName));
        }

        public RrBodyAaaa(KaitaiStream _io) {
            this(_io, null, null);
        }

        public RrBodyAaaa(KaitaiStream _io, DnsPacket.ResourceRecord _parent) {
            this(_io, _parent, null);
        }

        public RrBodyAaaa(KaitaiStream _io, DnsPacket.ResourceRecord _parent, DnsPacket _root) {
            super(_io);
            this._parent = _parent;
            this._root = _root;
            _read();
        }
        private void _read() {
            this.class = this._io.readU2be();
            this.timeToLive = this._io.readU4be();
            this.dataLength = this._io.readU2be();
            this.address = new Ipv6Address(this._io, this, _root);
        }
        private int class;
        private long timeToLive;
        private int dataLength;
        private Ipv6Address address;
        private DnsPacket _root;
        private DnsPacket.ResourceRecord _parent;
        public int class() { return class; }
        public long timeToLive() { return timeToLive; }
        public int dataLength() { return dataLength; }
        public Ipv6Address address() { return address; }
        public DnsPacket _root() { return _root; }
        public DnsPacket.ResourceRecord _parent() { return _parent; }
    }
    public static class RrBodyNs extends KaitaiStruct {
        public static RrBodyNs fromFile(String fileName) throws IOException {
            return new RrBodyNs(new ByteBufferKaitaiStream(fileName));
        }

        public RrBodyNs(KaitaiStream _io) {
            this(_io, null, null);
        }

        public RrBodyNs(KaitaiStream _io, DnsPacket.ResourceRecord _parent) {
            this(_io, _parent, null);
        }

        public RrBodyNs(KaitaiStream _io, DnsPacket.ResourceRecord _parent, DnsPacket _root) {
            super(_io);
            this._parent = _parent;
            this._root = _root;
            _read();
        }
        private void _read() {
            this.class = this._io.readU2be();
            this.timeToLive = this._io.readU4be();
            this.dataLength = this._io.readU2be();
            this.nameServer = new Domain(this._io, this, _root);
        }
        private int class;
        private long timeToLive;
        private int dataLength;
        private Domain nameServer;
        private DnsPacket _root;
        private DnsPacket.ResourceRecord _parent;
        public int class() { return class; }
        public long timeToLive() { return timeToLive; }
        public int dataLength() { return dataLength; }
        public Domain nameServer() { return nameServer; }
        public DnsPacket _root() { return _root; }
        public DnsPacket.ResourceRecord _parent() { return _parent; }
    }
    public static class RrBodyDs extends KaitaiStruct {
        public static RrBodyDs fromFile(String fileName) throws IOException {
            return new RrBodyDs(new ByteBufferKaitaiStream(fileName));
        }

        public RrBodyDs(KaitaiStream _io) {
            this(_io, null, null);
        }

        public RrBodyDs(KaitaiStream _io, DnsPacket.ResourceRecord _parent) {
            this(_io, _parent, null);
        }

        public RrBodyDs(KaitaiStream _io, DnsPacket.ResourceRecord _parent, DnsPacket _root) {
            super(_io);
            this._parent = _parent;
            this._root = _root;
            _read();
        }
        private void _read() {
            this.class = this._io.readU2be();
            this.timeToLive = this._io.readU4be();
            this.dataLength = this._io.readU2be();
            this.keyid = this._io.readU2be();
            this.alg = this._io.readU1();
            this.digestType = this._io.readU1();
            this.digest = new String(this._io.readBytes(32), Charset.forName("utf-8"));
        }
        private int class;
        private long timeToLive;
        private int dataLength;
        private int keyid;
        private int alg;
        private int digestType;
        private String digest;
        private DnsPacket _root;
        private DnsPacket.ResourceRecord _parent;
        public int class() { return class; }
        public long timeToLive() { return timeToLive; }
        public int dataLength() { return dataLength; }
        public int keyid() { return keyid; }
        public int alg() { return alg; }
        public int digestType() { return digestType; }
        public String digest() { return digest; }
        public DnsPacket _root() { return _root; }
        public DnsPacket.ResourceRecord _parent() { return _parent; }
    }
    public static class RrBodyNsec3 extends KaitaiStruct {
        public static RrBodyNsec3 fromFile(String fileName) throws IOException {
            return new RrBodyNsec3(new ByteBufferKaitaiStream(fileName));
        }

        public RrBodyNsec3(KaitaiStream _io) {
            this(_io, null, null);
        }

        public RrBodyNsec3(KaitaiStream _io, DnsPacket.ResourceRecord _parent) {
            this(_io, _parent, null);
        }

        public RrBodyNsec3(KaitaiStream _io, DnsPacket.ResourceRecord _parent, DnsPacket _root) {
            super(_io);
            this._parent = _parent;
            this._root = _root;
            _read();
        }
        private void _read() {
            this.class = this._io.readU2be();
            this.timeToLive = this._io.readU4be();
            this.dataLength = this._io.readU2be();
            this.alg = this._io.readU1();
            this.flags = this._io.readU1();
            this.iterations = this._io.readU2be();
            this.saltLength = this._io.readU1();
            this.hashLength = this._io.readU1();
            this.nextHash = new String(this._io.readBytes(hashLength()), Charset.forName("utf-8"));
            this.typeMap = new Map(this._io, this, _root);
        }
        private int class;
        private long timeToLive;
        private int dataLength;
        private int alg;
        private int flags;
        private int iterations;
        private int saltLength;
        private int hashLength;
        private String nextHash;
        private Map typeMap;
        private DnsPacket _root;
        private DnsPacket.ResourceRecord _parent;
        public int class() { return class; }
        public long timeToLive() { return timeToLive; }
        public int dataLength() { return dataLength; }
        public int alg() { return alg; }
        public int flags() { return flags; }
        public int iterations() { return iterations; }
        public int saltLength() { return saltLength; }
        public int hashLength() { return hashLength; }
        public String nextHash() { return nextHash; }
        public Map typeMap() { return typeMap; }
        public DnsPacket _root() { return _root; }
        public DnsPacket.ResourceRecord _parent() { return _parent; }
    }
    public static class RrBodyA extends KaitaiStruct {
        public static RrBodyA fromFile(String fileName) throws IOException {
            return new RrBodyA(new ByteBufferKaitaiStream(fileName));
        }

        public RrBodyA(KaitaiStream _io) {
            this(_io, null, null);
        }

        public RrBodyA(KaitaiStream _io, DnsPacket.ResourceRecord _parent) {
            this(_io, _parent, null);
        }

        public RrBodyA(KaitaiStream _io, DnsPacket.ResourceRecord _parent, DnsPacket _root) {
            super(_io);
            this._parent = _parent;
            this._root = _root;
            _read();
        }
        private void _read() {
            this.class = this._io.readU2be();
            this.timeToLive = this._io.readU4be();
            this.dataLength = this._io.readU2be();
            this.address = new Ipv4Address(this._io, this, _root);
        }
        private int class;
        private long timeToLive;
        private int dataLength;
        private Ipv4Address address;
        private DnsPacket _root;
        private DnsPacket.ResourceRecord _parent;
        public int class() { return class; }
        public long timeToLive() { return timeToLive; }
        public int dataLength() { return dataLength; }
        public Ipv4Address address() { return address; }
        public DnsPacket _root() { return _root; }
        public DnsPacket.ResourceRecord _parent() { return _parent; }
    }
    public static class Word extends KaitaiStruct {
        public static Word fromFile(String fileName) throws IOException {
            return new Word(new ByteBufferKaitaiStream(fileName));
        }

        public Word(KaitaiStream _io) {
            this(_io, null, null);
        }

        public Word(KaitaiStream _io, DnsPacket.Domain _parent) {
            this(_io, _parent, null);
        }

        public Word(KaitaiStream _io, DnsPacket.Domain _parent, DnsPacket _root) {
            super(_io);
            this._parent = _parent;
            this._root = _root;
            _read();
        }
        private void _read() {
            this.length = this._io.readU1();
            if (isRef()) {
                this.ref = this._io.readU1();
            }
            if (!(isRef())) {
                this.letters = new String(this._io.readBytes(length()), Charset.forName("utf-8"));
            }
        }
        private Boolean isRef;
        public Boolean isRef() {
            if (this.isRef != null)
                return this.isRef;
            boolean _tmp = (boolean) (length() == 192);
            this.isRef = _tmp;
            return this.isRef;
        }
        private int length;
        private Integer ref;
        private String letters;
        private DnsPacket _root;
        private DnsPacket.Domain _parent;
        public int length() { return length; }
        public Integer ref() { return ref; }
        public String letters() { return letters; }
        public DnsPacket _root() { return _root; }
        public DnsPacket.Domain _parent() { return _parent; }
    }
    public static class RrBodySoa extends KaitaiStruct {
        public static RrBodySoa fromFile(String fileName) throws IOException {
            return new RrBodySoa(new ByteBufferKaitaiStream(fileName));
        }

        public RrBodySoa(KaitaiStream _io) {
            this(_io, null, null);
        }

        public RrBodySoa(KaitaiStream _io, DnsPacket.ResourceRecord _parent) {
            this(_io, _parent, null);
        }

        public RrBodySoa(KaitaiStream _io, DnsPacket.ResourceRecord _parent, DnsPacket _root) {
            super(_io);
            this._parent = _parent;
            this._root = _root;
            _read();
        }
        private void _read() {
            this.class = this._io.readU2be();
            this.timeToLive = this._io.readU4be();
            this.dataLength = this._io.readU2be();
            this.primaryNameServer = new Domain(this._io, this, _root);
            this.reponsibleAuthority = new Domain(this._io, this, _root);
            this.serialNumber = this._io.readU4be();
            this.refreshInterval = this._io.readU4be();
            this.retryInterval = this._io.readU4be();
            this.expireLimit = this._io.readU4be();
            this.minimumTtl = this._io.readU4be();
        }
        private int class;
        private long timeToLive;
        private int dataLength;
        private Domain primaryNameServer;
        private Domain reponsibleAuthority;
        private long serialNumber;
        private long refreshInterval;
        private long retryInterval;
        private long expireLimit;
        private long minimumTtl;
        private DnsPacket _root;
        private DnsPacket.ResourceRecord _parent;
        public int class() { return class; }
        public long timeToLive() { return timeToLive; }
        public int dataLength() { return dataLength; }
        public Domain primaryNameServer() { return primaryNameServer; }
        public Domain reponsibleAuthority() { return reponsibleAuthority; }
        public long serialNumber() { return serialNumber; }
        public long refreshInterval() { return refreshInterval; }
        public long retryInterval() { return retryInterval; }
        public long expireLimit() { return expireLimit; }
        public long minimumTtl() { return minimumTtl; }
        public DnsPacket _root() { return _root; }
        public DnsPacket.ResourceRecord _parent() { return _parent; }
    }
    private int transactionId;
    private int flags;
    private int qdcount;
    private int ancount;
    private int nscount;
    private int arcount;
    private ArrayList<Query> queries;
    private ArrayList<ResourceRecord> answers;
    private ArrayList<ResourceRecord> authorities;
    private ArrayList<ResourceRecord> additionals;
    private DnsPacket _root;
    private KaitaiStruct _parent;
    public int transactionId() { return transactionId; }
    public int flags() { return flags; }
    public int qdcount() { return qdcount; }
    public int ancount() { return ancount; }
    public int nscount() { return nscount; }
    public int arcount() { return arcount; }
    public ArrayList<Query> queries() { return queries; }
    public ArrayList<ResourceRecord> answers() { return answers; }
    public ArrayList<ResourceRecord> authorities() { return authorities; }
    public ArrayList<ResourceRecord> additionals() { return additionals; }
    public DnsPacket _root() { return _root; }
    public KaitaiStruct _parent() { return _parent; }
}
