<?php
// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

namespace {
    class DnsPacket extends \Kaitai\Struct\Struct {
        public function __construct(\Kaitai\Struct\Stream $_io, \Kaitai\Struct\Struct $_parent = null, \DnsPacket $_root = null) {
            parent::__construct($_io, $_parent, $_root);
            $this->_read();
        }

        private function _read() {
            $this->_m_transactionId = $this->_io->readU2be();
            $this->_m_flags = $this->_io->readU2be();
            $this->_m_qdcount = $this->_io->readU2be();
            $this->_m_ancount = $this->_io->readU2be();
            $this->_m_nscount = $this->_io->readU2be();
            $this->_m_arcount = $this->_io->readU2be();
            $this->_m_queries = [];
            $n = $this->qdcount();
            for ($i = 0; $i < $n; $i++) {
                $this->_m_queries[] = new \DnsPacket\Query($this->_io, $this, $this->_root);
            }
            $this->_m_answers = [];
            $n = $this->ancount();
            for ($i = 0; $i < $n; $i++) {
                $this->_m_answers[] = new \DnsPacket\ResourceRecord($this->_io, $this, $this->_root);
            }
            $this->_m_authorities = [];
            $n = $this->nscount();
            for ($i = 0; $i < $n; $i++) {
                $this->_m_authorities[] = new \DnsPacket\ResourceRecord($this->_io, $this, $this->_root);
            }
            $this->_m_additionals = [];
            $n = $this->arcount();
            for ($i = 0; $i < $n; $i++) {
                $this->_m_additionals[] = new \DnsPacket\ResourceRecord($this->_io, $this, $this->_root);
            }
        }
        protected $_m_transactionId;
        protected $_m_flags;
        protected $_m_qdcount;
        protected $_m_ancount;
        protected $_m_nscount;
        protected $_m_arcount;
        protected $_m_queries;
        protected $_m_answers;
        protected $_m_authorities;
        protected $_m_additionals;
        public function transactionId() { return $this->_m_transactionId; }
        public function flags() { return $this->_m_flags; }
        public function qdcount() { return $this->_m_qdcount; }
        public function ancount() { return $this->_m_ancount; }
        public function nscount() { return $this->_m_nscount; }
        public function arcount() { return $this->_m_arcount; }
        public function queries() { return $this->_m_queries; }
        public function answers() { return $this->_m_answers; }
        public function authorities() { return $this->_m_authorities; }
        public function additionals() { return $this->_m_additionals; }
    }
}

namespace DnsPacket {
    class Map extends \Kaitai\Struct\Struct {
        public function __construct(\Kaitai\Struct\Stream $_io, \DnsPacket\RrBodyNsec3 $_parent = null, \DnsPacket $_root = null) {
            parent::__construct($_io, $_parent, $_root);
            $this->_read();
        }

        private function _read() {
            $this->_m_mapNum = $this->_io->readU1();
            $this->_m_length = $this->_io->readU1();
            $this->_m_mapBits = \Kaitai\Struct\Stream::bytesToStr($this->_io->readBytes($this->length()), "utf-8");
        }
        protected $_m_mapNum;
        protected $_m_length;
        protected $_m_mapBits;
        public function mapNum() { return $this->_m_mapNum; }
        public function length() { return $this->_m_length; }
        public function mapBits() { return $this->_m_mapBits; }
    }
}

namespace DnsPacket {
    class ResourceRecord extends \Kaitai\Struct\Struct {
        public function __construct(\Kaitai\Struct\Stream $_io, \DnsPacket $_parent = null, \DnsPacket $_root = null) {
            parent::__construct($_io, $_parent, $_root);
            $this->_read();
        }

