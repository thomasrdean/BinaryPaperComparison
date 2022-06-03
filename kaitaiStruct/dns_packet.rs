// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

use std::option::Option;
use std::boxed::Box;
use std::io::Result;
use std::io::Cursor;
use std::vec::Vec;
use std::default::Default;
use kaitai_struct::KaitaiStream;
use kaitai_struct::KaitaiStruct;

#[derive(Default)]
pub struct DnsPacket {
    pub transactionId: u16,
    pub flags: u16,
    pub qdcount: u16,
    pub ancount: u16,
    pub nscount: u16,
    pub arcount: u16,
    pub queries: Vec<Box<DnsPacket__Query>>,
    pub answers: Vec<Box<DnsPacket__ResourceRecord>>,
    pub authorities: Vec<Box<DnsPacket__ResourceRecord>>,
    pub additionals: Vec<Box<DnsPacket__ResourceRecord>>,
}

impl KaitaiStruct for DnsPacket {
    fn new<S: KaitaiStream>(stream: &mut S,
                            _parent: &Option<Box<KaitaiStruct>>,
                            _root: &Option<Box<KaitaiStruct>>)
                            -> Result<Self>
        where Self: Sized {
        let mut s: Self = Default::default();

        s.stream = stream;
        s.read(stream, _parent, _root)?;

        Ok(s)
    }


    fn read<S: KaitaiStream>(&mut self,
                             stream: &mut S,
                             _parent: &Option<Box<KaitaiStruct>>,
                             _root: &Option<Box<KaitaiStruct>>)
                             -> Result<()>
        where Self: Sized {
        self.transactionId = self.stream.read_u2be()?;
        self.flags = self.stream.read_u2be()?;
        self.qdcount = self.stream.read_u2be()?;
        self.ancount = self.stream.read_u2be()?;
        self.nscount = self.stream.read_u2be()?;
        self.arcount = self.stream.read_u2be()?;
        self.queries = vec!();
        for i in 0..self.qdcount {
            self.queries.push(Box::new(DnsPacket__Query::new(self.stream, self, _root)?));
        }
        self.answers = vec!();
        for i in 0..self.ancount {
            self.answers.push(Box::new(DnsPacket__ResourceRecord::new(self.stream, self, _root)?));
        }
        self.authorities = vec!();
        for i in 0..self.nscount {
            self.authorities.push(Box::new(DnsPacket__ResourceRecord::new(self.stream, self, _root)?));
        }
        self.additionals = vec!();
        for i in 0..self.arcount {
            self.additionals.push(Box::new(DnsPacket__ResourceRecord::new(self.stream, self, _root)?));
        }
    }
}

impl DnsPacket {
}
enum DnsPacket__RrType {
    A,
    NS,
    CNAME,
    SOA,
    AAAA,
    OPT,
    DS,
    RRSIG,
    KEY,
    NSEC3,
}
#[derive(Default)]
pub struct DnsPacket__Map {
    pub mapNum: u8,
    pub length: u8,
    pub mapBits: String,
}

impl KaitaiStruct for DnsPacket__Map {
    fn new<S: KaitaiStream>(stream: &mut S,
                            _parent: &Option<Box<KaitaiStruct>>,
                            _root: &Option<Box<KaitaiStruct>>)
                            -> Result<Self>
        where Self: Sized {
        let mut s: Self = Default::default();

        s.stream = stream;
        s.read(stream, _parent, _root)?;

        Ok(s)
    }


    fn read<S: KaitaiStream>(&mut self,
                             stream: &mut S,
                             _parent: &Option<Box<KaitaiStruct>>,
                             _root: &Option<Box<KaitaiStruct>>)
                             -> Result<()>
        where Self: Sized {
        self.mapNum = self.stream.read_u1()?;
        self.length = self.stream.read_u1()?;
        self.mapBits = panic!("Unimplemented encoding for bytesToStr: {}", "utf-8");
    }
}

impl DnsPacket__Map {
}
#[derive(Default)]
pub struct DnsPacket__ResourceRecord {
    pub name: Box<DnsPacket__Domain>,
    pub type: Box<DnsPacket__RrType>,
    pub body: Option<Box<KaitaiStruct>>,
}

impl KaitaiStruct for DnsPacket__ResourceRecord {
    fn new<S: KaitaiStream>(stream: &mut S,
                            _parent: &Option<Box<KaitaiStruct>>,
                            _root: &Option<Box<KaitaiStruct>>)
                            -> Result<Self>
        where Self: Sized {
        let mut s: Self = Default::default();

        s.stream = stream;
        s.read(stream, _parent, _root)?;

        Ok(s)
    }


