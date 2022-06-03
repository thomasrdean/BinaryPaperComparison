# This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

use strict;
use warnings;
use IO::KaitaiStruct 0.009_000;
use Encode;

########################################################################
package DnsPacket;

our @ISA = 'IO::KaitaiStruct::Struct';

sub from_file {
    my ($class, $filename) = @_;
    my $fd;

    open($fd, '<', $filename) or return undef;
    binmode($fd);
    return new($class, IO::KaitaiStruct::Stream->new($fd));
}

our $RR_TYPE_A = 1;
our $RR_TYPE_NS = 2;
our $RR_TYPE_CNAME = 5;
our $RR_TYPE_SOA = 6;
our $RR_TYPE_AAAA = 28;
our $RR_TYPE_OPT = 41;
our $RR_TYPE_DS = 43;
our $RR_TYPE_RRSIG = 46;
our $RR_TYPE_KEY = 48;
our $RR_TYPE_NSEC3 = 50;

sub new {
    my ($class, $_io, $_parent, $_root) = @_;
    my $self = IO::KaitaiStruct::Struct->new($_io);

    bless $self, $class;
    $self->{_parent} = $_parent;
    $self->{_root} = $_root || $self;;

    $self->_read();

    return $self;
}

sub _read {
    my ($self) = @_;

    $self->{transaction_id} = $self->{_io}->read_u2be();
    $self->{flags} = $self->{_io}->read_u2be();
    $self->{qdcount} = $self->{_io}->read_u2be();
    $self->{ancount} = $self->{_io}->read_u2be();
    $self->{nscount} = $self->{_io}->read_u2be();
    $self->{arcount} = $self->{_io}->read_u2be();
    $self->{queries} = ();
    my $n_queries = $self->qdcount();
    for (my $i = 0; $i < $n_queries; $i++) {
        $self->{queries}[$i] = DnsPacket::Query->new($self->{_io}, $self, $self->{_root});
    }
    $self->{answers} = ();
    my $n_answers = $self->ancount();
    for (my $i = 0; $i < $n_answers; $i++) {
        $self->{answers}[$i] = DnsPacket::ResourceRecord->new($self->{_io}, $self, $self->{_root});
    }
    $self->{authorities} = ();
    my $n_authorities = $self->nscount();
    for (my $i = 0; $i < $n_authorities; $i++) {
        $self->{authorities}[$i] = DnsPacket::ResourceRecord->new($self->{_io}, $self, $self->{_root});
    }
    $self->{additionals} = ();
    my $n_additionals = $self->arcount();
    for (my $i = 0; $i < $n_additionals; $i++) {
        $self->{additionals}[$i] = DnsPacket::ResourceRecord->new($self->{_io}, $self, $self->{_root});
    }
}

sub transaction_id {
    my ($self) = @_;
    return $self->{transaction_id};
}

sub flags {
    my ($self) = @_;
    return $self->{flags};
}

sub qdcount {
    my ($self) = @_;
    return $self->{qdcount};
}

sub ancount {
    my ($self) = @_;
    return $self->{ancount};
}

sub nscount {
    my ($self) = @_;
    return $self->{nscount};
}

sub arcount {
    my ($self) = @_;
    return $self->{arcount};
}

sub queries {
    my ($self) = @_;
    return $self->{queries};
}

sub answers {
    my ($self) = @_;
    return $self->{answers};
}

sub authorities {
    my ($self) = @_;
    return $self->{authorities};
}

sub additionals {
    my ($self) = @_;
    return $self->{additionals};
}

########################################################################
package DnsPacket::Map;

our @ISA = 'IO::KaitaiStruct::Struct';

sub from_file {
    my ($class, $filename) = @_;
    my $fd;

    open($fd, '<', $filename) or return undef;
    binmode($fd);
    return new($class, IO::KaitaiStruct::Stream->new($fd));
}

sub new {
    my ($class, $_io, $_parent, $_root) = @_;
    my $self = IO::KaitaiStruct::Struct->new($_io);

    bless $self, $class;
    $self->{_parent} = $_parent;
    $self->{_root} = $_root || $self;;

    $self->_read();

    return $self;
}

