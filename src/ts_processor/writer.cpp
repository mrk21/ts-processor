#include <ts_processor/writer.hpp>

namespace ts_processor {
    bool writer::write(const ts::packet & packet) {
        if (packet.sync_byte != 0x47) return false;
        this->os.write(reinterpret_cast<const char *>(packet.container.data()), ts::packet::SIZE);
        return this->os.good();
    }
}