    fn read<S: KaitaiStream>(&mut self,
                             stream: &mut S,
                             _parent: &Option<Box<KaitaiStruct>>,
                             _root: &Option<Box<KaitaiStruct>>)
                             -> Result<()>
        where Self: Sized {
        self.name = Box::new(DnsPacket__Domain::new(self.stream, self, _root)?);
        self.type = self.stream.read_u2be()?;
        match self.type {
            DnsPacket__RrType::A => {
                self.body = Box::new(DnsPacket__RrBodyA::new(self.stream, self, _root)?);
            },
            DnsPacket__RrType::DS => {
                self.body = Box::new(DnsPacket__RrBodyDs::new(self.stream, self, _root)?);
            },
            DnsPacket__RrType::NS => {
                self.body = Box::new(DnsPacket__RrBodyNs::new(self.stream, self, _root)?);
            },
            DnsPacket__RrType::KEY => {
                self.body = Box::new(DnsPacket__RrBodyKey::new(self.stream, self, _root)?);
            },
            DnsPacket__RrType::CNAME => {
                self.body = Box::new(DnsPacket__RrBodyCname::new(self.stream, self, _root)?);
            },
            DnsPacket__RrType::OPT => {
                self.body = Box::new(DnsPacket__RrBodyOpt::new(self.stream, self, _root)?);
            },
            DnsPacket__RrType::RRSIG => {
                self.body = Box::new(DnsPacket__RrBodyRrsig::new(self.stream, self, _root)?);
            },
            DnsPacket__RrType::NSEC3 => {
                self.body = Box::new(DnsPacket__RrBodyNsec3::new(self.stream, self, _root)?);
            },
            DnsPacket__RrType::AAAA => {
                self.body = Box::new(DnsPacket__RrBodyAaaa::new(self.stream, self, _root)?);
            },
            DnsPacket__RrType::SOA => {
                self.body = Box::new(DnsPacket__RrBodySoa::new(self.stream, self, _root)?);
            },
        }
    }
}

impl DnsPacket__ResourceRecord {
}
#[derive(Default)]
pub struct DnsPacket__RrBodyOpt {
    pub udpPayloadSize: u16,
    pub higherBitsInExtendedRcode: u8,
    pub edns0version: u8,
    pub z: u16,
    pub dataLength: u16,
}

impl KaitaiStruct for DnsPacket__RrBodyOpt {
    fn new<S: KaitaiStream>(stream: &mut S,
                            _parent: &Option<Box<KaitaiStruct>>,
                            _root: &Option<Box<KaitaiStruct>>)
                            -> Result<Self>
        where Self: Sized {
        let mut s: Self = Default::default();

        s.stream = stream;
        s.read(stream, _parent, _root)?;

        Ok(s)
    }


    fn read<S: KaitaiStream>(&mut self,
                             stream: &mut S,
                             _parent: &Option<Box<KaitaiStruct>>,
                             _root: &Option<Box<KaitaiStruct>>)
                             -> Result<()>
        where Self: Sized {
        self.udpPayloadSize = self.stream.read_u2be()?;
        self.higherBitsInExtendedRcode = self.stream.read_u1()?;
        self.edns0version = self.stream.read_u1()?;
        self.z = self.stream.read_u2be()?;
        self.dataLength = self.stream.read_u2be()?;
    }
}

impl DnsPacket__RrBodyOpt {
}
#[derive(Default)]
pub struct DnsPacket__RrBodyKey {
    pub class: u16,
}

impl KaitaiStruct for DnsPacket__RrBodyKey {
    fn new<S: KaitaiStream>(stream: &mut S,
                            _parent: &Option<Box<KaitaiStruct>>,
                            _root: &Option<Box<KaitaiStruct>>)
                            -> Result<Self>
        where Self: Sized {
        let mut s: Self = Default::default();

        s.stream = stream;
        s.read(stream, _parent, _root)?;

        Ok(s)
    }


    fn read<S: KaitaiStream>(&mut self,
                             stream: &mut S,
                             _parent: &Option<Box<KaitaiStruct>>,
                             _root: &Option<Box<KaitaiStruct>>)
                             -> Result<()>
        where Self: Sized {
        self.class = self.stream.read_u2be()?;
    }
}

