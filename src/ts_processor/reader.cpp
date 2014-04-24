#include <ts_processor/reader.hpp>

namespace ts_processor {
    bool reader::read(ts::packet & packet) {
        this->is.read(reinterpret_cast<char *>(packet.container.data()), ts::packet::SIZE);
        if (packet.sync_byte != 0x47) return false;
        return this->is.good();
    }
    
    void reader::each(std::function<bool(ts::packet &)> callback) {
        ts::packet packet;
        while (this->read(packet) && callback(packet));
    }
}
