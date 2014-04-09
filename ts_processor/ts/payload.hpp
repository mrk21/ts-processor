#ifndef __INCLUDED_TS_PROCESSOR_TS_PAYLOAD__
#define __INCLUDED_TS_PROCESSOR_TS_PAYLOAD__

#include <bitfield/bitfield.hpp>
#include <array>

namespace ts_processor { namespace ts {
    union payload {
        std::array<uint8_t,1> container;
        
        // futures: The definition of the payload.
    };
}}

#endif //__INCLUDED_TS_PROCESSOR_TS_PAYLOAD__