impl DnsPacket__RrBodyKey {
}
#[derive(Default)]
pub struct DnsPacket__Domain {
    pub name: Vec<Box<DnsPacket__Word>>,
}

impl KaitaiStruct for DnsPacket__Domain {
    fn new<S: KaitaiStream>(stream: &mut S,
                            _parent: &Option<Box<KaitaiStruct>>,
                            _root: &Option<Box<KaitaiStruct>>)
                            -> Result<Self>
        where Self: Sized {
        let mut s: Self = Default::default();

        s.stream = stream;
        s.read(stream, _parent, _root)?;

        Ok(s)
    }


    fn read<S: KaitaiStream>(&mut self,
                             stream: &mut S,
                             _parent: &Option<Box<KaitaiStruct>>,
                             _root: &Option<Box<KaitaiStruct>>)
                             -> Result<()>
        where Self: Sized {
        self.name = vec!();
        while {
            let tmpa = Box::new(DnsPacket__Word::new(self.stream, self, _root)?);
            self.name.append(Box::new(DnsPacket__Word::new(self.stream, self, _root)?));
            !( ((tmpa.length == 0) || (tmpa.length >= 192)) )
        } { }
    }
}

impl DnsPacket__Domain {
}
#[derive(Default)]
pub struct DnsPacket__Ipv6Address {
    pub ipV6: Vec<u8>,
}

impl KaitaiStruct for DnsPacket__Ipv6Address {
    fn new<S: KaitaiStream>(stream: &mut S,
                            _parent: &Option<Box<KaitaiStruct>>,
                            _root: &Option<Box<KaitaiStruct>>)
                            -> Result<Self>
        where Self: Sized {
        let mut s: Self = Default::default();

        s.stream = stream;
        s.read(stream, _parent, _root)?;

        Ok(s)
    }


    fn read<S: KaitaiStream>(&mut self,
                             stream: &mut S,
                             _parent: &Option<Box<KaitaiStruct>>,
                             _root: &Option<Box<KaitaiStruct>>)
                             -> Result<()>
        where Self: Sized {
        self.ipV6 = self.stream.read_bytes(16)?;
    }
}

impl DnsPacket__Ipv6Address {
}
#[derive(Default)]
pub struct DnsPacket__Query {
    pub name: Box<DnsPacket__Domain>,
    pub type: Box<DnsPacket__RrType>,
    pub queryClass: u16,
}

impl KaitaiStruct for DnsPacket__Query {
    fn new<S: KaitaiStream>(stream: &mut S,
                            _parent: &Option<Box<KaitaiStruct>>,
                            _root: &Option<Box<KaitaiStruct>>)
                            -> Result<Self>
        where Self: Sized {
        let mut s: Self = Default::default();

        s.stream = stream;
        s.read(stream, _parent, _root)?;

        Ok(s)
    }


    fn read<S: KaitaiStream>(&mut self,
                             stream: &mut S,
                             _parent: &Option<Box<KaitaiStruct>>,
                             _root: &Option<Box<KaitaiStruct>>)
                             -> Result<()>
        where Self: Sized {
        self.name = Box::new(DnsPacket__Domain::new(self.stream, self, _root)?);
        self.type = self.stream.read_u2be()?;
        self.queryClass = self.stream.read_u2be()?;
    }
}

impl DnsPacket__Query {
}
#[derive(Default)]
pub struct DnsPacket__RrBodyRrsig {
    pub class: u16,
    pub timeToLive: u32,
    pub dataLength: u16,
    pub typeCov: u16,
    pub alg: u8,
    pub labels: u8,
    pub origTimeToLive: u32,
    pub sigExp: u32,
    pub sigInception: u32,
    pub keyTag: u16,
    pub signName: Box<DnsPacket__Domain>,
    pub signature: String,
}

impl KaitaiStruct for DnsPacket__RrBodyRrsig {
    fn new<S: KaitaiStream>(stream: &mut S,
                            _parent: &Option<Box<KaitaiStruct>>,
                            _root: &Option<Box<KaitaiStruct>>)
                            -> Result<Self>
        where Self: Sized {
        let mut s: Self = Default::default();

        s.stream = stream;
        s.read(stream, _parent, _root)?;

        Ok(s)
    }


