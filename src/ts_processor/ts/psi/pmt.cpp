#include <ts_processor/ts/psi/pmt.hpp>

// pmt::program_info_list_type
namespace ts_processor { namespace ts { namespace psi {
    const uint8_t * pmt::program_info_list_type::base_addr() const {
        return program_info_length_type::next_bytes().addr(this);
    }
    
    std::size_t pmt::program_info_list_type::length() const {
        return this->parent()->program_info_length;
    }
}}}

// pmt::section_type
namespace ts_processor { namespace ts { namespace psi {
    std::size_t pmt::section_type::length() const {
        return es_info_length_type::next_bytes() + this->es_info_length.get();
    }
}}}

// pmt::section_type::es_info_list_type
namespace ts_processor { namespace ts { namespace psi {
    const uint8_t * pmt::section_type::es_info_list_type::base_addr() const {
        return es_info_length_type::next_bytes().addr(this);
    }
    
    std::size_t pmt::section_type::es_info_list_type::length() const {
        return this->parent()->es_info_length;
    }
}}}

// pmt::section_list_type
namespace ts_processor { namespace ts { namespace psi {
    namespace {
        auto program_info_offset_(const pmt::section_list_type * sections) {
            return pmt::program_info_length_type::next_bytes()
                .add(sections->parent()->program_info_length.get());
        }
    }
    
    const uint8_t * pmt::section_list_type::base_addr() const {
        return program_info_offset_(this).addr(this);
    }
    
    std::size_t pmt::section_list_type::length() const {
        return this->parent()->section_length -
            program_info_offset_(this).byte() - this->offset_from_parent() - 1;
    }
}}}
