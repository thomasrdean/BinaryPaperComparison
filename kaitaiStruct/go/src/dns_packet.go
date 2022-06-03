// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

import "github.com/kaitai-io/kaitai_struct_go_runtime/kaitai"


type DnsPacket_RrType int
const (
	DnsPacket_RrType__A DnsPacket_RrType = 1
	DnsPacket_RrType__Ns DnsPacket_RrType = 2
	DnsPacket_RrType__Cname DnsPacket_RrType = 5
	DnsPacket_RrType__Soa DnsPacket_RrType = 6
	DnsPacket_RrType__Aaaa DnsPacket_RrType = 28
	DnsPacket_RrType__Opt DnsPacket_RrType = 41
	DnsPacket_RrType__Ds DnsPacket_RrType = 43
	DnsPacket_RrType__Rrsig DnsPacket_RrType = 46
	DnsPacket_RrType__Key DnsPacket_RrType = 48
	DnsPacket_RrType__Nsec3 DnsPacket_RrType = 50
)
type DnsPacket struct {
	TransactionId uint16
	Flags uint16
	Qdcount uint16
	Ancount uint16
	Nscount uint16
	Arcount uint16
	Queries []*DnsPacket_Query
	Answers []*DnsPacket_ResourceRecord
	Authorities []*DnsPacket_ResourceRecord
	Additionals []*DnsPacket_ResourceRecord
	_io *kaitai.Stream
	_root *DnsPacket
	_parent interface{}
}
func NewDnsPacket() *DnsPacket {
	return &DnsPacket{
	}
}

func (this *DnsPacket) Read(io *kaitai.Stream, parent interface{}, root *DnsPacket) (err error) {
	this._io = io
	this._parent = parent
	this._root = root

	tmp1, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.TransactionId = uint16(tmp1)
	tmp2, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.Flags = uint16(tmp2)
	tmp3, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.Qdcount = uint16(tmp3)
	tmp4, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.Ancount = uint16(tmp4)
	tmp5, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.Nscount = uint16(tmp5)
	tmp6, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.Arcount = uint16(tmp6)
	this.Queries = make([]*DnsPacket_Query, this.Qdcount)
	for i := range this.Queries {
		tmp7 := NewDnsPacket_Query()
		err = tmp7.Read(this._io, this, this._root)
		if err != nil {
			return err
		}
		this.Queries[i] = tmp7
	}
	this.Answers = make([]*DnsPacket_ResourceRecord, this.Ancount)
	for i := range this.Answers {
		tmp8 := NewDnsPacket_ResourceRecord()
		err = tmp8.Read(this._io, this, this._root)
		if err != nil {
			return err
		}
		this.Answers[i] = tmp8
	}
	this.Authorities = make([]*DnsPacket_ResourceRecord, this.Nscount)
	for i := range this.Authorities {
		tmp9 := NewDnsPacket_ResourceRecord()
		err = tmp9.Read(this._io, this, this._root)
		if err != nil {
			return err
		}
		this.Authorities[i] = tmp9
	}
	this.Additionals = make([]*DnsPacket_ResourceRecord, this.Arcount)
	for i := range this.Additionals {
		tmp10 := NewDnsPacket_ResourceRecord()
		err = tmp10.Read(this._io, this, this._root)
		if err != nil {
			return err
		}
		this.Additionals[i] = tmp10
	}
	return err
}
type DnsPacket_Map struct {
	MapNum uint8
	Length uint8
	MapBits string
	_io *kaitai.Stream
	_root *DnsPacket
	_parent *DnsPacket_RrBodyNsec3
}
func NewDnsPacket_Map() *DnsPacket_Map {
	return &DnsPacket_Map{
	}
}

func (this *DnsPacket_Map) Read(io *kaitai.Stream, parent *DnsPacket_RrBodyNsec3, root *DnsPacket) (err error) {
	this._io = io
	this._parent = parent
	this._root = root

	tmp11, err := this._io.ReadU1()
	if err != nil {
		return err
	}
	this.MapNum = tmp11
	tmp12, err := this._io.ReadU1()
	if err != nil {
		return err
	}
	this.Length = tmp12
	tmp13, err := this._io.ReadBytes(int(this.Length))
	if err != nil {
		return err
	}
	tmp13 = tmp13
	this.MapBits = string(tmp13)
	return err
}
type DnsPacket_ResourceRecord struct {
	Name *DnsPacket_Domain
	Type DnsPacket_RrType
	Body interface{}
	_io *kaitai.Stream
	_root *DnsPacket
	_parent *DnsPacket
}
func NewDnsPacket_ResourceRecord() *DnsPacket_ResourceRecord {
	return &DnsPacket_ResourceRecord{
	}
}

