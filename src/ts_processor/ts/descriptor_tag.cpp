#include <ts_processor/ts/descriptor_tag.hpp>
#include <bitfield/bit_type.hpp>

namespace ts_processor { namespace ts {
    using bitfield::operator "" _bit;
    
    decltype(descriptor_tag::types) descriptor_tag::types;
    
    bool descriptor_tag::initialize() {
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
    
    descriptor_tag::type descriptor_tag::type_of(uint32_t id) {
        if (id > (8_bit).max_value()) return type::invalid;
        return self::types.at(id);
    }
    
    namespace {
        bool const _initialized = descriptor_tag::initialize();
    }
}}
