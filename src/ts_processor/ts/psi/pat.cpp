#include <ts_processor/ts/psi/pat.hpp>

// pat::section_type
namespace ts_processor { namespace ts { namespace psi {
    pat::pid_type pat::section_type::type() const {
        return this->program_number == 0x0000 ?
            pat::pid_type::network : pat::pid_type::program_map;
    }
}}}

// pat::section_list_type
namespace ts_processor { namespace ts { namespace psi {
    const uint8_t * pat::section_list_type::base_addr() const {
        return pat::last_section_number_type::next_bytes().addr(this);
    }
    
    std::size_t pat::section_list_type::length() const {
        return this->parent()->section_length -
            pat::last_section_number_type::next_bytes() - pat::crc_32_type::size();
    }
}}}
