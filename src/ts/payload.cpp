#include <ts_processor/ts/payload.hpp>

namespace ts_processor { namespace ts {
    std::size_t payload::length() const {
        return this->pes.packet_start_code_prefix == 0x000001 ?
            (sizeof(pes::base) + this->pes.pes_packet_length) :
            (sizeof(psi::base) + this->psi.section_length + sizeof(this->pointer_field));
    }
}}
