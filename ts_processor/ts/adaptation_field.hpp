#ifndef __INCLUDED_TS_PROCESSOR_TS_ADAPTATION_FIELD_HPP__
#define __INCLUDED_TS_PROCESSOR_TS_ADAPTATION_FIELD_HPP__

#include <bitfield/field.hpp>

namespace ts_processor { namespace ts {
    // see: ISO/IEC 13818-1, 2.4.3.5, Table 2-6
    union adaptation_field {
        using adaptation_field_length_type = bitfield::field<8>;
        
        adaptation_field_length_type  adaptation_field_length;
        
        // futures: The more definition of the adaptation_field.
    };
}}

#endif // __INCLUDED_TS_PROCESSOR_TS_ADAPTATION_FIELD_HPP__
