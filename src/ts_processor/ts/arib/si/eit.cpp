#include <ts_processor/ts/arib/si/eit.hpp>

// eit::event_type
namespace ts_processor { namespace ts { namespace arib { namespace si {
    std::size_t eit::event_type::length() const {
        return descriptors_loop_length_type::next_bytes()
            .add(this->descriptors_loop_length.get());
    }
}}}}

// eit::event_type::descriptor_list_type
namespace ts_processor { namespace ts { namespace arib { namespace si {
    const uint8_t * eit::event_type::descroptor_list_type::base_addr() const {
        return event_type::descriptors_loop_length_type::next_bytes().addr(this);
    }
    
    std::size_t eit::event_type::descroptor_list_type::length() const {
        return this->parent()->descriptors_loop_length;
    }
}}}}

// eit::event_list_type
namespace ts_processor { namespace ts { namespace arib { namespace si {
    const uint8_t * eit::event_list_type::base_addr() const {
        return eit::last_table_id_type::next_bytes().addr(this);
    }
    
    std::size_t eit::event_list_type::length() const {
        return this->parent()->section_length -
            eit::last_table_id_type::next_bytes() - this->offset_from_parent() - 1;
    }
}}}}
