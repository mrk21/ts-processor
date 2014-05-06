#include <ts_processor/ts/psi/pat.hpp>

// pat::section_type
namespace ts_processor { namespace ts { namespace psi {
    pat::pid_type pat::section_type::type() const {
        return this->program_number == 0x0000 ? pat::pid_type::nit
                                              : pat::pid_type::pmt;
    }
}}}

// pat::section_list_type
namespace ts_processor { namespace ts { namespace psi {
    namespace {
        constexpr bitfield::bit_type _SECTIONS_OFFSET =
            bitfield::bit_type(pat::last_section_number_type::NEXT_OFFSET);
    }
    
    const uint8_t * pat::section_list_type::base_addr() const {
        return _SECTIONS_OFFSET.addr(this);
    }
    
    std::size_t pat::section_list_type::length() const {
        static constexpr uint32_t _DIFF = _SECTIONS_OFFSET.add(32).byte();
        
        return this->parent()->section_length - _DIFF;
    }
}}}