        private function _read() {
            $this->_m_name = new \DnsPacket\Domain($this->_io, $this, $this->_root);
            $this->_m_type = $this->_io->readU2be();
            switch ($this->type()) {
                case \DnsPacket\RrType::A:
                    $this->_m_body = new \DnsPacket\RrBodyA($this->_io, $this, $this->_root);
                    break;
                case \DnsPacket\RrType::DS:
                    $this->_m_body = new \DnsPacket\RrBodyDs($this->_io, $this, $this->_root);
                    break;
                case \DnsPacket\RrType::NS:
                    $this->_m_body = new \DnsPacket\RrBodyNs($this->_io, $this, $this->_root);
                    break;
                case \DnsPacket\RrType::KEY:
                    $this->_m_body = new \DnsPacket\RrBodyKey($this->_io, $this, $this->_root);
                    break;
                case \DnsPacket\RrType::CNAME:
                    $this->_m_body = new \DnsPacket\RrBodyCname($this->_io, $this, $this->_root);
                    break;
                case \DnsPacket\RrType::OPT:
                    $this->_m_body = new \DnsPacket\RrBodyOpt($this->_io, $this, $this->_root);
                    break;
                case \DnsPacket\RrType::RRSIG:
                    $this->_m_body = new \DnsPacket\RrBodyRrsig($this->_io, $this, $this->_root);
                    break;
                case \DnsPacket\RrType::NSEC3:
                    $this->_m_body = new \DnsPacket\RrBodyNsec3($this->_io, $this, $this->_root);
                    break;
                case \DnsPacket\RrType::AAAA:
                    $this->_m_body = new \DnsPacket\RrBodyAaaa($this->_io, $this, $this->_root);
                    break;
                case \DnsPacket\RrType::SOA:
                    $this->_m_body = new \DnsPacket\RrBodySoa($this->_io, $this, $this->_root);
                    break;
            }
        }
        protected $_m_name;
        protected $_m_type;
        protected $_m_body;
        public function name() { return $this->_m_name; }
        public function type() { return $this->_m_type; }
        public function body() { return $this->_m_body; }
    }
}

namespace DnsPacket {
    class RrBodyOpt extends \Kaitai\Struct\Struct {
        public function __construct(\Kaitai\Struct\Stream $_io, \DnsPacket\ResourceRecord $_parent = null, \DnsPacket $_root = null) {
            parent::__construct($_io, $_parent, $_root);
            $this->_read();
        }

        private function _read() {
            $this->_m_udpPayloadSize = $this->_io->readU2be();
            $this->_m_higherBitsInExtendedRcode = $this->_io->readU1();
            $this->_m_edns0version = $this->_io->readU1();
            $this->_m_z = $this->_io->readU2be();
            $this->_m_dataLength = $this->_io->readU2be();
        }
        protected $_m_udpPayloadSize;
        protected $_m_higherBitsInExtendedRcode;
        protected $_m_edns0version;
        protected $_m_z;
        protected $_m_dataLength;
        public function udpPayloadSize() { return $this->_m_udpPayloadSize; }
        public function higherBitsInExtendedRcode() { return $this->_m_higherBitsInExtendedRcode; }
        public function edns0version() { return $this->_m_edns0version; }
        public function z() { return $this->_m_z; }
        public function dataLength() { return $this->_m_dataLength; }
    }
}

namespace DnsPacket {
    class RrBodyKey extends \Kaitai\Struct\Struct {
        public function __construct(\Kaitai\Struct\Stream $_io, \DnsPacket\ResourceRecord $_parent = null, \DnsPacket $_root = null) {
            parent::__construct($_io, $_parent, $_root);
            $this->_read();
        }

        private function _read() {
            $this->_m_class = $this->_io->readU2be();
        }
        protected $_m_class;
        public function class() { return $this->_m_class; }
    }
}

namespace DnsPacket {
    class Domain extends \Kaitai\Struct\Struct {
        public function __construct(\Kaitai\Struct\Stream $_io, \Kaitai\Struct\Struct $_parent = null, \DnsPacket $_root = null) {
            parent::__construct($_io, $_parent, $_root);
            $this->_read();
        }

        private function _read() {
            $this->_m_name = [];
            $i = 0;
            do {
                $_ = new \DnsPacket\Word($this->_io, $this, $this->_root);
                $this->_m_name[] = $_;
                $i++;
            } while (!( (($_->length() == 0) || ($_->length() >= 192)) ));
        }
        protected $_m_name;
        public function name() { return $this->_m_name; }
    }
}

namespace DnsPacket {
    class Ipv6Address extends \Kaitai\Struct\Struct {
        public function __construct(\Kaitai\Struct\Stream $_io, \DnsPacket\RrBodyAaaa $_parent = null, \DnsPacket $_root = null) {
            parent::__construct($_io, $_parent, $_root);
            $this->_read();
        }

        private function _read() {
            $this->_m_ipV6 = $this->_io->readBytes(16);
        }
        protected $_m_ipV6;
        public function ipV6() { return $this->_m_ipV6; }
    }
}

namespace DnsPacket {
    class Query extends \Kaitai\Struct\Struct {
        public function __construct(\Kaitai\Struct\Stream $_io, \DnsPacket $_parent = null, \DnsPacket $_root = null) {
            parent::__construct($_io, $_parent, $_root);
            $this->_read();
        }