    fn read<S: KaitaiStream>(&mut self,
                             stream: &mut S,
                             _parent: &Option<Box<KaitaiStruct>>,
                             _root: &Option<Box<KaitaiStruct>>)
                             -> Result<()>
        where Self: Sized {
        self.class = self.stream.read_u2be()?;
        self.timeToLive = self.stream.read_u4be()?;
        self.dataLength = self.stream.read_u2be()?;
        self.typeCov = self.stream.read_u2be()?;
        self.alg = self.stream.read_u1()?;
        self.labels = self.stream.read_u1()?;
        self.origTimeToLive = self.stream.read_u4be()?;
        self.sigExp = self.stream.read_u4be()?;
        self.sigInception = self.stream.read_u4be()?;
        self.keyTag = self.stream.read_u2be()?;
        self.signName = Box::new(DnsPacket__Domain::new(self.stream, self, _root)?);
        self.signature = panic!("Unimplemented encoding for bytesToStr: {}", "utf-8");
    }
}

impl DnsPacket__RrBodyRrsig {
}
#[derive(Default)]
pub struct DnsPacket__Ipv4Address {
    pub ip: Vec<u8>,
}

impl KaitaiStruct for DnsPacket__Ipv4Address {
    fn new<S: KaitaiStream>(stream: &mut S,
                            _parent: &Option<Box<KaitaiStruct>>,
                            _root: &Option<Box<KaitaiStruct>>)
                            -> Result<Self>
        where Self: Sized {
        let mut s: Self = Default::default();

        s.stream = stream;
        s.read(stream, _parent, _root)?;

        Ok(s)
    }


    fn read<S: KaitaiStream>(&mut self,
                             stream: &mut S,
                             _parent: &Option<Box<KaitaiStruct>>,
                             _root: &Option<Box<KaitaiStruct>>)
                             -> Result<()>
        where Self: Sized {
        self.ip = self.stream.read_bytes(4)?;
    }
}

impl DnsPacket__Ipv4Address {
}
#[derive(Default)]
pub struct DnsPacket__RrBodyCname {
    pub class: u16,
    pub timeToLive: u32,
    pub dataLength: u16,
    pub cname: Box<DnsPacket__Domain>,
}

impl KaitaiStruct for DnsPacket__RrBodyCname {
    fn new<S: KaitaiStream>(stream: &mut S,
                            _parent: &Option<Box<KaitaiStruct>>,
                            _root: &Option<Box<KaitaiStruct>>)
                            -> Result<Self>
        where Self: Sized {
        let mut s: Self = Default::default();

        s.stream = stream;
        s.read(stream, _parent, _root)?;

        Ok(s)
    }


    fn read<S: KaitaiStream>(&mut self,
                             stream: &mut S,
                             _parent: &Option<Box<KaitaiStruct>>,
                             _root: &Option<Box<KaitaiStruct>>)
                             -> Result<()>
        where Self: Sized {
        self.class = self.stream.read_u2be()?;
        self.timeToLive = self.stream.read_u4be()?;
        self.dataLength = self.stream.read_u2be()?;
        self.cname = Box::new(DnsPacket__Domain::new(self.stream, self, _root)?);
    }
}

impl DnsPacket__RrBodyCname {
}
#[derive(Default)]
pub struct DnsPacket__RrBodyAaaa {
    pub class: u16,
    pub timeToLive: u32,
    pub dataLength: u16,
    pub address: Box<DnsPacket__Ipv6Address>,
}

impl KaitaiStruct for DnsPacket__RrBodyAaaa {
    fn new<S: KaitaiStream>(stream: &mut S,
                            _parent: &Option<Box<KaitaiStruct>>,
                            _root: &Option<Box<KaitaiStruct>>)
                            -> Result<Self>
        where Self: Sized {
        let mut s: Self = Default::default();

        s.stream = stream;
        s.read(stream, _parent, _root)?;

        Ok(s)
    }


    fn read<S: KaitaiStream>(&mut self,
                             stream: &mut S,
                             _parent: &Option<Box<KaitaiStruct>>,
                             _root: &Option<Box<KaitaiStruct>>)
                             -> Result<()>
        where Self: Sized {
        self.class = self.stream.read_u2be()?;
        self.timeToLive = self.stream.read_u4be()?;
        self.dataLength = self.stream.read_u2be()?;
        self.address = Box::new(DnsPacket__Ipv6Address::new(self.stream, self, _root)?);
    }
}

impl DnsPacket__RrBodyAaaa {
}
#[derive(Default)]
pub struct DnsPacket__RrBodyNs {
    pub class: u16,
    pub timeToLive: u32,
    pub dataLength: u16,
    pub nameServer: Box<DnsPacket__Domain>,
}

