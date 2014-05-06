#include <ts_processor/ts/descriptor/base.hpp>

namespace ts_processor { namespace ts { namespace descriptor {
    std::size_t base::length() const {
        return bitfield::bit_type(descriptor_length_type::NEXT_OFFSET).byte() + this->descriptor_length;
    }
    
    descriptor_tag::type base::type() const {
        return descriptor_tag::type_of(this->descriptor_tag);
    }
}}}
