#include <ts_processor/ts/packet.hpp>
#include <bitfield/byte_type.hpp>

namespace ts_processor { namespace ts {
    namespace {
        constexpr bitfield::byte_type _ADAPTATION_OFFSET =
            bitfield::bit_type(packet::continuity_counter_type::NEXT_OFFSET).byte();
    }
}}

// packet::adaptation_field_container_type
namespace ts_processor { namespace ts {
    const uint8_t * packet::adaptation_field_container_type::base_addr() const {
        switch (this->parent()->adaptation_field_control) {
        case 0b10: case 0b11:
            return _ADAPTATION_OFFSET.addr(this);
        default:
            return nullptr;
        }
    }
    
    std::size_t packet::adaptation_field_container_type::size() const {
        if (this->fieldset() == nullptr) return 0;
        return this->fieldset()->adaptation_field_length + 1;
    }
}}

// packet::payload_container_type
namespace ts_processor { namespace ts {
    const uint8_t * packet::payload_container_type::base_addr() const {
        switch (this->parent()->adaptation_field_control) {
        case 0b01:
            return _ADAPTATION_OFFSET.addr(this);
        case 0b11:
            return _ADAPTATION_OFFSET
                .add(this->parent()->adaptation_field.size())
                .addr(this);
        default:
            return nullptr;
        }
    }
    
    std::size_t packet::payload_container_type::size() const {
        if (this->fieldset() == nullptr) return 0;
        return packet::SIZE - this->offset();
    }
}}