sub _read {
    my ($self) = @_;

    $self->{map_num} = $self->{_io}->read_u1();
    $self->{length} = $self->{_io}->read_u1();
    $self->{map_bits} = Encode::decode("utf-8", $self->{_io}->read_bytes($self->length()));
}

sub map_num {
    my ($self) = @_;
    return $self->{map_num};
}

sub length {
    my ($self) = @_;
    return $self->{length};
}

sub map_bits {
    my ($self) = @_;
    return $self->{map_bits};
}

########################################################################
package DnsPacket::ResourceRecord;

our @ISA = 'IO::KaitaiStruct::Struct';

sub from_file {
    my ($class, $filename) = @_;
    my $fd;

    open($fd, '<', $filename) or return undef;
    binmode($fd);
    return new($class, IO::KaitaiStruct::Stream->new($fd));
}

sub new {
    my ($class, $_io, $_parent, $_root) = @_;
    my $self = IO::KaitaiStruct::Struct->new($_io);

    bless $self, $class;
    $self->{_parent} = $_parent;
    $self->{_root} = $_root || $self;;

    $self->_read();

    return $self;
}

sub _read {
    my ($self) = @_;

    $self->{name} = DnsPacket::Domain->new($self->{_io}, $self, $self->{_root});
    $self->{type} = $self->{_io}->read_u2be();
    my $_on = $self->type();
    if ($_on == $DnsPacket::RR_TYPE_A) {
        $self->{body} = DnsPacket::RrBodyA->new($self->{_io}, $self, $self->{_root});
    }
    elsif ($_on == $DnsPacket::RR_TYPE_DS) {
        $self->{body} = DnsPacket::RrBodyDs->new($self->{_io}, $self, $self->{_root});
    }
    elsif ($_on == $DnsPacket::RR_TYPE_NS) {
        $self->{body} = DnsPacket::RrBodyNs->new($self->{_io}, $self, $self->{_root});
    }
    elsif ($_on == $DnsPacket::RR_TYPE_KEY) {
        $self->{body} = DnsPacket::RrBodyKey->new($self->{_io}, $self, $self->{_root});
    }
    elsif ($_on == $DnsPacket::RR_TYPE_CNAME) {
        $self->{body} = DnsPacket::RrBodyCname->new($self->{_io}, $self, $self->{_root});
    }
    elsif ($_on == $DnsPacket::RR_TYPE_OPT) {
        $self->{body} = DnsPacket::RrBodyOpt->new($self->{_io}, $self, $self->{_root});
    }
    elsif ($_on == $DnsPacket::RR_TYPE_RRSIG) {
        $self->{body} = DnsPacket::RrBodyRrsig->new($self->{_io}, $self, $self->{_root});
    }
    elsif ($_on == $DnsPacket::RR_TYPE_NSEC3) {
        $self->{body} = DnsPacket::RrBodyNsec3->new($self->{_io}, $self, $self->{_root});
    }
    elsif ($_on == $DnsPacket::RR_TYPE_AAAA) {
        $self->{body} = DnsPacket::RrBodyAaaa->new($self->{_io}, $self, $self->{_root});
    }
    elsif ($_on == $DnsPacket::RR_TYPE_SOA) {
        $self->{body} = DnsPacket::RrBodySoa->new($self->{_io}, $self, $self->{_root});
    }
}

sub name {
    my ($self) = @_;
    return $self->{name};
}

sub type {
    my ($self) = @_;
    return $self->{type};
}

sub body {
    my ($self) = @_;
    return $self->{body};
}

########################################################################
package DnsPacket::RrBodyOpt;

our @ISA = 'IO::KaitaiStruct::Struct';

sub from_file {
    my ($class, $filename) = @_;
    my $fd;

    open($fd, '<', $filename) or return undef;
    binmode($fd);
    return new($class, IO::KaitaiStruct::Stream->new($fd));
}

sub new {
    my ($class, $_io, $_parent, $_root) = @_;
    my $self = IO::KaitaiStruct::Struct->new($_io);

    bless $self, $class;
    $self->{_parent} = $_parent;
    $self->{_root} = $_root || $self;;

    $self->_read();

    return $self;
}