        private function _read() {
            $this->_m_name = new \DnsPacket\Domain($this->_io, $this, $this->_root);
            $this->_m_type = $this->_io->readU2be();
            $this->_m_queryClass = $this->_io->readU2be();
        }
        protected $_m_name;
        protected $_m_type;
        protected $_m_queryClass;
        public function name() { return $this->_m_name; }
        public function type() { return $this->_m_type; }
        public function queryClass() { return $this->_m_queryClass; }
    }
}

namespace DnsPacket {
    class RrBodyRrsig extends \Kaitai\Struct\Struct {
        public function __construct(\Kaitai\Struct\Stream $_io, \DnsPacket\ResourceRecord $_parent = null, \DnsPacket $_root = null) {
            parent::__construct($_io, $_parent, $_root);
            $this->_read();
        }

        private function _read() {
            $this->_m_class = $this->_io->readU2be();
            $this->_m_timeToLive = $this->_io->readU4be();
            $this->_m_dataLength = $this->_io->readU2be();
            $this->_m_typeCov = $this->_io->readU2be();
            $this->_m_alg = $this->_io->readU1();
            $this->_m_labels = $this->_io->readU1();
            $this->_m_origTimeToLive = $this->_io->readU4be();
            $this->_m_sigExp = $this->_io->readU4be();
            $this->_m_sigInception = $this->_io->readU4be();
            $this->_m_keyTag = $this->_io->readU2be();
            $this->_m_signName = new \DnsPacket\Domain($this->_io, $this, $this->_root);
            $this->_m_signature = \Kaitai\Struct\Stream::bytesToStr($this->_io->readBytes(256), "utf-8");
        }
        protected $_m_class;
        protected $_m_timeToLive;
        protected $_m_dataLength;
        protected $_m_typeCov;
        protected $_m_alg;
        protected $_m_labels;
        protected $_m_origTimeToLive;
        protected $_m_sigExp;
        protected $_m_sigInception;
        protected $_m_keyTag;
        protected $_m_signName;
        protected $_m_signature;
        public function class() { return $this->_m_class; }
        public function timeToLive() { return $this->_m_timeToLive; }
        public function dataLength() { return $this->_m_dataLength; }
        public function typeCov() { return $this->_m_typeCov; }
        public function alg() { return $this->_m_alg; }
        public function labels() { return $this->_m_labels; }
        public function origTimeToLive() { return $this->_m_origTimeToLive; }
        public function sigExp() { return $this->_m_sigExp; }
        public function sigInception() { return $this->_m_sigInception; }
        public function keyTag() { return $this->_m_keyTag; }
        public function signName() { return $this->_m_signName; }
        public function signature() { return $this->_m_signature; }
    }
}

namespace DnsPacket {
    class Ipv4Address extends \Kaitai\Struct\Struct {
        public function __construct(\Kaitai\Struct\Stream $_io, \DnsPacket\RrBodyA $_parent = null, \DnsPacket $_root = null) {
            parent::__construct($_io, $_parent, $_root);
            $this->_read();
        }

        private function _read() {
            $this->_m_ip = $this->_io->readBytes(4);
        }
        protected $_m_ip;
        public function ip() { return $this->_m_ip; }
    }
}

namespace DnsPacket {
    class RrBodyCname extends \Kaitai\Struct\Struct {
        public function __construct(\Kaitai\Struct\Stream $_io, \DnsPacket\ResourceRecord $_parent = null, \DnsPacket $_root = null) {
            parent::__construct($_io, $_parent, $_root);
            $this->_read();
        }

        private function _read() {
            $this->_m_class = $this->_io->readU2be();
            $this->_m_timeToLive = $this->_io->readU4be();
            $this->_m_dataLength = $this->_io->readU2be();
            $this->_m_cname = new \DnsPacket\Domain($this->_io, $this, $this->_root);
        }
        protected $_m_class;
        protected $_m_timeToLive;
        protected $_m_dataLength;
        protected $_m_cname;
        public function class() { return $this->_m_class; }
        public function timeToLive() { return $this->_m_timeToLive; }
        public function dataLength() { return $this->_m_dataLength; }
        public function cname() { return $this->_m_cname; }
    }
}

namespace DnsPacket {
    class RrBodyAaaa extends \Kaitai\Struct\Struct {
        public function __construct(\Kaitai\Struct\Stream $_io, \DnsPacket\ResourceRecord $_parent = null, \DnsPacket $_root = null) {
            parent::__construct($_io, $_parent, $_root);
            $this->_read();
        }

