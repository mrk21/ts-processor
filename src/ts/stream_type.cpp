#include <ts_processor/ts/stream_type.hpp>

namespace ts_processor { namespace ts {
    decltype(stream_type::tags) stream_type::tags;
    
    bool stream_type::initialize() {
        static bool initialized = false;
        if (initialized) return false;
        
        for (auto & record: self::database()) {
            switch (record.range.size()) {
            case 1:
                self::tags[record.range[0]] = record.info.tag;
                
            case 2:
                for (uint16_t id = record.range[0]; id <= record.range[1]; ++id) {
                    self::tags[id] = record.info.tag;
                }
            }
        }
        
        return initialized = true;
    }
    
    stream_type::tag stream_type::tag_of(uint32_t id) {
        return self::tags.at(id);
    }
    
    namespace {
        bool const _initialized = stream_type::initialize();
    }
}}