impl KaitaiStruct for DnsPacket__RrBodyNs {
    fn new<S: KaitaiStream>(stream: &mut S,
                            _parent: &Option<Box<KaitaiStruct>>,
                            _root: &Option<Box<KaitaiStruct>>)
                            -> Result<Self>
        where Self: Sized {
        let mut s: Self = Default::default();

        s.stream = stream;
        s.read(stream, _parent, _root)?;

        Ok(s)
    }


    fn read<S: KaitaiStream>(&mut self,
                             stream: &mut S,
                             _parent: &Option<Box<KaitaiStruct>>,
                             _root: &Option<Box<KaitaiStruct>>)
                             -> Result<()>
        where Self: Sized {
        self.class = self.stream.read_u2be()?;
        self.timeToLive = self.stream.read_u4be()?;
        self.dataLength = self.stream.read_u2be()?;
        self.nameServer = Box::new(DnsPacket__Domain::new(self.stream, self, _root)?);
    }
}

impl DnsPacket__RrBodyNs {
}
#[derive(Default)]
pub struct DnsPacket__RrBodyDs {
    pub class: u16,
    pub timeToLive: u32,
    pub dataLength: u16,
    pub keyid: u16,
    pub alg: u8,
    pub digestType: u8,
    pub digest: String,
}

impl KaitaiStruct for DnsPacket__RrBodyDs {
    fn new<S: KaitaiStream>(stream: &mut S,
                            _parent: &Option<Box<KaitaiStruct>>,
                            _root: &Option<Box<KaitaiStruct>>)
                            -> Result<Self>
        where Self: Sized {
        let mut s: Self = Default::default();

        s.stream = stream;
        s.read(stream, _parent, _root)?;

        Ok(s)
    }


    fn read<S: KaitaiStream>(&mut self,
                             stream: &mut S,
                             _parent: &Option<Box<KaitaiStruct>>,
                             _root: &Option<Box<KaitaiStruct>>)
                             -> Result<()>
        where Self: Sized {
        self.class = self.stream.read_u2be()?;
        self.timeToLive = self.stream.read_u4be()?;
        self.dataLength = self.stream.read_u2be()?;
        self.keyid = self.stream.read_u2be()?;
        self.alg = self.stream.read_u1()?;
        self.digestType = self.stream.read_u1()?;
        self.digest = panic!("Unimplemented encoding for bytesToStr: {}", "utf-8");
    }
}

impl DnsPacket__RrBodyDs {
}
#[derive(Default)]
pub struct DnsPacket__RrBodyNsec3 {
    pub class: u16,
    pub timeToLive: u32,
    pub dataLength: u16,
    pub alg: u8,
    pub flags: u8,
    pub iterations: u16,
    pub saltLength: u8,
    pub hashLength: u8,
    pub nextHash: String,
    pub typeMap: Box<DnsPacket__Map>,
}

impl KaitaiStruct for DnsPacket__RrBodyNsec3 {
    fn new<S: KaitaiStream>(stream: &mut S,
                            _parent: &Option<Box<KaitaiStruct>>,
                            _root: &Option<Box<KaitaiStruct>>)
                            -> Result<Self>
        where Self: Sized {
        let mut s: Self = Default::default();

        s.stream = stream;
        s.read(stream, _parent, _root)?;

        Ok(s)
    }


    fn read<S: KaitaiStream>(&mut self,
                             stream: &mut S,
                             _parent: &Option<Box<KaitaiStruct>>,
                             _root: &Option<Box<KaitaiStruct>>)
                             -> Result<()>
        where Self: Sized {
        self.class = self.stream.read_u2be()?;
        self.timeToLive = self.stream.read_u4be()?;
        self.dataLength = self.stream.read_u2be()?;
        self.alg = self.stream.read_u1()?;
        self.flags = self.stream.read_u1()?;
        self.iterations = self.stream.read_u2be()?;
        self.saltLength = self.stream.read_u1()?;
        self.hashLength = self.stream.read_u1()?;
        self.nextHash = panic!("Unimplemented encoding for bytesToStr: {}", "utf-8");
        self.typeMap = Box::new(DnsPacket__Map::new(self.stream, self, _root)?);
    }
}