        private function _read() {
            $this->_m_class = $this->_io->readU2be();
            $this->_m_timeToLive = $this->_io->readU4be();
            $this->_m_dataLength = $this->_io->readU2be();
            $this->_m_address = new \DnsPacket\Ipv6Address($this->_io, $this, $this->_root);
        }
        protected $_m_class;
        protected $_m_timeToLive;
        protected $_m_dataLength;
        protected $_m_address;
        public function class() { return $this->_m_class; }
        public function timeToLive() { return $this->_m_timeToLive; }
        public function dataLength() { return $this->_m_dataLength; }
        public function address() { return $this->_m_address; }
    }
}

namespace DnsPacket {
    class RrBodyNs extends \Kaitai\Struct\Struct {
        public function __construct(\Kaitai\Struct\Stream $_io, \DnsPacket\ResourceRecord $_parent = null, \DnsPacket $_root = null) {
            parent::__construct($_io, $_parent, $_root);
            $this->_read();
        }

        private function _read() {
            $this->_m_class = $this->_io->readU2be();
            $this->_m_timeToLive = $this->_io->readU4be();
            $this->_m_dataLength = $this->_io->readU2be();
            $this->_m_nameServer = new \DnsPacket\Domain($this->_io, $this, $this->_root);
        }
        protected $_m_class;
        protected $_m_timeToLive;
        protected $_m_dataLength;
        protected $_m_nameServer;
        public function class() { return $this->_m_class; }
        public function timeToLive() { return $this->_m_timeToLive; }
        public function dataLength() { return $this->_m_dataLength; }
        public function nameServer() { return $this->_m_nameServer; }
    }
}

namespace DnsPacket {
    class RrBodyDs extends \Kaitai\Struct\Struct {
        public function __construct(\Kaitai\Struct\Stream $_io, \DnsPacket\ResourceRecord $_parent = null, \DnsPacket $_root = null) {
            parent::__construct($_io, $_parent, $_root);
            $this->_read();
        }

        private function _read() {
            $this->_m_class = $this->_io->readU2be();
            $this->_m_timeToLive = $this->_io->readU4be();
            $this->_m_dataLength = $this->_io->readU2be();
            $this->_m_keyid = $this->_io->readU2be();
            $this->_m_alg = $this->_io->readU1();
            $this->_m_digestType = $this->_io->readU1();
            $this->_m_digest = \Kaitai\Struct\Stream::bytesToStr($this->_io->readBytes(32), "utf-8");
        }
        protected $_m_class;
        protected $_m_timeToLive;
        protected $_m_dataLength;
        protected $_m_keyid;
        protected $_m_alg;
        protected $_m_digestType;
        protected $_m_digest;
        public function class() { return $this->_m_class; }
        public function timeToLive() { return $this->_m_timeToLive; }
        public function dataLength() { return $this->_m_dataLength; }
        public function keyid() { return $this->_m_keyid; }
        public function alg() { return $this->_m_alg; }
        public function digestType() { return $this->_m_digestType; }
        public function digest() { return $this->_m_digest; }
    }
}

namespace DnsPacket {
    class RrBodyNsec3 extends \Kaitai\Struct\Struct {
        public function __construct(\Kaitai\Struct\Stream $_io, \DnsPacket\ResourceRecord $_parent = null, \DnsPacket $_root = null) {
            parent::__construct($_io, $_parent, $_root);
            $this->_read();
        }

        private function _read() {
            $this->_m_class = $this->_io->readU2be();
            $this->_m_timeToLive = $this->_io->readU4be();
            $this->_m_dataLength = $this->_io->readU2be();
            $this->_m_alg = $this->_io->readU1();
            $this->_m_flags = $this->_io->readU1();
            $this->_m_iterations = $this->_io->readU2be();
            $this->_m_saltLength = $this->_io->readU1();
            $this->_m_hashLength = $this->_io->readU1();
            $this->_m_nextHash = \Kaitai\Struct\Stream::bytesToStr($this->_io->readBytes($this->hashLength()), "utf-8");
            $this->_m_typeMap = new \DnsPacket\Map($this->_io, $this, $this->_root);
        }
        protected $_m_class;
        protected $_m_timeToLive;
        protected $_m_dataLength;
        protected $_m_alg;
        protected $_m_flags;
        protected $_m_iterations;
        protected $_m_saltLength;
        protected $_m_hashLength;
        protected $_m_nextHash;
        protected $_m_typeMap;
        public function class() { return $this->_m_class; }
        public function timeToLive() { return $this->_m_timeToLive; }
        public function dataLength() { return $this->_m_dataLength; }
        public function alg() { return $this->_m_alg; }
        public function flags() { return $this->_m_flags; }
        public function iterations() { return $this->_m_iterations; }
        public function saltLength() { return $this->_m_saltLength; }
        public function hashLength() { return $this->_m_hashLength; }
        public function nextHash() { return $this->_m_nextHash; }
        public function typeMap() { return $this->_m_typeMap; }
    }
}

