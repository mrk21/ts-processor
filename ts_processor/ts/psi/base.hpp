#ifndef __INCLUDED_TS_PROCESSOR_TS_PSI_BASE_HPP__
#define __INCLUDED_TS_PROCESSOR_TS_PSI_BASE_HPP__

#include <bitfield/field.hpp>

namespace ts_processor { namespace ts { namespace psi {
    // PSI/SI common fields
    // Member variables of the derived class will be assigned without padding from 4th bytes of this address.
    // size: 24 bits = 3 bytes
    struct base {
        using table_id_type                 =                           bitfield::field< 8>;
        using section_syntax_indicator_type =                 table_id_type::next_field< 1>;
        using private_bit_type              = section_syntax_indicator_type::next_field< 1>;
        using reserved1_type                =              private_bit_type::next_field< 2>;
        using section_length_type           =                reserved1_type::next_field<12>;
        using container_type = section_length_type::container_type;
        
        union {
            container_type container;
            
            table_id_type                 table_id;
            section_syntax_indicator_type section_syntax_indicator;
            private_bit_type              private_bit;
            reserved1_type                reserved1;
            section_length_type           section_length;
        };
    };
}}}

#endif // __INCLUDED_TS_PROCESSOR_TS_PSI_BASE_HPP__
