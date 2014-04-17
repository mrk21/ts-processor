#ifndef __INCLUDED_TS_PROCESSOR_TS_PAYLOAD_BUILDER_HPP__
#define __INCLUDED_TS_PROCESSOR_TS_PAYLOAD_BUILDER_HPP__

#include <ts_processor/ts/packet.hpp>
#include <bitfield/container/vector.hpp>
#include <string>
#include <exception>
#include <bitset>

namespace ts_processor { namespace ts {
    class payload_builder {
        bitfield::container::vector container;
        int32_t pid;
        std::size_t n;
        int32_t length;
        
    public:
        enum status {
            PUSHED,
            COMPLETED,
            INVALID,
            INVALID_SYNC_BYTE,
            INVALID_PID,
            INVALID_PAYLOAD_UNIT_START_INDICATOR,
            
            SIZE
        };
        using status_set = std::bitset<status::SIZE>;
        
        payload_builder(int32_t pid = -1) : pid(pid), n(0) {}
        
        status_set push(const ts::packet & packet);
        const ts::payload * payload() const;
        std::size_t size() const;
        int32_t current_pid() const;
        bool empty() const;
        void clear();
    };
}}

#endif // __INCLUDED_TS_PROCESSOR_TS_PAYLOAD_BUILDER_HPP__
