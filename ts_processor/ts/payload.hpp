#ifndef __INCLUDED_TS_PROCESSOR_TS_PAYLOAD__
#define __INCLUDED_TS_PROCESSOR_TS_PAYLOAD__

#include <ts_processor/ts/psi/pat.hpp>
#include <bitfield/bitfield.hpp>
#include <array>

namespace ts_processor { namespace ts {
    union payload {
        struct {
            uint8_t pointer_field;
            psi::pat pat;
        };
        
        // futures: The definition of the payload.
    };
}}

#endif //__INCLUDED_TS_PROCESSOR_TS_PAYLOAD__
