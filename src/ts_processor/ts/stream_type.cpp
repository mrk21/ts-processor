#include <ts_processor/ts/stream_type.hpp>
#include <bitfield/bit_type.hpp>

namespace ts_processor { namespace ts {
    using bitfield::operator "" _bit;
    
    decltype(stream_type::types) stream_type::types;
    
    bool stream_type::initialize() {
        static bool initialized = false;
        if (initialized) return false;
        
        for (auto & record: self::database()) {
            switch (record.id.size()) {
            case 1:
                self::types[record.id[0]] = record.info.type;
                
            case 2:
                for (uint16_t id = record.id[0]; id <= record.id[1]; ++id) {
                    self::types[id] = record.info.type;
                }
            }
        }
        
        return initialized = true;
    }
    
    stream_type::type stream_type::type_of(uint32_t id) {
        if (id > (8_bit).max_value()) return type::invalid;
        return self::types.at(id);
    }
    
    namespace {
        bool const _initialized = stream_type::initialize();
    }
}}
