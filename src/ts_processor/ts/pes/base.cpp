#include <ts_processor/ts/pes/base.hpp>

namespace ts_processor { namespace ts { namespace pes {
    std::size_t base::length() const {
        return sizeof(base) + this->pes_packet_length;
    }
}}}
