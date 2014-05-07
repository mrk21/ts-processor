#ifndef __INCLUDED_TS_PROCESSOR_TS_PES_BASE_HPP__
#define __INCLUDED_TS_PROCESSOR_TS_PES_BASE_HPP__

#include <bitfield/field.hpp>

namespace ts_processor { namespace ts { namespace pes {
    // PES common fields
    // Member variables of the derived class will be assigned without padding from 7th bytes of this address.
    // size: 48 bits = 6 bytes
    // see: ISO/IEC 13818-1, 2.4.3.7, Table 2-17
    struct base {
        using packet_start_code_prefix_type =                           bitfield::field<24>;
        using stream_id_type                = packet_start_code_prefix_type::next_field< 8>;
        using pes_packet_length_type        =                stream_id_type::next_field<16>;
        using container_type = pes_packet_length_type::container_type;
        
        union {
            container_type container;
            
            packet_start_code_prefix_type packet_start_code_prefix;
            stream_id_type                stream_id;
            pes_packet_length_type        pes_packet_length;
        };
        
        std::size_t length() const;
    };
}}}

#endif // __INCLUDED_TS_PROCESSOR_TS_PES_BASE_HPP__
