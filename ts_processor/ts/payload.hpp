#ifndef __INCLUDED_TS_PROCESSOR_TS_PAYLOAD__
#define __INCLUDED_TS_PROCESSOR_TS_PAYLOAD__

#include <ts_processor/ts/psi/base.hpp>
#include <ts_processor/ts/pes/base.hpp>
#include <bitfield/field.hpp>
#include <bitfield/section/base.hpp>

namespace ts_processor { namespace ts {
    union payload {
        using pointer_field_type = uint8_t;
        
        struct psi_section_type: public bitfield::section::base<psi_section_type, psi::base, payload> {
            const uint8_t * base_addr() const;
            std::size_t length() const;
        };
        
        enum class type: uint8_t {
            none,
            psi,
            pes,
        };
        
        pointer_field_type pointer_field;
        psi_section_type psi;
        pes::base pes;
        
        std::size_t data_length() const;
        std::ptrdiff_t data_offset() const;
        type data_type() const;
    };
}}

#endif //__INCLUDED_TS_PROCESSOR_TS_PAYLOAD__
