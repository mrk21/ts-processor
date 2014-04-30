#include <ts_processor/ts/pid.hpp>
#include <bitfield/bit_type.hpp>

namespace ts_processor { namespace ts {
    using bitfield::operator "" _bit;
    
    decltype(pid::types) pid::types;
    
    bool pid::initialize() {
        static bool initialized = false;
        if (initialized) return false;
        
        for (auto & record: self::database()) {
            switch (record.id.size()) {
            case 1:
                self::types[record.id[0]] = record.info.type;
                break;
                
            case 2:
                for (uint16_t id = record.id[0]; id <= record.id[1]; ++id) {
                    self::types[id] = record.info.type;
                }
                break;
            }
        }
        
        return initialized = true;
    }
    
    pid::type pid::type_of(uint32_t id) {
        if (id > (13_bit).max_value()) return type::invalid;
        return self::types.at(id);
    }
    
    namespace {
        bool _initialized = pid::initialize();
    }
}}
