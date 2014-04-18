#include <ts_processor/ts/payload.hpp>
#include <bitfield/byte_type.hpp>

namespace ts_processor { namespace ts {
    std::size_t payload::data_length() const {
        switch (this->data_type()) {
        case type::pes:
            return sizeof(pes::base) + this->pes.pes_packet_length;
        case type::psi:
            return sizeof(psi::base) + this->psi->section_length;
        default:
            return 0;
        }
    }
    
    std::ptrdiff_t payload::data_offset() const {
        switch (this->data_type()) {
        case type::psi:
            return sizeof(pointer_field_type) + this->pointer_field;
        default:
            return 0;
        }
    }
    
    payload::type payload::data_type() const {
        return this->pes.packet_start_code_prefix == 0x000001 ? type::pes : type::psi;
    }
}}

// payload::psi_section_type
namespace ts_processor { namespace ts {
    const uint8_t * payload::psi_section_type::base_addr() const {
        return bitfield::byte_type(this->parent()->data_offset()).addr(this);
    }
    
    std::size_t payload::psi_section_type::length() const {
        return sizeof(psi::base);
    }
}}
