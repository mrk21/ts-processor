#include <ts_processor/ts/psi/base.hpp>
#include <bitfield/byte_type.hpp>

namespace ts_processor { namespace ts { namespace psi {
    std::size_t base::length() const {
        return sizeof(base) + this->section_length;
    }
    base::crc_32_type & base::crc_32() {
        return const_cast<crc_32_type &>(const_cast<const base *>(this)->crc_32());
    }
    
    const base::crc_32_type & base::crc_32() const {
        return *bitfield::byte_type(this->length())
            .diff(sizeof(crc_32_type::container_type))
            .addr<crc_32_type>(this);
    }
}}}
