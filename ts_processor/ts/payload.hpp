#ifndef __INCLUDED_TS_PROCESSOR_TS_PAYLOAD__
#define __INCLUDED_TS_PROCESSOR_TS_PAYLOAD__

#include <ts_processor/ts/psi/base.hpp>
#include <ts_processor/ts/psi/pat.hpp>
#include <ts_processor/ts/psi/pmt.hpp>
#include <ts_processor/ts/pes/base.hpp>
#include <bitfield/field.hpp>

namespace ts_processor { namespace ts {
    union payload {
        // PSI/SI
        struct {
            uint8_t pointer_field;
            union {
                psi::base psi;
                psi::pat pat;
                psi::pmt pmt;
            };
        };
        
        pes::base pes;
        
        std::size_t length() const;
        
        // futures: The definition of the payload.
    };
}}

#endif //__INCLUDED_TS_PROCESSOR_TS_PAYLOAD__
