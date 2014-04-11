#ifndef __INCLUDED_TS_PROCESSOR_TS_PSI_PMT_HPP__
#define __INCLUDED_TS_PROCESSOR_TS_PSI_PMT_HPP__

#include <bitfield/bitfield.hpp>
#include <bitfield/section/list.hpp>
#include <cstddef>

namespace ts_processor { namespace ts { namespace psi {
    // see: ISO/IEC 13818-1, 2.4.4.8, Table 2-28
    union pmt {
        using table_id_type                 =                           bitfield::bitfield< 8>;
        using section_syntax_indicator_type =                 table_id_type::next_bitfield< 1>;
        using _0_type                       = section_syntax_indicator_type::next_bitfield< 1>;
        using reserved1_type                =                       _0_type::next_bitfield< 2>;
        using section_length_type           =                reserved1_type::next_bitfield<12>;
        using program_number_type           =           section_length_type::next_bitfield<16>;
        using reserved2_type                =           program_number_type::next_bitfield< 2>;
        using version_number_type           =                reserved2_type::next_bitfield< 5>;
        using current_next_indicator_type   =           version_number_type::next_bitfield< 1>;
        using section_number_type           =   current_next_indicator_type::next_bitfield< 8>;
        using last_section_number_type      =           section_number_type::next_bitfield< 8>;
        using reserved3_type                =      last_section_number_type::next_bitfield< 3>;
        using pcr_pid_type                  =                reserved3_type::next_bitfield<13>;
        using reserved4_type                =                  pcr_pid_type::next_bitfield< 4>;
        using program_info_length_type      =                reserved4_type::next_bitfield<12>;
        
        union section_type {
            using stream_type_type    =                 bitfield::bitfield< 8>;
            using reserved1_type      =    stream_type_type::next_bitfield< 3>;
            using elementary_pid_type =      reserved1_type::next_bitfield<13>;
            using reserved2_type      = elementary_pid_type::next_bitfield< 4>;
            using es_info_length_type =      reserved2_type::next_bitfield<12>;
            
            stream_type_type     stream_type;
            reserved1_type       reserved1;
            elementary_pid_type  elementary_pid;
            reserved2_type       reserved2;
            es_info_length_type  es_info_length;
            
            std::size_t length() const;
            
            // futures: The definition of the descriptor.
        };
        
        struct section_container_type: public bitfield::section::list<section_container_type, section_type, pmt> {
            const uint8_t * base_addr() const;
            std::size_t length() const;
        };
        
        table_id_type                  table_id;
        section_syntax_indicator_type  section_syntax_indicator;
        _0_type                        _0;
        reserved1_type                 reserved1;
        section_length_type            section_length;
        program_number_type            program_number;
        reserved2_type                 reserved2;
        version_number_type            version_number;
        current_next_indicator_type    current_next_indicator;
        section_number_type            section_number;
        last_section_number_type       last_section_number;
        reserved3_type                 reserved3;
        pcr_pid_type                   pcr_pid;
        reserved4_type                 reserved4;
        program_info_length_type       program_info_length;
        
        section_container_type  sections;
        
        // futures: The definition of the descriptor.
    };
}}}

#endif // __INCLUDED_TS_PROCESSOR_TS_PSI_PMT_HPP__