func (this *DnsPacket_ResourceRecord) Read(io *kaitai.Stream, parent *DnsPacket, root *DnsPacket) (err error) {
	this._io = io
	this._parent = parent
	this._root = root

	tmp14 := NewDnsPacket_Domain()
	err = tmp14.Read(this._io, this, this._root)
	if err != nil {
		return err
	}
	this.Name = tmp14
	tmp15, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.Type = DnsPacket_RrType(tmp15)
	switch (this.Type) {
	case DnsPacket_RrType__A:
		tmp16 := NewDnsPacket_RrBodyA()
		err = tmp16.Read(this._io, this, this._root)
		if err != nil {
			return err
		}
		this.Body = tmp16
	case DnsPacket_RrType__Ds:
		tmp17 := NewDnsPacket_RrBodyDs()
		err = tmp17.Read(this._io, this, this._root)
		if err != nil {
			return err
		}
		this.Body = tmp17
	case DnsPacket_RrType__Ns:
		tmp18 := NewDnsPacket_RrBodyNs()
		err = tmp18.Read(this._io, this, this._root)
		if err != nil {
			return err
		}
		this.Body = tmp18
	case DnsPacket_RrType__Key:
		tmp19 := NewDnsPacket_RrBodyKey()
		err = tmp19.Read(this._io, this, this._root)
		if err != nil {
			return err
		}
		this.Body = tmp19
	case DnsPacket_RrType__Cname:
		tmp20 := NewDnsPacket_RrBodyCname()
		err = tmp20.Read(this._io, this, this._root)
		if err != nil {
			return err
		}
		this.Body = tmp20
	case DnsPacket_RrType__Opt:
		tmp21 := NewDnsPacket_RrBodyOpt()
		err = tmp21.Read(this._io, this, this._root)
		if err != nil {
			return err
		}
		this.Body = tmp21
	case DnsPacket_RrType__Rrsig:
		tmp22 := NewDnsPacket_RrBodyRrsig()
		err = tmp22.Read(this._io, this, this._root)
		if err != nil {
			return err
		}
		this.Body = tmp22
	case DnsPacket_RrType__Nsec3:
		tmp23 := NewDnsPacket_RrBodyNsec3()
		err = tmp23.Read(this._io, this, this._root)
		if err != nil {
			return err
		}
		this.Body = tmp23
	case DnsPacket_RrType__Aaaa:
		tmp24 := NewDnsPacket_RrBodyAaaa()
		err = tmp24.Read(this._io, this, this._root)
		if err != nil {
			return err
		}
		this.Body = tmp24
	case DnsPacket_RrType__Soa:
		tmp25 := NewDnsPacket_RrBodySoa()
		err = tmp25.Read(this._io, this, this._root)
		if err != nil {
			return err
		}
		this.Body = tmp25
	}
	return err
}
type DnsPacket_RrBodyOpt struct {
	UdpPayloadSize uint16
	HigherBitsInExtendedRcode uint8
	Edns0version uint8
	Z uint16
	DataLength uint16
	_io *kaitai.Stream
	_root *DnsPacket
	_parent *DnsPacket_ResourceRecord
}
func NewDnsPacket_RrBodyOpt() *DnsPacket_RrBodyOpt {
	return &DnsPacket_RrBodyOpt{
	}
}

func (this *DnsPacket_RrBodyOpt) Read(io *kaitai.Stream, parent *DnsPacket_ResourceRecord, root *DnsPacket) (err error) {
	this._io = io
	this._parent = parent
	this._root = root

	tmp26, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.UdpPayloadSize = uint16(tmp26)
	tmp27, err := this._io.ReadU1()
	if err != nil {
		return err
	}
	this.HigherBitsInExtendedRcode = tmp27
	tmp28, err := this._io.ReadU1()
	if err != nil {
		return err
	}
	this.Edns0version = tmp28
	tmp29, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.Z = uint16(tmp29)
	tmp30, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.DataLength = uint16(tmp30)
	return err
}
type DnsPacket_RrBodyKey struct {
	Class uint16
	_io *kaitai.Stream
	_root *DnsPacket
	_parent *DnsPacket_ResourceRecord
}
func NewDnsPacket_RrBodyKey() *DnsPacket_RrBodyKey {
	return &DnsPacket_RrBodyKey{
	}
}

