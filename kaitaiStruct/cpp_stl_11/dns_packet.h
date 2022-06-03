#pragma once

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include <memory>
#include <vector>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif

class dns_packet_t : public kaitai::kstruct {

public:
    class map__t;
    class resource_record_t;
    class rr_body_opt_t;
    class rr_body_key_t;
    class domain_t;
    class ipv6_address_t;
    class query_t;
    class rr_body_rrsig_t;
    class ipv4_address_t;
    class rr_body_cname_t;
    class rr_body_aaaa_t;
    class rr_body_ns_t;
    class rr_body_ds_t;
    class rr_body_nsec3_t;
    class rr_body_a_t;
    class word_t;
    class rr_body_soa_t;

    enum rr_type_t {
        RR_TYPE_A = 1,
        RR_TYPE_NS = 2,
        RR_TYPE_CNAME = 5,
        RR_TYPE_SOA = 6,
        RR_TYPE_AAAA = 28,
        RR_TYPE_OPT = 41,
        RR_TYPE_DS = 43,
        RR_TYPE_RRSIG = 46,
        RR_TYPE_KEY = 48,
        RR_TYPE_NSEC3 = 50
    };

    dns_packet_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = nullptr, dns_packet_t* p__root = nullptr);

private:
    void _read();
    void _clean_up();

