// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "dns_packet.h"

dns_packet_t::dns_packet_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, dns_packet_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_queries = 0;
    m_answers = 0;
    m_authorities = 0;
    m_additionals = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void dns_packet_t::_read() {
    m_transaction_id = m__io->read_u2be();
    m_flags = m__io->read_u2be();
    m_qdcount = m__io->read_u2be();
    m_ancount = m__io->read_u2be();
    m_nscount = m__io->read_u2be();
    m_arcount = m__io->read_u2be();
    int l_queries = qdcount();
    m_queries = new std::vector<query_t*>();
    m_queries->reserve(l_queries);
    for (int i = 0; i < l_queries; i++) {
        m_queries->push_back(new query_t(m__io, this, m__root));
    }
    int l_answers = ancount();
    m_answers = new std::vector<resource_record_t*>();
    m_answers->reserve(l_answers);
    for (int i = 0; i < l_answers; i++) {
        m_answers->push_back(new resource_record_t(m__io, this, m__root));
    }
    int l_authorities = nscount();
    m_authorities = new std::vector<resource_record_t*>();
    m_authorities->reserve(l_authorities);
    for (int i = 0; i < l_authorities; i++) {
        m_authorities->push_back(new resource_record_t(m__io, this, m__root));
    }
    int l_additionals = arcount();
    m_additionals = new std::vector<resource_record_t*>();
    m_additionals->reserve(l_additionals);
    for (int i = 0; i < l_additionals; i++) {
        m_additionals->push_back(new resource_record_t(m__io, this, m__root));
    }
}

dns_packet_t::~dns_packet_t() {
    _clean_up();
}

void dns_packet_t::_clean_up() {
    if (m_queries) {
        for (std::vector<query_t*>::iterator it = m_queries->begin(); it != m_queries->end(); ++it) {
            delete *it;
        }
        delete m_queries; m_queries = 0;
    }
    if (m_answers) {
        for (std::vector<resource_record_t*>::iterator it = m_answers->begin(); it != m_answers->end(); ++it) {
            delete *it;
        }
        delete m_answers; m_answers = 0;
    }
    if (m_authorities) {
        for (std::vector<resource_record_t*>::iterator it = m_authorities->begin(); it != m_authorities->end(); ++it) {
            delete *it;
        }
        delete m_authorities; m_authorities = 0;
    }
    if (m_additionals) {
        for (std::vector<resource_record_t*>::iterator it = m_additionals->begin(); it != m_additionals->end(); ++it) {
            delete *it;
        }
        delete m_additionals; m_additionals = 0;
    }
}