func (this *DnsPacket_RrBodyKey) Read(io *kaitai.Stream, parent *DnsPacket_ResourceRecord, root *DnsPacket) (err error) {
	this._io = io
	this._parent = parent
	this._root = root

	tmp31, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.Class = uint16(tmp31)
	return err
}
type DnsPacket_Domain struct {
	Name []*DnsPacket_Word
	_io *kaitai.Stream
	_root *DnsPacket
	_parent interface{}
}
func NewDnsPacket_Domain() *DnsPacket_Domain {
	return &DnsPacket_Domain{
	}
}

func (this *DnsPacket_Domain) Read(io *kaitai.Stream, parent interface{}, root *DnsPacket) (err error) {
	this._io = io
	this._parent = parent
	this._root = root

	for i := 1;; i++ {
		tmp32 := NewDnsPacket_Word()
		err = tmp32.Read(this._io, this, this._root)
		if err != nil {
			return err
		}
		_it := tmp32
		this.Name = append(this.Name, _it)
		if  ((_it.Length == 0) || (_it.Length >= 192))  {
			break
		}
	}
	return err
}
type DnsPacket_Ipv6Address struct {
	IpV6 []byte
	_io *kaitai.Stream
	_root *DnsPacket
	_parent *DnsPacket_RrBodyAaaa
}
func NewDnsPacket_Ipv6Address() *DnsPacket_Ipv6Address {
	return &DnsPacket_Ipv6Address{
	}
}

func (this *DnsPacket_Ipv6Address) Read(io *kaitai.Stream, parent *DnsPacket_RrBodyAaaa, root *DnsPacket) (err error) {
	this._io = io
	this._parent = parent
	this._root = root

	tmp33, err := this._io.ReadBytes(int(16))
	if err != nil {
		return err
	}
	tmp33 = tmp33
	this.IpV6 = tmp33
	return err
}
type DnsPacket_Query struct {
	Name *DnsPacket_Domain
	Type DnsPacket_RrType
	QueryClass uint16
	_io *kaitai.Stream
	_root *DnsPacket
	_parent *DnsPacket
}
func NewDnsPacket_Query() *DnsPacket_Query {
	return &DnsPacket_Query{
	}
}

func (this *DnsPacket_Query) Read(io *kaitai.Stream, parent *DnsPacket, root *DnsPacket) (err error) {
	this._io = io
	this._parent = parent
	this._root = root

	tmp34 := NewDnsPacket_Domain()
	err = tmp34.Read(this._io, this, this._root)
	if err != nil {
		return err
	}
	this.Name = tmp34
	tmp35, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.Type = DnsPacket_RrType(tmp35)
	tmp36, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.QueryClass = uint16(tmp36)
	return err
}
type DnsPacket_RrBodyRrsig struct {
	Class uint16
	TimeToLive uint32
	DataLength uint16
	TypeCov uint16
	Alg uint8
	Labels uint8
	OrigTimeToLive uint32
	SigExp uint32
	SigInception uint32
	KeyTag uint16
	SignName *DnsPacket_Domain
	Signature string
	_io *kaitai.Stream
	_root *DnsPacket
	_parent *DnsPacket_ResourceRecord
}
func NewDnsPacket_RrBodyRrsig() *DnsPacket_RrBodyRrsig {
	return &DnsPacket_RrBodyRrsig{
	}
}

