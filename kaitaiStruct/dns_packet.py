from construct import *
from construct.lib import *

dns_packet__map_ = Struct(
	'map_num' / Int8ub,
	'length' / Int8ub,
	'map_bits' / FixedSized(this.length, GreedyString(encoding='utf-8')),
)

dns_packet__resource_record = Struct(
	'name' / LazyBound(lambda: dns_packet__domain),
	'type' / dns_packet__rr_type(Int16ub),
	'body' / Switch(this.type, {DnsPacket.RrType.a: LazyBound(lambda: dns_packet__rr_body_a), DnsPacket.RrType.ds: LazyBound(lambda: dns_packet__rr_body_ds), DnsPacket.RrType.ns: LazyBound(lambda: dns_packet__rr_body_ns), DnsPacket.RrType.key: LazyBound(lambda: dns_packet__rr_body_key), DnsPacket.RrType.cname: LazyBound(lambda: dns_packet__rr_body_cname), DnsPacket.RrType.opt: LazyBound(lambda: dns_packet__rr_body_opt), DnsPacket.RrType.rrsig: LazyBound(lambda: dns_packet__rr_body_rrsig), DnsPacket.RrType.nsec3: LazyBound(lambda: dns_packet__rr_body_nsec3), DnsPacket.RrType.aaaa: LazyBound(lambda: dns_packet__rr_body_aaaa), DnsPacket.RrType.soa: LazyBound(lambda: dns_packet__rr_body_soa), }),
)

dns_packet__rr_body_opt = Struct(
	'udp_payload_size' / Int16ub,
	'higher_bits_in_extended_rcode' / Int8ub,
	'edns0version' / Int8ub,
	'z' / Int16ub,
	'data_length' / Int16ub,
)

dns_packet__rr_body_key = Struct(
	'class_' / Int16ub,
)

dns_packet__domain = Struct(
	'name' / RepeatUntil(lambda obj_, list_, this:  ((obj_.length == 0) or (obj_.length >= 192)) , LazyBound(lambda: dns_packet__word)),
)

dns_packet__ipv6_address = Struct(
	'ip_v6' / FixedSized(16, GreedyBytes),
)

dns_packet__query = Struct(
	'name' / LazyBound(lambda: dns_packet__domain),
	'type' / dns_packet__rr_type(Int16ub),
	'query_class' / Int16ub,
)

dns_packet__rr_body_rrsig = Struct(
	'class_' / Int16ub,
	'time_to_live' / Int32ub,
	'data_length' / Int16ub,
	'type_cov' / Int16ub,
	'alg' / Int8ub,
	'labels' / Int8ub,
	'orig_time_to_live' / Int32ub,
	'sig_exp' / Int32ub,
	'sig_inception' / Int32ub,
	'key_tag' / Int16ub,
	'sign_name' / LazyBound(lambda: dns_packet__domain),
	'signature' / FixedSized(256, GreedyString(encoding='utf-8')),
)

dns_packet__ipv4_address = Struct(
	'ip' / FixedSized(4, GreedyBytes),
)

dns_packet__rr_body_cname = Struct(
	'class_' / Int16ub,
	'time_to_live' / Int32ub,
	'data_length' / Int16ub,
	'cname' / LazyBound(lambda: dns_packet__domain),
)

dns_packet__rr_body_aaaa = Struct(
	'class_' / Int16ub,
	'time_to_live' / Int32ub,
	'data_length' / Int16ub,
	'address' / LazyBound(lambda: dns_packet__ipv6_address),
)

dns_packet__rr_body_ns = Struct(
	'class_' / Int16ub,
	'time_to_live' / Int32ub,
	'data_length' / Int16ub,
	'name_server' / LazyBound(lambda: dns_packet__domain),
)

dns_packet__rr_body_ds = Struct(
	'class_' / Int16ub,
	'time_to_live' / Int32ub,
	'data_length' / Int16ub,
	'keyid' / Int16ub,
	'alg' / Int8ub,
	'digest_type' / Int8ub,
	'digest' / FixedSized(32, GreedyString(encoding='utf-8')),
)

dns_packet__rr_body_nsec3 = Struct(
	'class_' / Int16ub,
	'time_to_live' / Int32ub,
	'data_length' / Int16ub,
	'alg' / Int8ub,
	'flags' / Int8ub,
	'iterations' / Int16ub,
	'salt_length' / Int8ub,
	'hash_length' / Int8ub,
	'next_hash' / FixedSized(this.hash_length, GreedyString(encoding='utf-8')),
	'type_map' / LazyBound(lambda: dns_packet__map_),
)

dns_packet__rr_body_a = Struct(
	'class_' / Int16ub,
	'time_to_live' / Int32ub,
	'data_length' / Int16ub,
	'address' / LazyBound(lambda: dns_packet__ipv4_address),
)

dns_packet__word = Struct(
	'length' / Int8ub,
	'ref' / If(this.is_ref, Int8ub),
	'letters' / If(not (this.is_ref), FixedSized(this.length, GreedyString(encoding='utf-8'))),
	'is_ref' / Computed(lambda this: this.length == 192),
)

dns_packet__rr_body_soa = Struct(
	'class_' / Int16ub,
	'time_to_live' / Int32ub,
	'data_length' / Int16ub,
	'primary_name_server' / LazyBound(lambda: dns_packet__domain),
	'reponsible_authority' / LazyBound(lambda: dns_packet__domain),
	'serial_number' / Int32ub,
	'refresh_interval' / Int32ub,
	'retry_interval' / Int32ub,
	'expire_limit' / Int32ub,
	'minimum_ttl' / Int32ub,
)

def dns_packet__rr_type(subcon):
	return Enum(subcon,
		a=1,
		ns=2,
		cname=5,
		soa=6,
		aaaa=28,
		opt=41,
		ds=43,
		rrsig=46,
		key=48,
		nsec3=50,
	)

dns_packet = Struct(
	'transaction_id' / Int16ub,
	'flags' / Int16ub,
	'qdcount' / Int16ub,
	'ancount' / Int16ub,
	'nscount' / Int16ub,
	'arcount' / Int16ub,
	'queries' / Array(this.qdcount, LazyBound(lambda: dns_packet__query)),
	'answers' / Array(this.ancount, LazyBound(lambda: dns_packet__resource_record)),
	'authorities' / Array(this.nscount, LazyBound(lambda: dns_packet__resource_record)),
	'additionals' / Array(this.arcount, LazyBound(lambda: dns_packet__resource_record)),
)

_schema = dns_packet