impl DnsPacket__RrBodyNsec3 {
}
#[derive(Default)]
pub struct DnsPacket__RrBodyA {
    pub class: u16,
    pub timeToLive: u32,
    pub dataLength: u16,
    pub address: Box<DnsPacket__Ipv4Address>,
}

impl KaitaiStruct for DnsPacket__RrBodyA {
    fn new<S: KaitaiStream>(stream: &mut S,
                            _parent: &Option<Box<KaitaiStruct>>,
                            _root: &Option<Box<KaitaiStruct>>)
                            -> Result<Self>
        where Self: Sized {
        let mut s: Self = Default::default();

        s.stream = stream;
        s.read(stream, _parent, _root)?;

        Ok(s)
    }


    fn read<S: KaitaiStream>(&mut self,
                             stream: &mut S,
                             _parent: &Option<Box<KaitaiStruct>>,
                             _root: &Option<Box<KaitaiStruct>>)
                             -> Result<()>
        where Self: Sized {
        self.class = self.stream.read_u2be()?;
        self.timeToLive = self.stream.read_u4be()?;
        self.dataLength = self.stream.read_u2be()?;
        self.address = Box::new(DnsPacket__Ipv4Address::new(self.stream, self, _root)?);
    }
}

impl DnsPacket__RrBodyA {
}
#[derive(Default)]
pub struct DnsPacket__Word {
    pub length: u8,
    pub ref: u8,
    pub letters: String,
    pub isRef: Option<bool>,
}

impl KaitaiStruct for DnsPacket__Word {
    fn new<S: KaitaiStream>(stream: &mut S,
                            _parent: &Option<Box<KaitaiStruct>>,
                            _root: &Option<Box<KaitaiStruct>>)
                            -> Result<Self>
        where Self: Sized {
        let mut s: Self = Default::default();

        s.stream = stream;
        s.read(stream, _parent, _root)?;

        Ok(s)
    }


    fn read<S: KaitaiStream>(&mut self,
                             stream: &mut S,
                             _parent: &Option<Box<KaitaiStruct>>,
                             _root: &Option<Box<KaitaiStruct>>)
                             -> Result<()>
        where Self: Sized {
        self.length = self.stream.read_u1()?;
        if self.is_ref {
            self.ref = self.stream.read_u1()?;
        }
        if !(self.is_ref) {
            self.letters = panic!("Unimplemented encoding for bytesToStr: {}", "utf-8");
        }
    }
}

impl DnsPacket__Word {
    fn isRef(&mut self) -> bool {
        if let Some(x) = self.isRef {
            return x;
        }

        self.isRef = self.length == 192;
        return self.isRef;
    }
}
#[derive(Default)]
pub struct DnsPacket__RrBodySoa {
    pub class: u16,
    pub timeToLive: u32,
    pub dataLength: u16,
    pub primaryNameServer: Box<DnsPacket__Domain>,
    pub reponsibleAuthority: Box<DnsPacket__Domain>,
    pub serialNumber: u32,
    pub refreshInterval: u32,
    pub retryInterval: u32,
    pub expireLimit: u32,
    pub minimumTtl: u32,
}

impl KaitaiStruct for DnsPacket__RrBodySoa {
    fn new<S: KaitaiStream>(stream: &mut S,
                            _parent: &Option<Box<KaitaiStruct>>,
                            _root: &Option<Box<KaitaiStruct>>)
                            -> Result<Self>
        where Self: Sized {
        let mut s: Self = Default::default();

        s.stream = stream;
        s.read(stream, _parent, _root)?;

        Ok(s)
    }


    fn read<S: KaitaiStream>(&mut self,
                             stream: &mut S,
                             _parent: &Option<Box<KaitaiStruct>>,
                             _root: &Option<Box<KaitaiStruct>>)
                             -> Result<()>
        where Self: Sized {
        self.class = self.stream.read_u2be()?;
        self.timeToLive = self.stream.read_u4be()?;
        self.dataLength = self.stream.read_u2be()?;
        self.primaryNameServer = Box::new(DnsPacket__Domain::new(self.stream, self, _root)?);
        self.reponsibleAuthority = Box::new(DnsPacket__Domain::new(self.stream, self, _root)?);
        self.serialNumber = self.stream.read_u4be()?;
        self.refreshInterval = self.stream.read_u4be()?;
        self.retryInterval = self.stream.read_u4be()?;
        self.expireLimit = self.stream.read_u4be()?;
        self.minimumTtl = self.stream.read_u4be()?;
    }
}

impl DnsPacket__RrBodySoa {
}