sub _read {
    my ($self) = @_;

    $self->{udp_payload_size} = $self->{_io}->read_u2be();
    $self->{higher_bits_in_extended_rcode} = $self->{_io}->read_u1();
    $self->{edns0version} = $self->{_io}->read_u1();
    $self->{z} = $self->{_io}->read_u2be();
    $self->{data_length} = $self->{_io}->read_u2be();
}

sub udp_payload_size {
    my ($self) = @_;
    return $self->{udp_payload_size};
}

sub higher_bits_in_extended_rcode {
    my ($self) = @_;
    return $self->{higher_bits_in_extended_rcode};
}

sub edns0version {
    my ($self) = @_;
    return $self->{edns0version};
}

sub z {
    my ($self) = @_;
    return $self->{z};
}

sub data_length {
    my ($self) = @_;
    return $self->{data_length};
}

########################################################################
package DnsPacket::RrBodyKey;

our @ISA = 'IO::KaitaiStruct::Struct';

sub from_file {
    my ($class, $filename) = @_;
    my $fd;

    open($fd, '<', $filename) or return undef;
    binmode($fd);
    return new($class, IO::KaitaiStruct::Stream->new($fd));
}

sub new {
    my ($class, $_io, $_parent, $_root) = @_;
    my $self = IO::KaitaiStruct::Struct->new($_io);

    bless $self, $class;
    $self->{_parent} = $_parent;
    $self->{_root} = $_root || $self;;

    $self->_read();

    return $self;
}

sub _read {
    my ($self) = @_;

    $self->{class_} = $self->{_io}->read_u2be();
}

sub class_ {
    my ($self) = @_;
    return $self->{class_};
}

########################################################################
package DnsPacket::Domain;

our @ISA = 'IO::KaitaiStruct::Struct';

sub from_file {
    my ($class, $filename) = @_;
    my $fd;

    open($fd, '<', $filename) or return undef;
    binmode($fd);
    return new($class, IO::KaitaiStruct::Stream->new($fd));
}

sub new {
    my ($class, $_io, $_parent, $_root) = @_;
    my $self = IO::KaitaiStruct::Struct->new($_io);

    bless $self, $class;
    $self->{_parent} = $_parent;
    $self->{_root} = $_root || $self;;

    $self->_read();

    return $self;
}

sub _read {
    my ($self) = @_;

    $self->{name} = ();
    do {
        $_ = DnsPacket::Word->new($self->{_io}, $self, $self->{_root});
        push @{$self->{name}}, $_;
    } until ( (($_->length() == 0) || ($_->length() >= 192)) );
}

sub name {
    my ($self) = @_;
    return $self->{name};
}

########################################################################
package DnsPacket::Ipv6Address;

our @ISA = 'IO::KaitaiStruct::Struct';

sub from_file {
    my ($class, $filename) = @_;
    my $fd;

    open($fd, '<', $filename) or return undef;
    binmode($fd);
    return new($class, IO::KaitaiStruct::Stream->new($fd));
}

sub new {
    my ($class, $_io, $_parent, $_root) = @_;
    my $self = IO::KaitaiStruct::Struct->new($_io);

    bless $self, $class;
    $self->{_parent} = $_parent;
    $self->{_root} = $_root || $self;;

    $self->_read();

    return $self;
}

sub _read {
    my ($self) = @_;

    $self->{ip_v6} = $self->{_io}->read_bytes(16);
}

sub ip_v6 {
    my ($self) = @_;
    return $self->{ip_v6};
}

########################################################################
package DnsPacket::Query;

our @ISA = 'IO::KaitaiStruct::Struct';

sub from_file {
    my ($class, $filename) = @_;
    my $fd;

    open($fd, '<', $filename) or return undef;
    binmode($fd);
    return new($class, IO::KaitaiStruct::Stream->new($fd));
}

sub new {
    my ($class, $_io, $_parent, $_root) = @_;
    my $self = IO::KaitaiStruct::Struct->new($_io);

    bless $self, $class;
    $self->{_parent} = $_parent;
    $self->{_root} = $_root || $self;;

    $self->_read();

    return $self;
}

