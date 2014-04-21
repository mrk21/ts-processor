#include <ts_processor/ts/packet.hpp>
#include <bitfield/byte_type.hpp>
#include <algorithm>

namespace ts_processor { namespace ts {
    namespace {
        constexpr bitfield::byte_type _ADAPTATION_OFFSET =
            bitfield::bit_type(packet::continuity_counter_type::NEXT_OFFSET).byte();
    }
    
    packet::packet(bitfield::container::initializer_list list) {
        std::copy(list.begin(), list.end(), this->container.begin());
    }
    
    packet & packet::operator =(bitfield::container::initializer_list list) {
        std::copy(list.begin(), list.end(), this->container.begin());
        return *this;
    }
}}

// packet::adaptation_field_section_type
namespace ts_processor { namespace ts {
    const uint8_t * packet::adaptation_field_section_type::base_addr() const {
        switch (this->parent()->adaptation_field_control) {
        case 0b10: case 0b11:
            return _ADAPTATION_OFFSET.addr(this);
        default:
            return nullptr;
        }
    }
    
    std::size_t packet::adaptation_field_section_type::length() const {
        if (this->fieldset() == nullptr) return 0;
        return this->fieldset()->adaptation_field_length + 1;
    }
}}

// packet::payload_section_type
namespace ts_processor { namespace ts {
    const uint8_t * packet::payload_section_type::base_addr() const {
        switch (this->parent()->adaptation_field_control) {
        case 0b01:
            return _ADAPTATION_OFFSET.addr(this);
        case 0b11:
            return _ADAPTATION_OFFSET
                .add(this->parent()->adaptation_field.length())
                .addr(this);
        default:
            return nullptr;
        }
    }
    
    std::size_t packet::payload_section_type::length() const {
        if (this->fieldset() == nullptr) return 0;
        return packet::SIZE - this->offset();
    }
}}
