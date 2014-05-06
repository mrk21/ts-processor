#include <ts_processor/ts/psi/pmt.hpp>
#include <bitfield/byte_type.hpp>

// pmt::section_type
namespace ts_processor { namespace ts { namespace psi {
    std::size_t pmt::section_type::length() const {
        static constexpr uint32_t _OFFSET =
            bitfield::bit_type(es_info_length_type::NEXT_OFFSET).byte();
        
        return _OFFSET + this->es_info_length;
    }
}}}

// pmt::section_list_type
namespace ts_processor { namespace ts { namespace psi {
    namespace {
        bitfield::byte_type _sections_offset(const pmt::section_list_type * sections) {
            static constexpr uint32_t _PROGRAM_INFO_OFSET =
                bitfield::bit_type(pmt::program_info_length_type::NEXT_OFFSET).byte();
            
            return _PROGRAM_INFO_OFSET + sections->parent()->program_info_length;
        }
    }
    
    const uint8_t * pmt::section_list_type::base_addr() const {
        return _sections_offset(this).addr(this);
    }
    
    std::size_t pmt::section_list_type::length() const {
        return this->parent()->section_length - _sections_offset(this).byte() - this->offset_from_parent() - 1;
    }
}}}