public:
    ~dns_packet_t();

    class map__t : public kaitai::kstruct {

    public:

        map__t(kaitai::kstream* p__io, dns_packet_t::rr_body_nsec3_t* p__parent = nullptr, dns_packet_t* p__root = nullptr);

    private:
        void _read();
        void _clean_up();

    public:
        ~map__t();

    private:
        uint8_t m_map_num;
        uint8_t m_length;
        std::string m_map_bits;
        dns_packet_t* m__root;
        dns_packet_t::rr_body_nsec3_t* m__parent;

    public:
        uint8_t map_num() const { return m_map_num; }
        uint8_t length() const { return m_length; }
        std::string map_bits() const { return m_map_bits; }
        dns_packet_t* _root() const { return m__root; }
        dns_packet_t::rr_body_nsec3_t* _parent() const { return m__parent; }
    };

    class resource_record_t : public kaitai::kstruct {

    public:

        resource_record_t(kaitai::kstream* p__io, dns_packet_t* p__parent = nullptr, dns_packet_t* p__root = nullptr);

    private:
        void _read();
        void _clean_up();

    public:
        ~resource_record_t();

    private:
        std::unique_ptr<domain_t> m_name;
        rr_type_t m_type;
        std::unique_ptr<kaitai::kstruct> m_body;
        bool n_body;

    public:
        bool _is_null_body() { body(); return n_body; };

    private:
        dns_packet_t* m__root;
        dns_packet_t* m__parent;

    public:
        domain_t* name() const { return m_name.get(); }
        rr_type_t type() const { return m_type; }
        kaitai::kstruct* body() const { return m_body.get(); }
        dns_packet_t* _root() const { return m__root; }
        dns_packet_t* _parent() const { return m__parent; }
    };

    class rr_body_opt_t : public kaitai::kstruct {

    public:

        rr_body_opt_t(kaitai::kstream* p__io, dns_packet_t::resource_record_t* p__parent = nullptr, dns_packet_t* p__root = nullptr);

    private:
        void _read();
        void _clean_up();

    public:
        ~rr_body_opt_t();

    private:
        uint16_t m_udp_payload_size;
        uint8_t m_higher_bits_in_extended_rcode;
        uint8_t m_edns0version;
        uint16_t m_z;
        uint16_t m_data_length;
        dns_packet_t* m__root;
        dns_packet_t::resource_record_t* m__parent;

    public:
        uint16_t udp_payload_size() const { return m_udp_payload_size; }
        uint8_t higher_bits_in_extended_rcode() const { return m_higher_bits_in_extended_rcode; }
        uint8_t edns0version() const { return m_edns0version; }
        uint16_t z() const { return m_z; }
        uint16_t data_length() const { return m_data_length; }
        dns_packet_t* _root() const { return m__root; }
        dns_packet_t::resource_record_t* _parent() const { return m__parent; }
    };

    class rr_body_key_t : public kaitai::kstruct {

    public:

        rr_body_key_t(kaitai::kstream* p__io, dns_packet_t::resource_record_t* p__parent = nullptr, dns_packet_t* p__root = nullptr);

    private:
        void _read();
        void _clean_up();

    public:
        ~rr_body_key_t();

    private:
        uint16_t m_class_;
        dns_packet_t* m__root;
        dns_packet_t::resource_record_t* m__parent;

    public:
        uint16_t class_() const { return m_class_; }
        dns_packet_t* _root() const { return m__root; }
        dns_packet_t::resource_record_t* _parent() const { return m__parent; }
    };

    class domain_t : public kaitai::kstruct {

    public:

        domain_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = nullptr, dns_packet_t* p__root = nullptr);

    private:
        void _read();
        void _clean_up();

    public:
        ~domain_t();

    private:
        std::unique_ptr<std::vector<std::unique_ptr<word_t>>> m_name;
        dns_packet_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        std::vector<std::unique_ptr<word_t>>* name() const { return m_name.get(); }
        dns_packet_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    class ipv6_address_t : public kaitai::kstruct {

    public:

        ipv6_address_t(kaitai::kstream* p__io, dns_packet_t::rr_body_aaaa_t* p__parent = nullptr, dns_packet_t* p__root = nullptr);

    private:
        void _read();
        void _clean_up();

    public:
        ~ipv6_address_t();

    private:
        std::string m_ip_v6;
        dns_packet_t* m__root;
        dns_packet_t::rr_body_aaaa_t* m__parent;

    public:
        std::string ip_v6() const { return m_ip_v6; }
        dns_packet_t* _root() const { return m__root; }
        dns_packet_t::rr_body_aaaa_t* _parent() const { return m__parent; }
    };

    class query_t : public kaitai::kstruct {

    public:

        query_t(kaitai::kstream* p__io, dns_packet_t* p__parent = nullptr, dns_packet_t* p__root = nullptr);

    private:
        void _read();
        void _clean_up();

    public:
        ~query_t();

    private:
        std::unique_ptr<domain_t> m_name;
        rr_type_t m_type;
        uint16_t m_query_class;
        dns_packet_t* m__root;
        dns_packet_t* m__parent;

    public:
        domain_t* name() const { return m_name.get(); }
        rr_type_t type() const { return m_type; }
        uint16_t query_class() const { return m_query_class; }
        dns_packet_t* _root() const { return m__root; }
        dns_packet_t* _parent() const { return m__parent; }
    };

    class rr_body_rrsig_t : public kaitai::kstruct {

    public:

        rr_body_rrsig_t(kaitai::kstream* p__io, dns_packet_t::resource_record_t* p__parent = nullptr, dns_packet_t* p__root = nullptr);

    private:
        void _read();
        void _clean_up();

    public:
        ~rr_body_rrsig_t();

    private:
        uint16_t m_class_;
        uint32_t m_time_to_live;
        uint16_t m_data_length;
        uint16_t m_type_cov;
        uint8_t m_alg;
        uint8_t m_labels;
        uint32_t m_orig_time_to_live;
        uint32_t m_sig_exp;
        uint32_t m_sig_inception;
        uint16_t m_key_tag;
        std::unique_ptr<domain_t> m_sign_name;
        std::string m_signature;
        dns_packet_t* m__root;
        dns_packet_t::resource_record_t* m__parent;

    public:
        uint16_t class_() const { return m_class_; }
        uint32_t time_to_live() const { return m_time_to_live; }
        uint16_t data_length() const { return m_data_length; }
        uint16_t type_cov() const { return m_type_cov; }
        uint8_t alg() const { return m_alg; }
        uint8_t labels() const { return m_labels; }
        uint32_t orig_time_to_live() const { return m_orig_time_to_live; }
        uint32_t sig_exp() const { return m_sig_exp; }
        uint32_t sig_inception() const { return m_sig_inception; }
        uint16_t key_tag() const { return m_key_tag; }
        domain_t* sign_name() const { return m_sign_name.get(); }
        std::string signature() const { return m_signature; }
        dns_packet_t* _root() const { return m__root; }
        dns_packet_t::resource_record_t* _parent() const { return m__parent; }
    };

    class ipv4_address_t : public kaitai::kstruct {

    public:

        ipv4_address_t(kaitai::kstream* p__io, dns_packet_t::rr_body_a_t* p__parent = nullptr, dns_packet_t* p__root = nullptr);

    private:
        void _read();
        void _clean_up();

    public:
        ~ipv4_address_t();

    private:
        std::string m_ip;
        dns_packet_t* m__root;
        dns_packet_t::rr_body_a_t* m__parent;

    public:
        std::string ip() const { return m_ip; }
        dns_packet_t* _root() const { return m__root; }
        dns_packet_t::rr_body_a_t* _parent() const { return m__parent; }
    };

    class rr_body_cname_t : public kaitai::kstruct {

    public:

        rr_body_cname_t(kaitai::kstream* p__io, dns_packet_t::resource_record_t* p__parent = nullptr, dns_packet_t* p__root = nullptr);

    private:
        void _read();
        void _clean_up();

    public:
        ~rr_body_cname_t();

    private:
        uint16_t m_class_;
        uint32_t m_time_to_live;
        uint16_t m_data_length;
        std::unique_ptr<domain_t> m_cname;
        dns_packet_t* m__root;
        dns_packet_t::resource_record_t* m__parent;

    public:
        uint16_t class_() const { return m_class_; }
        uint32_t time_to_live() const { return m_time_to_live; }
        uint16_t data_length() const { return m_data_length; }
        domain_t* cname() const { return m_cname.get(); }
        dns_packet_t* _root() const { return m__root; }
        dns_packet_t::resource_record_t* _parent() const { return m__parent; }
    };

    class rr_body_aaaa_t : public kaitai::kstruct {

    public:

        rr_body_aaaa_t(kaitai::kstream* p__io, dns_packet_t::resource_record_t* p__parent = nullptr, dns_packet_t* p__root = nullptr);

    private:
        void _read();
        void _clean_up();

    public:
        ~rr_body_aaaa_t();

    private:
        uint16_t m_class_;
        uint32_t m_time_to_live;
        uint16_t m_data_length;
        std::unique_ptr<ipv6_address_t> m_address;
        dns_packet_t* m__root;
        dns_packet_t::resource_record_t* m__parent;

    public:
        uint16_t class_() const { return m_class_; }
        uint32_t time_to_live() const { return m_time_to_live; }
        uint16_t data_length() const { return m_data_length; }
        ipv6_address_t* address() const { return m_address.get(); }
        dns_packet_t* _root() const { return m__root; }
        dns_packet_t::resource_record_t* _parent() const { return m__parent; }
    };

    class rr_body_ns_t : public kaitai::kstruct {

    public:

        rr_body_ns_t(kaitai::kstream* p__io, dns_packet_t::resource_record_t* p__parent = nullptr, dns_packet_t* p__root = nullptr);

    private:
        void _read();
        void _clean_up();

    public:
        ~rr_body_ns_t();

    private:
        uint16_t m_class_;
        uint32_t m_time_to_live;
        uint16_t m_data_length;
        std::unique_ptr<domain_t> m_name_server;
        dns_packet_t* m__root;
        dns_packet_t::resource_record_t* m__parent;

    public:
        uint16_t class_() const { return m_class_; }
        uint32_t time_to_live() const { return m_time_to_live; }
        uint16_t data_length() const { return m_data_length; }
        domain_t* name_server() const { return m_name_server.get(); }
        dns_packet_t* _root() const { return m__root; }
        dns_packet_t::resource_record_t* _parent() const { return m__parent; }
    };

    class rr_body_ds_t : public kaitai::kstruct {

    public:

        rr_body_ds_t(kaitai::kstream* p__io, dns_packet_t::resource_record_t* p__parent = nullptr, dns_packet_t* p__root = nullptr);

    private:
        void _read();
        void _clean_up();

    public:
        ~rr_body_ds_t();

    private:
        uint16_t m_class_;
        uint32_t m_time_to_live;
        uint16_t m_data_length;
        uint16_t m_keyid;
        uint8_t m_alg;
        uint8_t m_digest_type;
        std::string m_digest;
        dns_packet_t* m__root;
        dns_packet_t::resource_record_t* m__parent;

    public:
        uint16_t class_() const { return m_class_; }
        uint32_t time_to_live() const { return m_time_to_live; }
        uint16_t data_length() const { return m_data_length; }
        uint16_t keyid() const { return m_keyid; }
        uint8_t alg() const { return m_alg; }
        uint8_t digest_type() const { return m_digest_type; }
        std::string digest() const { return m_digest; }
        dns_packet_t* _root() const { return m__root; }
        dns_packet_t::resource_record_t* _parent() const { return m__parent; }
    };

    class rr_body_nsec3_t : public kaitai::kstruct {

    public:

        rr_body_nsec3_t(kaitai::kstream* p__io, dns_packet_t::resource_record_t* p__parent = nullptr, dns_packet_t* p__root = nullptr);

    private:
        void _read();
        void _clean_up();

    public:
        ~rr_body_nsec3_t();

    private:
        uint16_t m_class_;
        uint32_t m_time_to_live;
        uint16_t m_data_length;
        uint8_t m_alg;
        uint8_t m_flags;
        uint16_t m_iterations;
        uint8_t m_salt_length;
        uint8_t m_hash_length;
        std::string m_next_hash;
        std::unique_ptr<map__t> m_type_map;
        dns_packet_t* m__root;
        dns_packet_t::resource_record_t* m__parent;

    public:
        uint16_t class_() const { return m_class_; }
        uint32_t time_to_live() const { return m_time_to_live; }
        uint16_t data_length() const { return m_data_length; }
        uint8_t alg() const { return m_alg; }
        uint8_t flags() const { return m_flags; }
        uint16_t iterations() const { return m_iterations; }
        uint8_t salt_length() const { return m_salt_length; }
        uint8_t hash_length() const { return m_hash_length; }
        std::string next_hash() const { return m_next_hash; }
        map__t* type_map() const { return m_type_map.get(); }
        dns_packet_t* _root() const { return m__root; }
        dns_packet_t::resource_record_t* _parent() const { return m__parent; }
    };

    class rr_body_a_t : public kaitai::kstruct {

    public:

        rr_body_a_t(kaitai::kstream* p__io, dns_packet_t::resource_record_t* p__parent = nullptr, dns_packet_t* p__root = nullptr);

    private:
        void _read();
        void _clean_up();

    public:
        ~rr_body_a_t();

    private:
        uint16_t m_class_;
        uint32_t m_time_to_live;
        uint16_t m_data_length;
        std::unique_ptr<ipv4_address_t> m_address;
        dns_packet_t* m__root;
        dns_packet_t::resource_record_t* m__parent;

    public:
        uint16_t class_() const { return m_class_; }
        uint32_t time_to_live() const { return m_time_to_live; }
        uint16_t data_length() const { return m_data_length; }
        ipv4_address_t* address() const { return m_address.get(); }
        dns_packet_t* _root() const { return m__root; }
        dns_packet_t::resource_record_t* _parent() const { return m__parent; }
    };

    class word_t : public kaitai::kstruct {

    public:

        word_t(kaitai::kstream* p__io, dns_packet_t::domain_t* p__parent = nullptr, dns_packet_t* p__root = nullptr);

    private:
        void _read();
        void _clean_up();

    public:
        ~word_t();

    private:
        bool f_is_ref;
        bool m_is_ref;

    public:
        bool is_ref();

    private:
        uint8_t m_length;
        uint8_t m_ref;
        bool n_ref;

    public:
        bool _is_null_ref() { ref(); return n_ref; };

    private:
        std::string m_letters;
        bool n_letters;

    public:
        bool _is_null_letters() { letters(); return n_letters; };

    private:
        dns_packet_t* m__root;
        dns_packet_t::domain_t* m__parent;

    public:
        uint8_t length() const { return m_length; }
        uint8_t ref() const { return m_ref; }
        std::string letters() const { return m_letters; }
        dns_packet_t* _root() const { return m__root; }
        dns_packet_t::domain_t* _parent() const { return m__parent; }
    };

    class rr_body_soa_t : public kaitai::kstruct {

    public:

        rr_body_soa_t(kaitai::kstream* p__io, dns_packet_t::resource_record_t* p__parent = nullptr, dns_packet_t* p__root = nullptr);

    private:
        void _read();
        void _clean_up();

    public:
        ~rr_body_soa_t();

    private:
        uint16_t m_class_;
        uint32_t m_time_to_live;
        uint16_t m_data_length;
        std::unique_ptr<domain_t> m_primary_name_server;
        std::unique_ptr<domain_t> m_reponsible_authority;
        uint32_t m_serial_number;
        uint32_t m_refresh_interval;
        uint32_t m_retry_interval;
        uint32_t m_expire_limit;
        uint32_t m_minimum_ttl;
        dns_packet_t* m__root;
        dns_packet_t::resource_record_t* m__parent;

    public:
        uint16_t class_() const { return m_class_; }
        uint32_t time_to_live() const { return m_time_to_live; }
        uint16_t data_length() const { return m_data_length; }
        domain_t* primary_name_server() const { return m_primary_name_server.get(); }
        domain_t* reponsible_authority() const { return m_reponsible_authority.get(); }
        uint32_t serial_number() const { return m_serial_number; }
        uint32_t refresh_interval() const { return m_refresh_interval; }
        uint32_t retry_interval() const { return m_retry_interval; }
        uint32_t expire_limit() const { return m_expire_limit; }
        uint32_t minimum_ttl() const { return m_minimum_ttl; }
        dns_packet_t* _root() const { return m__root; }
        dns_packet_t::resource_record_t* _parent() const { return m__parent; }
    };

