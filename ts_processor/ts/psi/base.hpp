#ifndef __INCLUDED_TS_PROCESSOR_TS_PSI_BASE_HPP__
#define __INCLUDED_TS_PROCESSOR_TS_PSI_BASE_HPP__

#include <bitfield/field.hpp>

namespace ts_processor { namespace ts { namespace psi {
    // PSI/SI common fields
    // Member variables of the derived class will be assigned without padding from 4th bytes of this address.
    // When not contained a CRC_32 on the derived class, you must delete the function as listed below:
    //   * const crc_32_type & crc_32() const = delete;
    // 
    // size: 24 bits = 3 bytes
    struct base {
        using table_id_type                 =                           bitfield::field< 8>;
        using section_syntax_indicator_type =                 table_id_type::next_field< 1>;
        using private_bit_type              = section_syntax_indicator_type::next_field< 1>;
        using reserved1_type                =              private_bit_type::next_field< 2>;
        using section_length_type           =                reserved1_type::next_field<12>;
        using container_type = section_length_type::container_type;
        
        using crc_32_type = bitfield::field<32>;
        
        union {
            container_type container;
            
            table_id_type                 table_id;
            section_syntax_indicator_type section_syntax_indicator;
            private_bit_type              private_bit;
            reserved1_type                reserved1;
            section_length_type           section_length;
        };
        
        std::size_t length() const;
        crc_32_type & crc_32();
        const crc_32_type & crc_32() const;
        
        template<class PSI>       PSI * get()       { return static_cast<      PSI *>(this); }
        template<class PSI> const PSI * get() const { return static_cast<const PSI *>(this); }
   };
}}}

#endif // __INCLUDED_TS_PROCESSOR_TS_PSI_BASE_HPP__