sub _read {
    my ($self) = @_;

    $self->{name} = DnsPacket::Domain->new($self->{_io}, $self, $self->{_root});
    $self->{type} = $self->{_io}->read_u2be();
    $self->{query_class} = $self->{_io}->read_u2be();
}

sub name {
    my ($self) = @_;
    return $self->{name};
}

sub type {
    my ($self) = @_;
    return $self->{type};
}

sub query_class {
    my ($self) = @_;
    return $self->{query_class};
}

########################################################################
package DnsPacket::RrBodyRrsig;

our @ISA = 'IO::KaitaiStruct::Struct';

sub from_file {
    my ($class, $filename) = @_;
    my $fd;

    open($fd, '<', $filename) or return undef;
    binmode($fd);
    return new($class, IO::KaitaiStruct::Stream->new($fd));
}

sub new {
    my ($class, $_io, $_parent, $_root) = @_;
    my $self = IO::KaitaiStruct::Struct->new($_io);

    bless $self, $class;
    $self->{_parent} = $_parent;
    $self->{_root} = $_root || $self;;

    $self->_read();

    return $self;
}

sub _read {
    my ($self) = @_;

    $self->{class_} = $self->{_io}->read_u2be();
    $self->{time_to_live} = $self->{_io}->read_u4be();
    $self->{data_length} = $self->{_io}->read_u2be();
    $self->{type_cov} = $self->{_io}->read_u2be();
    $self->{alg} = $self->{_io}->read_u1();
    $self->{labels} = $self->{_io}->read_u1();
    $self->{orig_time_to_live} = $self->{_io}->read_u4be();
    $self->{sig_exp} = $self->{_io}->read_u4be();
    $self->{sig_inception} = $self->{_io}->read_u4be();
    $self->{key_tag} = $self->{_io}->read_u2be();
    $self->{sign_name} = DnsPacket::Domain->new($self->{_io}, $self, $self->{_root});
    $self->{signature} = Encode::decode("utf-8", $self->{_io}->read_bytes(256));
}

sub class_ {
    my ($self) = @_;
    return $self->{class_};
}

sub time_to_live {
    my ($self) = @_;
    return $self->{time_to_live};
}

sub data_length {
    my ($self) = @_;
    return $self->{data_length};
}

sub type_cov {
    my ($self) = @_;
    return $self->{type_cov};
}

sub alg {
    my ($self) = @_;
    return $self->{alg};
}

sub labels {
    my ($self) = @_;
    return $self->{labels};
}

sub orig_time_to_live {
    my ($self) = @_;
    return $self->{orig_time_to_live};
}

sub sig_exp {
    my ($self) = @_;
    return $self->{sig_exp};
}

sub sig_inception {
    my ($self) = @_;
    return $self->{sig_inception};
}

sub key_tag {
    my ($self) = @_;
    return $self->{key_tag};
}

sub sign_name {
    my ($self) = @_;
    return $self->{sign_name};
}

sub signature {
    my ($self) = @_;
    return $self->{signature};
}

########################################################################
package DnsPacket::Ipv4Address;

our @ISA = 'IO::KaitaiStruct::Struct';

sub from_file {
    my ($class, $filename) = @_;
    my $fd;

    open($fd, '<', $filename) or return undef;
    binmode($fd);
    return new($class, IO::KaitaiStruct::Stream->new($fd));
}

sub new {
    my ($class, $_io, $_parent, $_root) = @_;
    my $self = IO::KaitaiStruct::Struct->new($_io);

    bless $self, $class;
    $self->{_parent} = $_parent;
    $self->{_root} = $_root || $self;;

    $self->_read();

    return $self;
}

sub _read {
    my ($self) = @_;

    $self->{ip} = $self->{_io}->read_bytes(4);
}

sub ip {
    my ($self) = @_;
    return $self->{ip};
}

########################################################################
package DnsPacket::RrBodyCname;

our @ISA = 'IO::KaitaiStruct::Struct';

sub from_file {
    my ($class, $filename) = @_;
    my $fd;

    open($fd, '<', $filename) or return undef;
    binmode($fd);
    return new($class, IO::KaitaiStruct::Stream->new($fd));
}

