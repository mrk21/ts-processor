#include <ts_processor/ts/packet.hpp>
#include <bitfield/byte_type.hpp>

namespace ts_processor { namespace ts {
    namespace {
        constexpr bitfield::byte_type _ADAPTATION_OFFSET =
            bitfield::bit_type(packet::continuity_counter_type::NEXT_OFFSET).byte();
    }
    
    ts::adaptation_field * packet::adaptation_field() {
        switch (this->adaptation_field_control) {
        case 0b10: case 0b11:
            return _ADAPTATION_OFFSET.addr<ts::adaptation_field>(this);
        default:
            return nullptr;
        }
    }
    
    ts::payload * packet::payload() {
        switch (this->adaptation_field_control) {
        case 0b01:
            return _ADAPTATION_OFFSET.addr<ts::payload>(this);
        case 0b11:
            return _ADAPTATION_OFFSET
                .add(this->adaptation_field()->adaptation_field_length + 1)
                .addr<ts::payload>(this);
        default:
            return nullptr;
        }
    }
}}
