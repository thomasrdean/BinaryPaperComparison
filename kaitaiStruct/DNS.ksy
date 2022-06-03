meta:
  id: dns_packet
  endian: be
  encoding: utf-8
seq:
  - id: transaction_id
    type: u2
  - id: flags
    type: u2
  - id: qdcount
    type: u2
  - id: ancount
    type: u2
  - id: nscount
    type: u2
  - id: arcount
    type: u2
  - id: queries
    type: query
    repeat: expr
    repeat-expr: qdcount
  - id: answers
    type: resource_record
    repeat: expr
    repeat-expr: ancount
  - id: authorities
    type: resource_record
    repeat: expr
    repeat-expr: nscount
  - id: additionals
    type: resource_record
    repeat: expr
    repeat-expr: arcount
types:
  query:
    seq:
      - id: name
        type: domain
      - id: type
        type: u2
        enum: rr_type
      - id: query_class
        type: u2
  resource_record:
    seq:
      - id: name
        type: domain
      - id: type
        type: u2
        enum: rr_type
      - id: body
        type:
          switch-on: type
          cases:
            "rr_type::a": rr_body_a
            "rr_type::aaaa": rr_body_aaaa
            "rr_type::cname": rr_body_cname
            "rr_type::soa": rr_body_soa
            "rr_type::opt": rr_body_opt
            "rr_type::ns": rr_body_ns
            "rr_type::key": rr_body_key
            "rr_type::rrsig": rr_body_rrsig
            "rr_type::ds": rr_body_ds
            "rr_type::nsec3": rr_body_nsec3
  rr_body_a:
    seq:
      - id: class_
        type: u2
      - id: time_to_live
        type: u4
      - id: data_length
        type: u2
      - id: address
        type: ipv4_address
  rr_body_aaaa:
    seq:
      - id: class_
        type: u2
      - id: time_to_live
        type: u4
      - id: data_length
        type: u2
      - id: address
        type: ipv6_address
  rr_body_cname:
    seq:
      - id: class_
        type: u2
      - id: time_to_live
        type: u4
      - id: data_length
        type: u2
      - id: cname
        type: domain
  rr_body_soa:
    seq:
      - id: class_
        type: u2
      - id: time_to_live
        type: u4
      - id: data_length
        type: u2
      - id: primary_name_server
        type: domain
      - id: reponsible_authority
        type: domain
      - id: serial_number
        type: u4
      - id: refresh_interval
        type: u4
      - id: retry_interval
        type: u4
      - id: expire_limit
        type: u4
      - id: minimum_ttl
        type: u4
  rr_body_opt:
    seq:
      - id: udp_payload_size
        type: u2
      - id: higher_bits_in_extended_rcode
        type: u1
      - id: edns0version
        type: u1
      - id: z
        type: u2
      - id: data_length
        type: u2
  rr_body_ns:
    seq:
      - id: class_
        type: u2
      - id: time_to_live
        type: u4
      - id: data_length
        type: u2
      - id: name_server
        type: domain
  rr_body_key:
    seq:
      - id: class_
        type: u2
  rr_body_rrsig:
    seq:
      - id: class_
        type: u2
      - id: time_to_live
        type: u4
      - id: data_length
        type: u2
      - id: type_cov
        type: u2
      - id: alg
        type: u1
      - id: labels
        type: u1
      - id: orig_time_to_live
        type: u4
      - id: sig_exp
        type: u4
      - id: sig_inception
        type: u4
      - id: key_tag
        type: u2
      - id: sign_name
        type: domain
      - id: signature
        type: str
        size: 256
  rr_body_ds:
    seq:
      - id: class_
        type: u2
      - id: time_to_live
        type: u4
      - id: data_length
        type: u2
      - id: keyid
        type: u2
      - id: alg
        type: u1
      - id: digest_type
        type: u1
      - id: digest
        type: str
        size: 32
  rr_body_nsec3:
    seq:
      - id: class_
        type: u2
      - id: time_to_live
        type: u4
      - id: data_length
        type: u2
      - id: alg
        type: u1
      - id: flags
        type: u1
      - id: iterations
        type: u2
      - id: salt_length
        type: u1
      - id: hash_length
        type: u1
      - id: next_hash
        type: str
        size: hash_length
      - id: type_map
        type: map_
  map_:
    seq:
      - id: map_num
        type: u1
      - id: length
        type: u1
      - id: map_bits
        type: str
        size: length

  domain:
    seq:
      - id: name
        type: word
        repeat: until
        repeat-until: "_.length == 0 or _.length >= 192"
  word:
    seq:
      - id: length
        type: u1
      - id: ref
        if: "is_ref"
        type: u1
      - id: letters
        if: "not is_ref"
        type: str
        size: length
    instances:
      is_ref:
        value: length == 192
  ipv4_address:
    seq:
      - id: ip
        size: 4
  ipv6_address:
    seq:
      - id: ip_v6
        size: 16
enums:
  rr_type:
    1: a
    28: aaaa
    5: cname
    6: soa
    41: opt
    2: ns
    48: key
    46: rrsig
    43: ds
    50: nsec3