func (this *DnsPacket_RrBodyRrsig) Read(io *kaitai.Stream, parent *DnsPacket_ResourceRecord, root *DnsPacket) (err error) {
	this._io = io
	this._parent = parent
	this._root = root

	tmp37, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.Class = uint16(tmp37)
	tmp38, err := this._io.ReadU4be()
	if err != nil {
		return err
	}
	this.TimeToLive = uint32(tmp38)
	tmp39, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.DataLength = uint16(tmp39)
	tmp40, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.TypeCov = uint16(tmp40)
	tmp41, err := this._io.ReadU1()
	if err != nil {
		return err
	}
	this.Alg = tmp41
	tmp42, err := this._io.ReadU1()
	if err != nil {
		return err
	}
	this.Labels = tmp42
	tmp43, err := this._io.ReadU4be()
	if err != nil {
		return err
	}
	this.OrigTimeToLive = uint32(tmp43)
	tmp44, err := this._io.ReadU4be()
	if err != nil {
		return err
	}
	this.SigExp = uint32(tmp44)
	tmp45, err := this._io.ReadU4be()
	if err != nil {
		return err
	}
	this.SigInception = uint32(tmp45)
	tmp46, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.KeyTag = uint16(tmp46)
	tmp47 := NewDnsPacket_Domain()
	err = tmp47.Read(this._io, this, this._root)
	if err != nil {
		return err
	}
	this.SignName = tmp47
	tmp48, err := this._io.ReadBytes(int(256))
	if err != nil {
		return err
	}
	tmp48 = tmp48
	this.Signature = string(tmp48)
	return err
}
type DnsPacket_Ipv4Address struct {
	Ip []byte
	_io *kaitai.Stream
	_root *DnsPacket
	_parent *DnsPacket_RrBodyA
}
func NewDnsPacket_Ipv4Address() *DnsPacket_Ipv4Address {
	return &DnsPacket_Ipv4Address{
	}
}

func (this *DnsPacket_Ipv4Address) Read(io *kaitai.Stream, parent *DnsPacket_RrBodyA, root *DnsPacket) (err error) {
	this._io = io
	this._parent = parent
	this._root = root

	tmp49, err := this._io.ReadBytes(int(4))
	if err != nil {
		return err
	}
	tmp49 = tmp49
	this.Ip = tmp49
	return err
}
type DnsPacket_RrBodyCname struct {
	Class uint16
	TimeToLive uint32
	DataLength uint16
	Cname *DnsPacket_Domain
	_io *kaitai.Stream
	_root *DnsPacket
	_parent *DnsPacket_ResourceRecord
}
func NewDnsPacket_RrBodyCname() *DnsPacket_RrBodyCname {
	return &DnsPacket_RrBodyCname{
	}
}

func (this *DnsPacket_RrBodyCname) Read(io *kaitai.Stream, parent *DnsPacket_ResourceRecord, root *DnsPacket) (err error) {
	this._io = io
	this._parent = parent
	this._root = root

	tmp50, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.Class = uint16(tmp50)
	tmp51, err := this._io.ReadU4be()
	if err != nil {
		return err
	}
	this.TimeToLive = uint32(tmp51)
	tmp52, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.DataLength = uint16(tmp52)
	tmp53 := NewDnsPacket_Domain()
	err = tmp53.Read(this._io, this, this._root)
	if err != nil {
		return err
	}
	this.Cname = tmp53
	return err
}
type DnsPacket_RrBodyAaaa struct {
	Class uint16
	TimeToLive uint32
	DataLength uint16
	Address *DnsPacket_Ipv6Address
	_io *kaitai.Stream
	_root *DnsPacket
	_parent *DnsPacket_ResourceRecord
}
func NewDnsPacket_RrBodyAaaa() *DnsPacket_RrBodyAaaa {
	return &DnsPacket_RrBodyAaaa{
	}
}

func (this *DnsPacket_RrBodyAaaa) Read(io *kaitai.Stream, parent *DnsPacket_ResourceRecord, root *DnsPacket) (err error) {
	this._io = io
	this._parent = parent
	this._root = root

	tmp54, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.Class = uint16(tmp54)
	tmp55, err := this._io.ReadU4be()
	if err != nil {
		return err
	}
	this.TimeToLive = uint32(tmp55)
	tmp56, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.DataLength = uint16(tmp56)
	tmp57 := NewDnsPacket_Ipv6Address()
	err = tmp57.Read(this._io, this, this._root)
	if err != nil {
		return err
	}
	this.Address = tmp57
	return err
}
type DnsPacket_RrBodyNs struct {
	Class uint16
	TimeToLive uint32
	DataLength uint16
	NameServer *DnsPacket_Domain
	_io *kaitai.Stream
	_root *DnsPacket
	_parent *DnsPacket_ResourceRecord
}
func NewDnsPacket_RrBodyNs() *DnsPacket_RrBodyNs {
	return &DnsPacket_RrBodyNs{
	}
}

