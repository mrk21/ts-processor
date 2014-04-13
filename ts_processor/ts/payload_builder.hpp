#ifndef __INCLUDED_TS_PROCESSOR_TS_PAYLOAD_BUILDER_HPP__
#define __INCLUDED_TS_PROCESSOR_TS_PAYLOAD_BUILDER_HPP__

#include <ts_processor/ts/packet.hpp>
#include <bitfield/container/vector.hpp>

namespace ts_processor { namespace ts {
    class payload_builder {
        bitfield::container::vector container;
        
    public:
        void push(const ts::packet & packet);
        const ts::payload * payload() const;
        void clear();
    };
}}

#endif // __INCLUDED_TS_PROCESSOR_TS_PAYLOAD_BUILDER_HPP__