sub new {
    my ($class, $_io, $_parent, $_root) = @_;
    my $self = IO::KaitaiStruct::Struct->new($_io);

    bless $self, $class;
    $self->{_parent} = $_parent;
    $self->{_root} = $_root || $self;;

    $self->_read();

    return $self;
}

sub _read {
    my ($self) = @_;

    $self->{class_} = $self->{_io}->read_u2be();
    $self->{time_to_live} = $self->{_io}->read_u4be();
    $self->{data_length} = $self->{_io}->read_u2be();
    $self->{cname} = DnsPacket::Domain->new($self->{_io}, $self, $self->{_root});
}

sub class_ {
    my ($self) = @_;
    return $self->{class_};
}

sub time_to_live {
    my ($self) = @_;
    return $self->{time_to_live};
}

sub data_length {
    my ($self) = @_;
    return $self->{data_length};
}

sub cname {
    my ($self) = @_;
    return $self->{cname};
}

########################################################################
package DnsPacket::RrBodyAaaa;

our @ISA = 'IO::KaitaiStruct::Struct';

sub from_file {
    my ($class, $filename) = @_;
    my $fd;

    open($fd, '<', $filename) or return undef;
    binmode($fd);
    return new($class, IO::KaitaiStruct::Stream->new($fd));
}

sub new {
    my ($class, $_io, $_parent, $_root) = @_;
    my $self = IO::KaitaiStruct::Struct->new($_io);

    bless $self, $class;
    $self->{_parent} = $_parent;
    $self->{_root} = $_root || $self;;

    $self->_read();

    return $self;
}

sub _read {
    my ($self) = @_;

    $self->{class_} = $self->{_io}->read_u2be();
    $self->{time_to_live} = $self->{_io}->read_u4be();
    $self->{data_length} = $self->{_io}->read_u2be();
    $self->{address} = DnsPacket::Ipv6Address->new($self->{_io}, $self, $self->{_root});
}

sub class_ {
    my ($self) = @_;
    return $self->{class_};
}

sub time_to_live {
    my ($self) = @_;
    return $self->{time_to_live};
}

sub data_length {
    my ($self) = @_;
    return $self->{data_length};
}

sub address {
    my ($self) = @_;
    return $self->{address};
}

########################################################################
package DnsPacket::RrBodyNs;

our @ISA = 'IO::KaitaiStruct::Struct';

sub from_file {
    my ($class, $filename) = @_;
    my $fd;

    open($fd, '<', $filename) or return undef;
    binmode($fd);
    return new($class, IO::KaitaiStruct::Stream->new($fd));
}

sub new {
    my ($class, $_io, $_parent, $_root) = @_;
    my $self = IO::KaitaiStruct::Struct->new($_io);

    bless $self, $class;
    $self->{_parent} = $_parent;
    $self->{_root} = $_root || $self;;

    $self->_read();

    return $self;
}

sub _read {
    my ($self) = @_;

    $self->{class_} = $self->{_io}->read_u2be();
    $self->{time_to_live} = $self->{_io}->read_u4be();
    $self->{data_length} = $self->{_io}->read_u2be();
    $self->{name_server} = DnsPacket::Domain->new($self->{_io}, $self, $self->{_root});
}

sub class_ {
    my ($self) = @_;
    return $self->{class_};
}

sub time_to_live {
    my ($self) = @_;
    return $self->{time_to_live};
}

sub data_length {
    my ($self) = @_;
    return $self->{data_length};
}

sub name_server {
    my ($self) = @_;
    return $self->{name_server};
}

########################################################################
package DnsPacket::RrBodyDs;

our @ISA = 'IO::KaitaiStruct::Struct';

sub from_file {
    my ($class, $filename) = @_;
    my $fd;

    open($fd, '<', $filename) or return undef;
    binmode($fd);
    return new($class, IO::KaitaiStruct::Stream->new($fd));
}

sub new {
    my ($class, $_io, $_parent, $_root) = @_;
    my $self = IO::KaitaiStruct::Struct->new($_io);

    bless $self, $class;
    $self->{_parent} = $_parent;
    $self->{_root} = $_root || $self;;

    $self->_read();

    return $self;
}

