# This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

require 'kaitai/struct/struct'

unless Gem::Version.new(Kaitai::Struct::VERSION) >= Gem::Version.new('0.9')
  raise "Incompatible Kaitai Struct Ruby API: 0.9 or later is required, but you have #{Kaitai::Struct::VERSION}"
end

class DnsPacket < Kaitai::Struct::Struct

  RR_TYPE = {
    1 => :rr_type_a,
    2 => :rr_type_ns,
    5 => :rr_type_cname,
    6 => :rr_type_soa,
    28 => :rr_type_aaaa,
    41 => :rr_type_opt,
    43 => :rr_type_ds,
    46 => :rr_type_rrsig,
    48 => :rr_type_key,
    50 => :rr_type_nsec3,
  }
  I__RR_TYPE = RR_TYPE.invert
  def initialize(_io, _parent = nil, _root = self)
    super(_io, _parent, _root)
    _read
  end

  def _read
    @transaction_id = @_io.read_u2be
    @flags = @_io.read_u2be
    @qdcount = @_io.read_u2be
    @ancount = @_io.read_u2be
    @nscount = @_io.read_u2be
    @arcount = @_io.read_u2be
    @queries = Array.new(qdcount)
    (qdcount).times { |i|
      @queries[i] = Query.new(@_io, self, @_root)
    }
    @answers = Array.new(ancount)
    (ancount).times { |i|
      @answers[i] = ResourceRecord.new(@_io, self, @_root)
    }
    @authorities = Array.new(nscount)
    (nscount).times { |i|
      @authorities[i] = ResourceRecord.new(@_io, self, @_root)
    }
    @additionals = Array.new(arcount)
    (arcount).times { |i|
      @additionals[i] = ResourceRecord.new(@_io, self, @_root)
    }
    self
  end
  class Map < Kaitai::Struct::Struct
    def initialize(_io, _parent = nil, _root = self)
      super(_io, _parent, _root)
      _read
    end

    def _read
      @map_num = @_io.read_u1
      @length = @_io.read_u1
      @map_bits = (@_io.read_bytes(length)).force_encoding("utf-8")
      self
    end
    attr_reader :map_num
    attr_reader :length
    attr_reader :map_bits
  end
  class ResourceRecord < Kaitai::Struct::Struct
    def initialize(_io, _parent = nil, _root = self)
      super(_io, _parent, _root)
      _read
    end

    def _read
      @name = Domain.new(@_io, self, @_root)
      @type = Kaitai::Struct::Stream::resolve_enum(DnsPacket::RR_TYPE, @_io.read_u2be)
      case type
      when :rr_type_a
        @body = RrBodyA.new(@_io, self, @_root)
      when :rr_type_ds
        @body = RrBodyDs.new(@_io, self, @_root)
      when :rr_type_ns
        @body = RrBodyNs.new(@_io, self, @_root)
      when :rr_type_key
        @body = RrBodyKey.new(@_io, self, @_root)
      when :rr_type_cname
        @body = RrBodyCname.new(@_io, self, @_root)
      when :rr_type_opt
        @body = RrBodyOpt.new(@_io, self, @_root)
      when :rr_type_rrsig
        @body = RrBodyRrsig.new(@_io, self, @_root)
      when :rr_type_nsec3
        @body = RrBodyNsec3.new(@_io, self, @_root)
      when :rr_type_aaaa
        @body = RrBodyAaaa.new(@_io, self, @_root)
      when :rr_type_soa
        @body = RrBodySoa.new(@_io, self, @_root)
      end
      self
    end
    attr_reader :name
    attr_reader :type
    attr_reader :body
  end
  class RrBodyOpt < Kaitai::Struct::Struct
    def initialize(_io, _parent = nil, _root = self)
      super(_io, _parent, _root)
      _read
    end

    def _read
      @udp_payload_size = @_io.read_u2be
      @higher_bits_in_extended_rcode = @_io.read_u1
      @edns0version = @_io.read_u1
      @z = @_io.read_u2be
      @data_length = @_io.read_u2be
      self
    end
    attr_reader :udp_payload_size
    attr_reader :higher_bits_in_extended_rcode
    attr_reader :edns0version
    attr_reader :z
    attr_reader :data_length
  end
  class RrBodyKey < Kaitai::Struct::Struct
    def initialize(_io, _parent = nil, _root = self)
      super(_io, _parent, _root)
      _read
    end

    def _read
      @class_ = @_io.read_u2be
      self
    end
    attr_reader :class_
  end
  class Domain < Kaitai::Struct::Struct
    def initialize(_io, _parent = nil, _root = self)
      super(_io, _parent, _root)
      _read
    end

    def _read
      @name = []
      i = 0
      begin
        _ = Word.new(@_io, self, @_root)
        @name << _
        i += 1
      end until  ((_.length == 0) || (_.length >= 192)) 
      self
    end
    attr_reader :name
  end
  class Ipv6Address < Kaitai::Struct::Struct
    def initialize(_io, _parent = nil, _root = self)
      super(_io, _parent, _root)
      _read
    end

    def _read
      @ip_v6 = @_io.read_bytes(16)
      self
    end
    attr_reader :ip_v6
  end
  class Query < Kaitai::Struct::Struct
    def initialize(_io, _parent = nil, _root = self)
      super(_io, _parent, _root)
      _read
    end

    def _read
      @name = Domain.new(@_io, self, @_root)
      @type = Kaitai::Struct::Stream::resolve_enum(DnsPacket::RR_TYPE, @_io.read_u2be)
      @query_class = @_io.read_u2be
      self
    end
    attr_reader :name
    attr_reader :type
    attr_reader :query_class
  end
  class RrBodyRrsig < Kaitai::Struct::Struct
    def initialize(_io, _parent = nil, _root = self)
      super(_io, _parent, _root)
      _read
    end

    def _read
      @class_ = @_io.read_u2be
      @time_to_live = @_io.read_u4be
      @data_length = @_io.read_u2be
      @type_cov = @_io.read_u2be
      @alg = @_io.read_u1
      @labels = @_io.read_u1
      @orig_time_to_live = @_io.read_u4be
      @sig_exp = @_io.read_u4be
      @sig_inception = @_io.read_u4be
      @key_tag = @_io.read_u2be
      @sign_name = Domain.new(@_io, self, @_root)
      @signature = (@_io.read_bytes(256)).force_encoding("utf-8")
      self
    end
    attr_reader :class_
    attr_reader :time_to_live
    attr_reader :data_length
    attr_reader :type_cov
    attr_reader :alg
    attr_reader :labels
    attr_reader :orig_time_to_live
    attr_reader :sig_exp
    attr_reader :sig_inception
    attr_reader :key_tag
    attr_reader :sign_name
    attr_reader :signature
  end
  class Ipv4Address < Kaitai::Struct::Struct
    def initialize(_io, _parent = nil, _root = self)
      super(_io, _parent, _root)
      _read
    end

    def _read
      @ip = @_io.read_bytes(4)
      self
    end
    attr_reader :ip
  end
  class RrBodyCname < Kaitai::Struct::Struct
    def initialize(_io, _parent = nil, _root = self)
      super(_io, _parent, _root)
      _read
    end

    def _read
      @class_ = @_io.read_u2be
      @time_to_live = @_io.read_u4be
      @data_length = @_io.read_u2be
      @cname = Domain.new(@_io, self, @_root)
      self
    end
    attr_reader :class_
    attr_reader :time_to_live
    attr_reader :data_length
    attr_reader :cname
  end
  class RrBodyAaaa < Kaitai::Struct::Struct
    def initialize(_io, _parent = nil, _root = self)
      super(_io, _parent, _root)
      _read
    end

    def _read
      @class_ = @_io.read_u2be
      @time_to_live = @_io.read_u4be
      @data_length = @_io.read_u2be
      @address = Ipv6Address.new(@_io, self, @_root)
      self
    end
    attr_reader :class_
    attr_reader :time_to_live
    attr_reader :data_length
    attr_reader :address
  end
  class RrBodyNs < Kaitai::Struct::Struct
    def initialize(_io, _parent = nil, _root = self)
      super(_io, _parent, _root)
      _read
    end

    def _read
      @class_ = @_io.read_u2be
      @time_to_live = @_io.read_u4be
      @data_length = @_io.read_u2be
      @name_server = Domain.new(@_io, self, @_root)
      self
    end
    attr_reader :class_
    attr_reader :time_to_live
    attr_reader :data_length
    attr_reader :name_server
  end
  class RrBodyDs < Kaitai::Struct::Struct
    def initialize(_io, _parent = nil, _root = self)
      super(_io, _parent, _root)
      _read
    end

    def _read
      @class_ = @_io.read_u2be
      @time_to_live = @_io.read_u4be
      @data_length = @_io.read_u2be
      @keyid = @_io.read_u2be
      @alg = @_io.read_u1
      @digest_type = @_io.read_u1
      @digest = (@_io.read_bytes(32)).force_encoding("utf-8")
      self
    end
    attr_reader :class_
    attr_reader :time_to_live
    attr_reader :data_length
    attr_reader :keyid
    attr_reader :alg
    attr_reader :digest_type
    attr_reader :digest
  end
  class RrBodyNsec3 < Kaitai::Struct::Struct
    def initialize(_io, _parent = nil, _root = self)
      super(_io, _parent, _root)
      _read
    end

    def _read
      @class_ = @_io.read_u2be
      @time_to_live = @_io.read_u4be
      @data_length = @_io.read_u2be
      @alg = @_io.read_u1
      @flags = @_io.read_u1
      @iterations = @_io.read_u2be
      @salt_length = @_io.read_u1
      @hash_length = @_io.read_u1
      @next_hash = (@_io.read_bytes(hash_length)).force_encoding("utf-8")
      @type_map = Map.new(@_io, self, @_root)
      self
    end
    attr_reader :class_
    attr_reader :time_to_live
    attr_reader :data_length
    attr_reader :alg
    attr_reader :flags
    attr_reader :iterations
    attr_reader :salt_length
    attr_reader :hash_length
    attr_reader :next_hash
    attr_reader :type_map
  end
  class RrBodyA < Kaitai::Struct::Struct
    def initialize(_io, _parent = nil, _root = self)
      super(_io, _parent, _root)
      _read
    end

    def _read
      @class_ = @_io.read_u2be
      @time_to_live = @_io.read_u4be
      @data_length = @_io.read_u2be
      @address = Ipv4Address.new(@_io, self, @_root)
      self
    end
    attr_reader :class_
    attr_reader :time_to_live
    attr_reader :data_length
    attr_reader :address
  end
  class Word < Kaitai::Struct::Struct
    def initialize(_io, _parent = nil, _root = self)
      super(_io, _parent, _root)
      _read
    end

    def _read
      @length = @_io.read_u1
      if is_ref
        @ref = @_io.read_u1
      end
      if !(is_ref)
        @letters = (@_io.read_bytes(length)).force_encoding("utf-8")
      end
      self
    end
    def is_ref
      return @is_ref unless @is_ref.nil?
      @is_ref = length == 192
      @is_ref
    end
    attr_reader :length
    attr_reader :ref
    attr_reader :letters
  end
  class RrBodySoa < Kaitai::Struct::Struct
    def initialize(_io, _parent = nil, _root = self)
      super(_io, _parent, _root)
      _read
    end

    def _read
      @class_ = @_io.read_u2be
      @time_to_live = @_io.read_u4be
      @data_length = @_io.read_u2be
      @primary_name_server = Domain.new(@_io, self, @_root)
      @reponsible_authority = Domain.new(@_io, self, @_root)
      @serial_number = @_io.read_u4be
      @refresh_interval = @_io.read_u4be
      @retry_interval = @_io.read_u4be
      @expire_limit = @_io.read_u4be
      @minimum_ttl = @_io.read_u4be
      self
    end
    attr_reader :class_
    attr_reader :time_to_live
    attr_reader :data_length
    attr_reader :primary_name_server
    attr_reader :reponsible_authority
    attr_reader :serial_number
    attr_reader :refresh_interval
    attr_reader :retry_interval
    attr_reader :expire_limit
    attr_reader :minimum_ttl
  end
  attr_reader :transaction_id
  attr_reader :flags
  attr_reader :qdcount
  attr_reader :ancount
  attr_reader :nscount
  attr_reader :arcount
  attr_reader :queries
  attr_reader :answers
  attr_reader :authorities
  attr_reader :additionals
end
