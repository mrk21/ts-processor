#include <ts_processor/ts/psi/pat.hpp>

// pat::section_type
namespace ts_processor { namespace ts { namespace psi {
    std::size_t pat::section_type::length() const {
        return bitfield::bit_type(pid_type::NEXT_OFFSET).byte();
    }
}}}

// pat::section_container_type
namespace ts_processor { namespace ts { namespace psi {
    namespace {
        constexpr bitfield::bit_type _SECTIONS_OFFSET =
            bitfield::bit_type(pat::last_section_number_type::NEXT_OFFSET);
    }
    
    uint8_t * pat::section_container_type::base_addr() {
        return _SECTIONS_OFFSET.addr(this);
    }
    
    std::size_t pat::section_container_type::length() const {
        static constexpr uint32_t _DIFF =
            _SECTIONS_OFFSET.diff(section_length_type::NEXT_OFFSET).add(32).byte();
        
        return ((const pat *)this)->section_length - _DIFF;
    }
}}}

