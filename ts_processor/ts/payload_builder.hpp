#ifndef __INCLUDED_TS_PROCESSOR_TS_PAYLOAD_BUILDER_HPP__
#define __INCLUDED_TS_PROCESSOR_TS_PAYLOAD_BUILDER_HPP__

#include <ts_processor/ts/packet.hpp>
#include <bitfield/container/vector.hpp>
#include <string>
#include <exception>

namespace ts_processor { namespace ts {
    class payload_builder {
        bitfield::container::vector container;
        int32_t pid;
        std::size_t n;
        
    public:
        struct invalid_sync_byte_exception: public std::invalid_argument {
            invalid_sync_byte_exception(const std::string & m) : std::invalid_argument(m) {}
        };
        
        struct invalid_pid_exeption: public std::invalid_argument {
            invalid_pid_exeption(const std::string & m) : std::invalid_argument(m) {}
        };
        
        struct invalid_payload_unit_start_indicator_exception: public std::invalid_argument {
            invalid_payload_unit_start_indicator_exception(const std::string & m) : std::invalid_argument(m) {}
        };
        
        payload_builder() : pid(-1), n(0) {}
        
        void push(const ts::packet & packet);
        const ts::payload * payload() const;
        std::size_t size() const;
        int32_t current_pid() const;
        bool empty() const;
        void clear();
    };
}}

#endif // __INCLUDED_TS_PROCESSOR_TS_PAYLOAD_BUILDER_HPP__