namespace DnsPacket {
    class RrBodyA extends \Kaitai\Struct\Struct {
        public function __construct(\Kaitai\Struct\Stream $_io, \DnsPacket\ResourceRecord $_parent = null, \DnsPacket $_root = null) {
            parent::__construct($_io, $_parent, $_root);
            $this->_read();
        }

        private function _read() {
            $this->_m_class = $this->_io->readU2be();
            $this->_m_timeToLive = $this->_io->readU4be();
            $this->_m_dataLength = $this->_io->readU2be();
            $this->_m_address = new \DnsPacket\Ipv4Address($this->_io, $this, $this->_root);
        }
        protected $_m_class;
        protected $_m_timeToLive;
        protected $_m_dataLength;
        protected $_m_address;
        public function class() { return $this->_m_class; }
        public function timeToLive() { return $this->_m_timeToLive; }
        public function dataLength() { return $this->_m_dataLength; }
        public function address() { return $this->_m_address; }
    }
}

namespace DnsPacket {
    class Word extends \Kaitai\Struct\Struct {
        public function __construct(\Kaitai\Struct\Stream $_io, \DnsPacket\Domain $_parent = null, \DnsPacket $_root = null) {
            parent::__construct($_io, $_parent, $_root);
            $this->_read();
        }

        private function _read() {
            $this->_m_length = $this->_io->readU1();
            if ($this->isRef()) {
                $this->_m_ref = $this->_io->readU1();
            }
            if (!($this->isRef())) {
                $this->_m_letters = \Kaitai\Struct\Stream::bytesToStr($this->_io->readBytes($this->length()), "utf-8");
            }
        }
        protected $_m_isRef;
        public function isRef() {
            if ($this->_m_isRef !== null)
                return $this->_m_isRef;
            $this->_m_isRef = $this->length() == 192;
            return $this->_m_isRef;
        }
        protected $_m_length;
        protected $_m_ref;
        protected $_m_letters;
        public function length() { return $this->_m_length; }
        public function ref() { return $this->_m_ref; }
        public function letters() { return $this->_m_letters; }
    }
}

namespace DnsPacket {
    class RrBodySoa extends \Kaitai\Struct\Struct {
        public function __construct(\Kaitai\Struct\Stream $_io, \DnsPacket\ResourceRecord $_parent = null, \DnsPacket $_root = null) {
            parent::__construct($_io, $_parent, $_root);
            $this->_read();
        }

        private function _read() {
            $this->_m_class = $this->_io->readU2be();
            $this->_m_timeToLive = $this->_io->readU4be();
            $this->_m_dataLength = $this->_io->readU2be();
            $this->_m_primaryNameServer = new \DnsPacket\Domain($this->_io, $this, $this->_root);
            $this->_m_reponsibleAuthority = new \DnsPacket\Domain($this->_io, $this, $this->_root);
            $this->_m_serialNumber = $this->_io->readU4be();
            $this->_m_refreshInterval = $this->_io->readU4be();
            $this->_m_retryInterval = $this->_io->readU4be();
            $this->_m_expireLimit = $this->_io->readU4be();
            $this->_m_minimumTtl = $this->_io->readU4be();
        }
        protected $_m_class;
        protected $_m_timeToLive;
        protected $_m_dataLength;
        protected $_m_primaryNameServer;
        protected $_m_reponsibleAuthority;
        protected $_m_serialNumber;
        protected $_m_refreshInterval;
        protected $_m_retryInterval;
        protected $_m_expireLimit;
        protected $_m_minimumTtl;
        public function class() { return $this->_m_class; }
        public function timeToLive() { return $this->_m_timeToLive; }
        public function dataLength() { return $this->_m_dataLength; }
        public function primaryNameServer() { return $this->_m_primaryNameServer; }
        public function reponsibleAuthority() { return $this->_m_reponsibleAuthority; }
        public function serialNumber() { return $this->_m_serialNumber; }
        public function refreshInterval() { return $this->_m_refreshInterval; }
        public function retryInterval() { return $this->_m_retryInterval; }
        public function expireLimit() { return $this->_m_expireLimit; }
        public function minimumTtl() { return $this->_m_minimumTtl; }
    }
}

namespace DnsPacket {
    class RrType {
        const A = 1;
        const NS = 2;
        const CNAME = 5;
        const SOA = 6;
        const AAAA = 28;
        const OPT = 41;
        const DS = 43;
        const RRSIG = 46;
        const KEY = 48;
        const NSEC3 = 50;
    }
}