sub _read {
    my ($self) = @_;

    $self->{class_} = $self->{_io}->read_u2be();
    $self->{time_to_live} = $self->{_io}->read_u4be();
    $self->{data_length} = $self->{_io}->read_u2be();
    $self->{keyid} = $self->{_io}->read_u2be();
    $self->{alg} = $self->{_io}->read_u1();
    $self->{digest_type} = $self->{_io}->read_u1();
    $self->{digest} = Encode::decode("utf-8", $self->{_io}->read_bytes(32));
}

sub class_ {
    my ($self) = @_;
    return $self->{class_};
}

sub time_to_live {
    my ($self) = @_;
    return $self->{time_to_live};
}

sub data_length {
    my ($self) = @_;
    return $self->{data_length};
}

sub keyid {
    my ($self) = @_;
    return $self->{keyid};
}

sub alg {
    my ($self) = @_;
    return $self->{alg};
}

sub digest_type {
    my ($self) = @_;
    return $self->{digest_type};
}

sub digest {
    my ($self) = @_;
    return $self->{digest};
}

########################################################################
package DnsPacket::RrBodyNsec3;

our @ISA = 'IO::KaitaiStruct::Struct';

sub from_file {
    my ($class, $filename) = @_;
    my $fd;

    open($fd, '<', $filename) or return undef;
    binmode($fd);
    return new($class, IO::KaitaiStruct::Stream->new($fd));
}

sub new {
    my ($class, $_io, $_parent, $_root) = @_;
    my $self = IO::KaitaiStruct::Struct->new($_io);

    bless $self, $class;
    $self->{_parent} = $_parent;
    $self->{_root} = $_root || $self;;

    $self->_read();

    return $self;
}

sub _read {
    my ($self) = @_;

    $self->{class_} = $self->{_io}->read_u2be();
    $self->{time_to_live} = $self->{_io}->read_u4be();
    $self->{data_length} = $self->{_io}->read_u2be();
    $self->{alg} = $self->{_io}->read_u1();
    $self->{flags} = $self->{_io}->read_u1();
    $self->{iterations} = $self->{_io}->read_u2be();
    $self->{salt_length} = $self->{_io}->read_u1();
    $self->{hash_length} = $self->{_io}->read_u1();
    $self->{next_hash} = Encode::decode("utf-8", $self->{_io}->read_bytes($self->hash_length()));
    $self->{type_map} = DnsPacket::Map->new($self->{_io}, $self, $self->{_root});
}

sub class_ {
    my ($self) = @_;
    return $self->{class_};
}

sub time_to_live {
    my ($self) = @_;
    return $self->{time_to_live};
}

sub data_length {
    my ($self) = @_;
    return $self->{data_length};
}

sub alg {
    my ($self) = @_;
    return $self->{alg};
}

sub flags {
    my ($self) = @_;
    return $self->{flags};
}

sub iterations {
    my ($self) = @_;
    return $self->{iterations};
}

sub salt_length {
    my ($self) = @_;
    return $self->{salt_length};
}

sub hash_length {
    my ($self) = @_;
    return $self->{hash_length};
}

sub next_hash {
    my ($self) = @_;
    return $self->{next_hash};
}

sub type_map {
    my ($self) = @_;
    return $self->{type_map};
}

########################################################################
package DnsPacket::RrBodyA;

our @ISA = 'IO::KaitaiStruct::Struct';

sub from_file {
    my ($class, $filename) = @_;
    my $fd;

    open($fd, '<', $filename) or return undef;
    binmode($fd);
    return new($class, IO::KaitaiStruct::Stream->new($fd));
}

sub new {
    my ($class, $_io, $_parent, $_root) = @_;
    my $self = IO::KaitaiStruct::Struct->new($_io);

    bless $self, $class;
    $self->{_parent} = $_parent;
    $self->{_root} = $_root || $self;;

    $self->_read();

    return $self;
}

sub _read {
    my ($self) = @_;

    $self->{class_} = $self->{_io}->read_u2be();
    $self->{time_to_live} = $self->{_io}->read_u4be();
    $self->{data_length} = $self->{_io}->read_u2be();
    $self->{address} = DnsPacket::Ipv4Address->new($self->{_io}, $self, $self->{_root});
}