private:
    uint16_t m_transaction_id;
    uint16_t m_flags;
    uint16_t m_qdcount;
    uint16_t m_ancount;
    uint16_t m_nscount;
    uint16_t m_arcount;
    std::unique_ptr<std::vector<std::unique_ptr<query_t>>> m_queries;
    std::unique_ptr<std::vector<std::unique_ptr<resource_record_t>>> m_answers;
    std::unique_ptr<std::vector<std::unique_ptr<resource_record_t>>> m_authorities;
    std::unique_ptr<std::vector<std::unique_ptr<resource_record_t>>> m_additionals;
    dns_packet_t* m__root;
    kaitai::kstruct* m__parent;

public:
    uint16_t transaction_id() const { return m_transaction_id; }
    uint16_t flags() const { return m_flags; }
    uint16_t qdcount() const { return m_qdcount; }
    uint16_t ancount() const { return m_ancount; }
    uint16_t nscount() const { return m_nscount; }
    uint16_t arcount() const { return m_arcount; }
    std::vector<std::unique_ptr<query_t>>* queries() const { return m_queries.get(); }
    std::vector<std::unique_ptr<resource_record_t>>* answers() const { return m_answers.get(); }
    std::vector<std::unique_ptr<resource_record_t>>* authorities() const { return m_authorities.get(); }
    std::vector<std::unique_ptr<resource_record_t>>* additionals() const { return m_additionals.get(); }
    dns_packet_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};