func (this *DnsPacket_RrBodyNs) Read(io *kaitai.Stream, parent *DnsPacket_ResourceRecord, root *DnsPacket) (err error) {
	this._io = io
	this._parent = parent
	this._root = root

	tmp58, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.Class = uint16(tmp58)
	tmp59, err := this._io.ReadU4be()
	if err != nil {
		return err
	}
	this.TimeToLive = uint32(tmp59)
	tmp60, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.DataLength = uint16(tmp60)
	tmp61 := NewDnsPacket_Domain()
	err = tmp61.Read(this._io, this, this._root)
	if err != nil {
		return err
	}
	this.NameServer = tmp61
	return err
}
type DnsPacket_RrBodyDs struct {
	Class uint16
	TimeToLive uint32
	DataLength uint16
	Keyid uint16
	Alg uint8
	DigestType uint8
	Digest string
	_io *kaitai.Stream
	_root *DnsPacket
	_parent *DnsPacket_ResourceRecord
}
func NewDnsPacket_RrBodyDs() *DnsPacket_RrBodyDs {
	return &DnsPacket_RrBodyDs{
	}
}

func (this *DnsPacket_RrBodyDs) Read(io *kaitai.Stream, parent *DnsPacket_ResourceRecord, root *DnsPacket) (err error) {
	this._io = io
	this._parent = parent
	this._root = root

	tmp62, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.Class = uint16(tmp62)
	tmp63, err := this._io.ReadU4be()
	if err != nil {
		return err
	}
	this.TimeToLive = uint32(tmp63)
	tmp64, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.DataLength = uint16(tmp64)
	tmp65, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.Keyid = uint16(tmp65)
	tmp66, err := this._io.ReadU1()
	if err != nil {
		return err
	}
	this.Alg = tmp66
	tmp67, err := this._io.ReadU1()
	if err != nil {
		return err
	}
	this.DigestType = tmp67
	tmp68, err := this._io.ReadBytes(int(32))
	if err != nil {
		return err
	}
	tmp68 = tmp68
	this.Digest = string(tmp68)
	return err
}
type DnsPacket_RrBodyNsec3 struct {
	Class uint16
	TimeToLive uint32
	DataLength uint16
	Alg uint8
	Flags uint8
	Iterations uint16
	SaltLength uint8
	HashLength uint8
	NextHash string
	TypeMap *DnsPacket_Map
	_io *kaitai.Stream
	_root *DnsPacket
	_parent *DnsPacket_ResourceRecord
}
func NewDnsPacket_RrBodyNsec3() *DnsPacket_RrBodyNsec3 {
	return &DnsPacket_RrBodyNsec3{
	}
}

func (this *DnsPacket_RrBodyNsec3) Read(io *kaitai.Stream, parent *DnsPacket_ResourceRecord, root *DnsPacket) (err error) {
	this._io = io
	this._parent = parent
	this._root = root

	tmp69, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.Class = uint16(tmp69)
	tmp70, err := this._io.ReadU4be()
	if err != nil {
		return err
	}
	this.TimeToLive = uint32(tmp70)
	tmp71, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.DataLength = uint16(tmp71)
	tmp72, err := this._io.ReadU1()
	if err != nil {
		return err
	}
	this.Alg = tmp72
	tmp73, err := this._io.ReadU1()
	if err != nil {
		return err
	}
	this.Flags = tmp73
	tmp74, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.Iterations = uint16(tmp74)
	tmp75, err := this._io.ReadU1()
	if err != nil {
		return err
	}
	this.SaltLength = tmp75
	tmp76, err := this._io.ReadU1()
	if err != nil {
		return err
	}
	this.HashLength = tmp76
	tmp77, err := this._io.ReadBytes(int(this.HashLength))
	if err != nil {
		return err
	}
	tmp77 = tmp77
	this.NextHash = string(tmp77)
	tmp78 := NewDnsPacket_Map()
	err = tmp78.Read(this._io, this, this._root)
	if err != nil {
		return err
	}
	this.TypeMap = tmp78
	return err
}
type DnsPacket_RrBodyA struct {
	Class uint16
	TimeToLive uint32
	DataLength uint16
	Address *DnsPacket_Ipv4Address
	_io *kaitai.Stream
	_root *DnsPacket
	_parent *DnsPacket_ResourceRecord
}
func NewDnsPacket_RrBodyA() *DnsPacket_RrBodyA {
	return &DnsPacket_RrBodyA{
	}
}

