#include <ts_processor/ts/psi/pmt.hpp>
#include <bitfield/byte_type.hpp>

// pmt::section_type
namespace ts_processor { namespace ts { namespace psi {
    std::size_t pmt::section_type::length() const {
        static constexpr uint32_t _OFFSET =
            bitfield::bit_type(es_info_length_type::NEXT_OFFSET).byte();
        
        return bitfield::byte_type(this->es_info_length).add(_OFFSET).byte();
    }
}}}

// pmt::section_container_type
namespace ts_processor { namespace ts { namespace psi {
    namespace {
        constexpr uint32_t _PROGRAM_INFO_OFSET =
            bitfield::bit_type(pmt::program_info_length_type::NEXT_OFFSET).byte();
        
        bitfield::byte_type _sections_offset(const pmt::section_container_type * target) {
            return bitfield::byte_type(
                ((pmt *)target)->program_info_length).add(_PROGRAM_INFO_OFSET);
        }
    }
    
    uint8_t * pmt::section_container_type::base_addr() {
        return _sections_offset(this).addr(this);
    }
    
    std::size_t pmt::section_container_type::length() const {
        return ((pmt *)this)->section_length - _sections_offset(this).add(1).byte();
    }
}}}