dns_packet_t::map__t::map__t(kaitai::kstream* p__io, dns_packet_t::rr_body_nsec3_t* p__parent, dns_packet_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void dns_packet_t::map__t::_read() {
    m_map_num = m__io->read_u1();
    m_length = m__io->read_u1();
    m_map_bits = kaitai::kstream::bytes_to_str(m__io->read_bytes(length()), std::string("utf-8"));
}

dns_packet_t::map__t::~map__t() {
    _clean_up();
}

void dns_packet_t::map__t::_clean_up() {
}

dns_packet_t::resource_record_t::resource_record_t(kaitai::kstream* p__io, dns_packet_t* p__parent, dns_packet_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_name = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void dns_packet_t::resource_record_t::_read() {
    m_name = new domain_t(m__io, this, m__root);
    m_type = static_cast<dns_packet_t::rr_type_t>(m__io->read_u2be());
    n_body = true;
    switch (type()) {
    case dns_packet_t::RR_TYPE_A: {
        n_body = false;
        m_body = new rr_body_a_t(m__io, this, m__root);
        break;
    }
    case dns_packet_t::RR_TYPE_DS: {
        n_body = false;
        m_body = new rr_body_ds_t(m__io, this, m__root);
        break;
    }
    case dns_packet_t::RR_TYPE_NS: {
        n_body = false;
        m_body = new rr_body_ns_t(m__io, this, m__root);
        break;
    }
    case dns_packet_t::RR_TYPE_KEY: {
        n_body = false;
        m_body = new rr_body_key_t(m__io, this, m__root);
        break;
    }
    case dns_packet_t::RR_TYPE_CNAME: {
        n_body = false;
        m_body = new rr_body_cname_t(m__io, this, m__root);
        break;
    }
    case dns_packet_t::RR_TYPE_OPT: {
        n_body = false;
        m_body = new rr_body_opt_t(m__io, this, m__root);
        break;
    }
    case dns_packet_t::RR_TYPE_RRSIG: {
        n_body = false;
        m_body = new rr_body_rrsig_t(m__io, this, m__root);
        break;
    }
    case dns_packet_t::RR_TYPE_NSEC3: {
        n_body = false;
        m_body = new rr_body_nsec3_t(m__io, this, m__root);
        break;
    }
    case dns_packet_t::RR_TYPE_AAAA: {
        n_body = false;
        m_body = new rr_body_aaaa_t(m__io, this, m__root);
        break;
    }
    case dns_packet_t::RR_TYPE_SOA: {
        n_body = false;
        m_body = new rr_body_soa_t(m__io, this, m__root);
        break;
    }
    }
}

dns_packet_t::resource_record_t::~resource_record_t() {
    _clean_up();
}

void dns_packet_t::resource_record_t::_clean_up() {
    if (m_name) {
        delete m_name; m_name = 0;
    }
    if (!n_body) {
        if (m_body) {
            delete m_body; m_body = 0;
        }
    }
}

dns_packet_t::rr_body_opt_t::rr_body_opt_t(kaitai::kstream* p__io, dns_packet_t::resource_record_t* p__parent, dns_packet_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void dns_packet_t::rr_body_opt_t::_read() {
    m_udp_payload_size = m__io->read_u2be();
    m_higher_bits_in_extended_rcode = m__io->read_u1();
    m_edns0version = m__io->read_u1();
    m_z = m__io->read_u2be();
    m_data_length = m__io->read_u2be();
}

dns_packet_t::rr_body_opt_t::~rr_body_opt_t() {
    _clean_up();
}

void dns_packet_t::rr_body_opt_t::_clean_up() {
}

dns_packet_t::rr_body_key_t::rr_body_key_t(kaitai::kstream* p__io, dns_packet_t::resource_record_t* p__parent, dns_packet_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void dns_packet_t::rr_body_key_t::_read() {
    m_class_ = m__io->read_u2be();
}

dns_packet_t::rr_body_key_t::~rr_body_key_t() {
    _clean_up();
}

void dns_packet_t::rr_body_key_t::_clean_up() {
}

dns_packet_t::domain_t::domain_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, dns_packet_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_name = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void dns_packet_t::domain_t::_read() {
    m_name = new std::vector<word_t*>();
    {
        int i = 0;
        word_t* _;
        do {
            _ = new word_t(m__io, this, m__root);
            m_name->push_back(_);
            i++;
        } while (!( ((_->length() == 0) || (_->length() >= 192)) ));
    }
}

dns_packet_t::domain_t::~domain_t() {
    _clean_up();
}

void dns_packet_t::domain_t::_clean_up() {
    if (m_name) {
        for (std::vector<word_t*>::iterator it = m_name->begin(); it != m_name->end(); ++it) {
            delete *it;
        }
        delete m_name; m_name = 0;
    }
}

dns_packet_t::ipv6_address_t::ipv6_address_t(kaitai::kstream* p__io, dns_packet_t::rr_body_aaaa_t* p__parent, dns_packet_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void dns_packet_t::ipv6_address_t::_read() {
    m_ip_v6 = m__io->read_bytes(16);
}

dns_packet_t::ipv6_address_t::~ipv6_address_t() {
    _clean_up();
}

void dns_packet_t::ipv6_address_t::_clean_up() {
}

dns_packet_t::query_t::query_t(kaitai::kstream* p__io, dns_packet_t* p__parent, dns_packet_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_name = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void dns_packet_t::query_t::_read() {
    m_name = new domain_t(m__io, this, m__root);
    m_type = static_cast<dns_packet_t::rr_type_t>(m__io->read_u2be());
    m_query_class = m__io->read_u2be();
}

dns_packet_t::query_t::~query_t() {
    _clean_up();
}

void dns_packet_t::query_t::_clean_up() {
    if (m_name) {
        delete m_name; m_name = 0;
    }
}

dns_packet_t::rr_body_rrsig_t::rr_body_rrsig_t(kaitai::kstream* p__io, dns_packet_t::resource_record_t* p__parent, dns_packet_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_sign_name = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void dns_packet_t::rr_body_rrsig_t::_read() {
    m_class_ = m__io->read_u2be();
    m_time_to_live = m__io->read_u4be();
    m_data_length = m__io->read_u2be();
    m_type_cov = m__io->read_u2be();
    m_alg = m__io->read_u1();
    m_labels = m__io->read_u1();
    m_orig_time_to_live = m__io->read_u4be();
    m_sig_exp = m__io->read_u4be();
    m_sig_inception = m__io->read_u4be();
    m_key_tag = m__io->read_u2be();
    m_sign_name = new domain_t(m__io, this, m__root);
    m_signature = kaitai::kstream::bytes_to_str(m__io->read_bytes(256), std::string("utf-8"));
}

dns_packet_t::rr_body_rrsig_t::~rr_body_rrsig_t() {
    _clean_up();
}

void dns_packet_t::rr_body_rrsig_t::_clean_up() {
    if (m_sign_name) {
        delete m_sign_name; m_sign_name = 0;
    }
}

dns_packet_t::ipv4_address_t::ipv4_address_t(kaitai::kstream* p__io, dns_packet_t::rr_body_a_t* p__parent, dns_packet_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void dns_packet_t::ipv4_address_t::_read() {
    m_ip = m__io->read_bytes(4);
}

dns_packet_t::ipv4_address_t::~ipv4_address_t() {
    _clean_up();
}

void dns_packet_t::ipv4_address_t::_clean_up() {
}

dns_packet_t::rr_body_cname_t::rr_body_cname_t(kaitai::kstream* p__io, dns_packet_t::resource_record_t* p__parent, dns_packet_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_cname = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void dns_packet_t::rr_body_cname_t::_read() {
    m_class_ = m__io->read_u2be();
    m_time_to_live = m__io->read_u4be();
    m_data_length = m__io->read_u2be();
    m_cname = new domain_t(m__io, this, m__root);
}

dns_packet_t::rr_body_cname_t::~rr_body_cname_t() {
    _clean_up();
}

void dns_packet_t::rr_body_cname_t::_clean_up() {
    if (m_cname) {
        delete m_cname; m_cname = 0;
    }
}

dns_packet_t::rr_body_aaaa_t::rr_body_aaaa_t(kaitai::kstream* p__io, dns_packet_t::resource_record_t* p__parent, dns_packet_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_address = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void dns_packet_t::rr_body_aaaa_t::_read() {
    m_class_ = m__io->read_u2be();
    m_time_to_live = m__io->read_u4be();
    m_data_length = m__io->read_u2be();
    m_address = new ipv6_address_t(m__io, this, m__root);
}

dns_packet_t::rr_body_aaaa_t::~rr_body_aaaa_t() {
    _clean_up();
}

void dns_packet_t::rr_body_aaaa_t::_clean_up() {
    if (m_address) {
        delete m_address; m_address = 0;
    }
}

dns_packet_t::rr_body_ns_t::rr_body_ns_t(kaitai::kstream* p__io, dns_packet_t::resource_record_t* p__parent, dns_packet_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_name_server = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void dns_packet_t::rr_body_ns_t::_read() {
    m_class_ = m__io->read_u2be();
    m_time_to_live = m__io->read_u4be();
    m_data_length = m__io->read_u2be();
    m_name_server = new domain_t(m__io, this, m__root);
}

dns_packet_t::rr_body_ns_t::~rr_body_ns_t() {
    _clean_up();
}

void dns_packet_t::rr_body_ns_t::_clean_up() {
    if (m_name_server) {
        delete m_name_server; m_name_server = 0;
    }
}

dns_packet_t::rr_body_ds_t::rr_body_ds_t(kaitai::kstream* p__io, dns_packet_t::resource_record_t* p__parent, dns_packet_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void dns_packet_t::rr_body_ds_t::_read() {
    m_class_ = m__io->read_u2be();
    m_time_to_live = m__io->read_u4be();
    m_data_length = m__io->read_u2be();
    m_keyid = m__io->read_u2be();
    m_alg = m__io->read_u1();
    m_digest_type = m__io->read_u1();
    m_digest = kaitai::kstream::bytes_to_str(m__io->read_bytes(32), std::string("utf-8"));
}

dns_packet_t::rr_body_ds_t::~rr_body_ds_t() {
    _clean_up();
}

void dns_packet_t::rr_body_ds_t::_clean_up() {
}

dns_packet_t::rr_body_nsec3_t::rr_body_nsec3_t(kaitai::kstream* p__io, dns_packet_t::resource_record_t* p__parent, dns_packet_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_type_map = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void dns_packet_t::rr_body_nsec3_t::_read() {
    m_class_ = m__io->read_u2be();
    m_time_to_live = m__io->read_u4be();
    m_data_length = m__io->read_u2be();
    m_alg = m__io->read_u1();
    m_flags = m__io->read_u1();
    m_iterations = m__io->read_u2be();
    m_salt_length = m__io->read_u1();
    m_hash_length = m__io->read_u1();
    m_next_hash = kaitai::kstream::bytes_to_str(m__io->read_bytes(hash_length()), std::string("utf-8"));
    m_type_map = new map__t(m__io, this, m__root);
}

dns_packet_t::rr_body_nsec3_t::~rr_body_nsec3_t() {
    _clean_up();
}

void dns_packet_t::rr_body_nsec3_t::_clean_up() {
    if (m_type_map) {
        delete m_type_map; m_type_map = 0;
    }
}

dns_packet_t::rr_body_a_t::rr_body_a_t(kaitai::kstream* p__io, dns_packet_t::resource_record_t* p__parent, dns_packet_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_address = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void dns_packet_t::rr_body_a_t::_read() {
    m_class_ = m__io->read_u2be();
    m_time_to_live = m__io->read_u4be();
    m_data_length = m__io->read_u2be();
    m_address = new ipv4_address_t(m__io, this, m__root);
}

dns_packet_t::rr_body_a_t::~rr_body_a_t() {
    _clean_up();
}

void dns_packet_t::rr_body_a_t::_clean_up() {
    if (m_address) {
        delete m_address; m_address = 0;
    }
}

dns_packet_t::word_t::word_t(kaitai::kstream* p__io, dns_packet_t::domain_t* p__parent, dns_packet_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_is_ref = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void dns_packet_t::word_t::_read() {
    m_length = m__io->read_u1();
    n_ref = true;
    if (is_ref()) {
        n_ref = false;
        m_ref = m__io->read_u1();
    }
    n_letters = true;
    if (!(is_ref())) {
        n_letters = false;
        m_letters = kaitai::kstream::bytes_to_str(m__io->read_bytes(length()), std::string("utf-8"));
    }
}

dns_packet_t::word_t::~word_t() {
    _clean_up();
}

void dns_packet_t::word_t::_clean_up() {
    if (!n_ref) {
    }
    if (!n_letters) {
    }
}

bool dns_packet_t::word_t::is_ref() {
    if (f_is_ref)
        return m_is_ref;
    m_is_ref = length() == 192;
    f_is_ref = true;
    return m_is_ref;
}

dns_packet_t::rr_body_soa_t::rr_body_soa_t(kaitai::kstream* p__io, dns_packet_t::resource_record_t* p__parent, dns_packet_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_primary_name_server = 0;
    m_reponsible_authority = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void dns_packet_t::rr_body_soa_t::_read() {
    m_class_ = m__io->read_u2be();
    m_time_to_live = m__io->read_u4be();
    m_data_length = m__io->read_u2be();
    m_primary_name_server = new domain_t(m__io, this, m__root);
    m_reponsible_authority = new domain_t(m__io, this, m__root);
    m_serial_number = m__io->read_u4be();
    m_refresh_interval = m__io->read_u4be();
    m_retry_interval = m__io->read_u4be();
    m_expire_limit = m__io->read_u4be();
    m_minimum_ttl = m__io->read_u4be();
}

dns_packet_t::rr_body_soa_t::~rr_body_soa_t() {
    _clean_up();
}

void dns_packet_t::rr_body_soa_t::_clean_up() {
    if (m_primary_name_server) {
        delete m_primary_name_server; m_primary_name_server = 0;
    }
    if (m_reponsible_authority) {
        delete m_reponsible_authority; m_reponsible_authority = 0;
    }
}
