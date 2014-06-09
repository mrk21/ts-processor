#include <ts_processor/ts/arib/si/eit.hpp>

// eit::event_type
namespace ts_processor { namespace ts { namespace arib { namespace si {
    std::size_t eit::event_type::length() const {
        return bitfield::bit_type(descriptors_loop_length_type::NEXT_OFFSET).byte() + this->descriptors_loop_length;
    }
}}}}

// eit::event_type::descriptor_list_type
namespace ts_processor { namespace ts { namespace arib { namespace si {
    const uint8_t * eit::event_type::descroptor_list_type::base_addr() const {
        return bitfield::bit_type(event_type::descriptors_loop_length_type::NEXT_OFFSET).addr(this);
    }
    std::size_t eit::event_type::descroptor_list_type::length() const {
        return this->parent()->descriptors_loop_length;
    }
}}}}

// eit::event_list_type
namespace ts_processor { namespace ts { namespace arib { namespace si {
    const uint8_t * eit::event_list_type::base_addr() const {
        return bitfield::bit_type(eit::last_table_id_type::NEXT_OFFSET).addr(this);
    }
    
    std::size_t eit::event_list_type::length() const {
        return this->parent()->section_length - bitfield::bit_type(eit::last_table_id_type::NEXT_OFFSET).byte() - this->offset_from_parent() - 1;
    }
}}}}
