#ifndef __INCLUDED_TS_PROCESSOR_TS_PSI_PAT_HPP__
#define __INCLUDED_TS_PROCESSOR_TS_PSI_PAT_HPP__

#include <ts_processor/ts/psi/base.hpp>
#include <symbolset/symbolset.hpp>
#include <bitfield/field.hpp>
#include <bitfield/section/list.hpp>
#include <cstddef>

namespace ts_processor { namespace ts { namespace psi {
    // see: ISO/IEC 13818-1, 2.4.4.3, Table 2-25
    struct pat: public base {
        using base_class = base;
        
        using transport_stream_id_type    =                         bitfield::field<16>;
        using reserved2_type              =    transport_stream_id_type::next_field< 2>;
        using version_number_type         =              reserved2_type::next_field< 5>;
        using current_next_indicator_type =         version_number_type::next_field< 1>;
        using section_number_type         = current_next_indicator_type::next_field< 8>;
        using last_section_number_type    =         section_number_type::next_field< 8>;
        
        SYMBOLSET_DEFINE(pid_type, (
            nit,
            pmt
        ))
        
        union section_type {
            using program_number_type =                 bitfield::field<16>;
            using reserved_type       = program_number_type::next_field< 3>;
            using pid_type            =       reserved_type::next_field<13>;
            
            program_number_type  program_number;
            reserved_type        reserved;
            pid_type             pid;
            
            constexpr std::size_t length() const { return sizeof(pid_type::container_type); }
            pat::pid_type type() const;
        };
        
        struct section_list_type: public bitfield::section::list<section_list_type, section_type, pat> {
            const uint8_t * base_addr() const;
            std::size_t length() const;
        };
        
        union {
            transport_stream_id_type    transport_stream_id;
            reserved2_type              reserved2;
            version_number_type         version_number;
            current_next_indicator_type current_next_indicator;
            section_number_type         section_number;
            last_section_number_type    last_section_number;
            
            section_list_type sections;
        };
    };
}}}

#endif // __INCLUDED_TS_PROCESSOR_TS_PSI_PAT_HPP__