sub class_ {
    my ($self) = @_;
    return $self->{class_};
}

sub time_to_live {
    my ($self) = @_;
    return $self->{time_to_live};
}

sub data_length {
    my ($self) = @_;
    return $self->{data_length};
}

sub address {
    my ($self) = @_;
    return $self->{address};
}

########################################################################
package DnsPacket::Word;

our @ISA = 'IO::KaitaiStruct::Struct';

sub from_file {
    my ($class, $filename) = @_;
    my $fd;

    open($fd, '<', $filename) or return undef;
    binmode($fd);
    return new($class, IO::KaitaiStruct::Stream->new($fd));
}

sub new {
    my ($class, $_io, $_parent, $_root) = @_;
    my $self = IO::KaitaiStruct::Struct->new($_io);

    bless $self, $class;
    $self->{_parent} = $_parent;
    $self->{_root} = $_root || $self;;

    $self->_read();

    return $self;
}

sub _read {
    my ($self) = @_;

    $self->{length} = $self->{_io}->read_u1();
    if ($self->is_ref()) {
        $self->{ref} = $self->{_io}->read_u1();
    }
    if (!($self->is_ref())) {
        $self->{letters} = Encode::decode("utf-8", $self->{_io}->read_bytes($self->length()));
    }
}

sub is_ref {
    my ($self) = @_;
    return $self->{is_ref} if ($self->{is_ref});
    $self->{is_ref} = $self->length() == 192;
    return $self->{is_ref};
}

sub length {
    my ($self) = @_;
    return $self->{length};
}

sub ref {
    my ($self) = @_;
    return $self->{ref};
}

sub letters {
    my ($self) = @_;
    return $self->{letters};
}

########################################################################
package DnsPacket::RrBodySoa;

our @ISA = 'IO::KaitaiStruct::Struct';

sub from_file {
    my ($class, $filename) = @_;
    my $fd;

    open($fd, '<', $filename) or return undef;
    binmode($fd);
    return new($class, IO::KaitaiStruct::Stream->new($fd));
}

sub new {
    my ($class, $_io, $_parent, $_root) = @_;
    my $self = IO::KaitaiStruct::Struct->new($_io);

    bless $self, $class;
    $self->{_parent} = $_parent;
    $self->{_root} = $_root || $self;;

    $self->_read();

    return $self;
}

sub _read {
    my ($self) = @_;

    $self->{class_} = $self->{_io}->read_u2be();
    $self->{time_to_live} = $self->{_io}->read_u4be();
    $self->{data_length} = $self->{_io}->read_u2be();
    $self->{primary_name_server} = DnsPacket::Domain->new($self->{_io}, $self, $self->{_root});
    $self->{reponsible_authority} = DnsPacket::Domain->new($self->{_io}, $self, $self->{_root});
    $self->{serial_number} = $self->{_io}->read_u4be();
    $self->{refresh_interval} = $self->{_io}->read_u4be();
    $self->{retry_interval} = $self->{_io}->read_u4be();
    $self->{expire_limit} = $self->{_io}->read_u4be();
    $self->{minimum_ttl} = $self->{_io}->read_u4be();
}

sub class_ {
    my ($self) = @_;
    return $self->{class_};
}

sub time_to_live {
    my ($self) = @_;
    return $self->{time_to_live};
}

sub data_length {
    my ($self) = @_;
    return $self->{data_length};
}

sub primary_name_server {
    my ($self) = @_;
    return $self->{primary_name_server};
}

sub reponsible_authority {
    my ($self) = @_;
    return $self->{reponsible_authority};
}

sub serial_number {
    my ($self) = @_;
    return $self->{serial_number};
}

sub refresh_interval {
    my ($self) = @_;
    return $self->{refresh_interval};
}

sub retry_interval {
    my ($self) = @_;
    return $self->{retry_interval};
}

sub expire_limit {
    my ($self) = @_;
    return $self->{expire_limit};
}

sub minimum_ttl {
    my ($self) = @_;
    return $self->{minimum_ttl};
}

1;
