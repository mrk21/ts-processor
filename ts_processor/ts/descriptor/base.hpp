#ifndef __INCLUDED_TS_PROCESSOR_TS_DESCRIPTOR_BASE_HPP__
#define __INCLUDED_TS_PROCESSOR_TS_DESCRIPTOR_BASE_HPP__

#include <ts_processor/ts/descriptor_tag.hpp>
#include <bitfield/field.hpp>

namespace ts_processor { namespace ts { namespace descriptor {
    // Descriptor common fields
    // Member variables of the derived class will be assigned without padding from 3rd bytes of this address.
    // size: 16 bits = 2 bytes
    // see: ISO/IEC 13818-1, 2.6.1
    struct base {
        using descriptor_tag_type    =                 bitfield::field<8>;
        using descriptor_length_type = descriptor_tag_type::next_field<8>;
        using container_type = descriptor_length_type::container_type;
        
        union {
            container_type container;
            
            descriptor_tag_type    descriptor_tag;
            descriptor_length_type descriptor_length;
        };
        
        std::size_t length() const;
        descriptor_tag::type type() const;
        
        template<class Descriptor>       Descriptor * get()       { return static_cast<      Descriptor *>(this); }
        template<class Descriptor> const Descriptor * get() const { return static_cast<const Descriptor *>(this); }
    };
}}}

#endif // __INCLUDED_TS_PROCESSOR_TS_DESCRIPTOR_BASE_HPP__
