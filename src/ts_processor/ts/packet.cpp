#include <ts_processor/ts/packet.hpp>
#include <bitfield/byte_type.hpp>
#include <bitfield/util.hpp>
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
    
    packet::packet(const ts::packet & packet) {
        *this = packet;
    }
    
    packet & packet::operator =(const ts::packet & packet) {
        std::copy(packet.container.begin(), packet.container.end(), this->container.begin());
        return *this;
    }
    
    bool operator ==(const ts::packet & rop, const ts::packet & lop) {
        return std::equal(rop.container.begin(), rop.container.end(), lop.container.begin());
    }
    
    bool operator !=(const ts::packet & rop, const ts::packet & lop) {
        return !(rop == lop);
    }
    
    std::ostream & operator <<(std::ostream & os, const ts::packet & packet) {
        return os << bitfield::util::hex_dump(packet.container);
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