func (this *DnsPacket_RrBodyA) Read(io *kaitai.Stream, parent *DnsPacket_ResourceRecord, root *DnsPacket) (err error) {
	this._io = io
	this._parent = parent
	this._root = root

	tmp79, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.Class = uint16(tmp79)
	tmp80, err := this._io.ReadU4be()
	if err != nil {
		return err
	}
	this.TimeToLive = uint32(tmp80)
	tmp81, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.DataLength = uint16(tmp81)
	tmp82 := NewDnsPacket_Ipv4Address()
	err = tmp82.Read(this._io, this, this._root)
	if err != nil {
		return err
	}
	this.Address = tmp82
	return err
}
type DnsPacket_Word struct {
	Length uint8
	Ref uint8
	Letters string
	_io *kaitai.Stream
	_root *DnsPacket
	_parent *DnsPacket_Domain
	_f_isRef bool
	isRef bool
}
func NewDnsPacket_Word() *DnsPacket_Word {
	return &DnsPacket_Word{
	}
}

func (this *DnsPacket_Word) Read(io *kaitai.Stream, parent *DnsPacket_Domain, root *DnsPacket) (err error) {
	this._io = io
	this._parent = parent
	this._root = root

	tmp83, err := this._io.ReadU1()
	if err != nil {
		return err
	}
	this.Length = tmp83
	tmp84, err := this.IsRef()
	if err != nil {
		return err
	}
	if (tmp84) {
		tmp85, err := this._io.ReadU1()
		if err != nil {
			return err
		}
		this.Ref = tmp85
	}
	tmp86, err := this.IsRef()
	if err != nil {
		return err
	}
	if (!(tmp86)) {
		tmp87, err := this._io.ReadBytes(int(this.Length))
		if err != nil {
			return err
		}
		tmp87 = tmp87
		this.Letters = string(tmp87)
	}
	return err
}
func (this *DnsPacket_Word) IsRef() (v bool, err error) {
	if (this._f_isRef) {
		return this.isRef, nil
	}
	this.isRef = bool(this.Length == 192)
	this._f_isRef = true
	return this.isRef, nil
}
type DnsPacket_RrBodySoa struct {
	Class uint16
	TimeToLive uint32
	DataLength uint16
	PrimaryNameServer *DnsPacket_Domain
	ReponsibleAuthority *DnsPacket_Domain
	SerialNumber uint32
	RefreshInterval uint32
	RetryInterval uint32
	ExpireLimit uint32
	MinimumTtl uint32
	_io *kaitai.Stream
	_root *DnsPacket
	_parent *DnsPacket_ResourceRecord
}
func NewDnsPacket_RrBodySoa() *DnsPacket_RrBodySoa {
	return &DnsPacket_RrBodySoa{
	}
}

func (this *DnsPacket_RrBodySoa) Read(io *kaitai.Stream, parent *DnsPacket_ResourceRecord, root *DnsPacket) (err error) {
	this._io = io
	this._parent = parent
	this._root = root

	tmp88, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.Class = uint16(tmp88)
	tmp89, err := this._io.ReadU4be()
	if err != nil {
		return err
	}
	this.TimeToLive = uint32(tmp89)
	tmp90, err := this._io.ReadU2be()
	if err != nil {
		return err
	}
	this.DataLength = uint16(tmp90)
	tmp91 := NewDnsPacket_Domain()
	err = tmp91.Read(this._io, this, this._root)
	if err != nil {
		return err
	}
	this.PrimaryNameServer = tmp91
	tmp92 := NewDnsPacket_Domain()
	err = tmp92.Read(this._io, this, this._root)
	if err != nil {
		return err
	}
	this.ReponsibleAuthority = tmp92
	tmp93, err := this._io.ReadU4be()
	if err != nil {
		return err
	}
	this.SerialNumber = uint32(tmp93)
	tmp94, err := this._io.ReadU4be()
	if err != nil {
		return err
	}
	this.RefreshInterval = uint32(tmp94)
	tmp95, err := this._io.ReadU4be()
	if err != nil {
		return err
	}
	this.RetryInterval = uint32(tmp95)
	tmp96, err := this._io.ReadU4be()
	if err != nil {
		return err
	}
	this.ExpireLimit = uint32(tmp96)
	tmp97, err := this._io.ReadU4be()
	if err != nil {
		return err
	}
	this.MinimumTtl = uint32(tmp97)
	return err
}
