#include <ts_processor/ts/payload_builder.hpp>

namespace ts_processor { namespace ts {
    payload_builder::status_set payload_builder::push(const ts::packet & packet) {
        status_set result;
        
        if (packet.sync_byte != 0x47) {
            result.set(status::INVALID);
            result.set(status::INVALID_SYNC_BYTE);
            return result;
        }
        
        if (this->empty()) {
            if (packet.payload_unit_start_indicator == 0) {
                result.set(status::INVALID);
                result.set(status::INVALID_PAYLOAD_UNIT_START_INDICATOR);
            }
            else {
                if (this->pid == -1) this->pid = packet.pid;
                this->length = packet.payload->length();
            }
        }
        else {
            if (packet.pid != this->pid) {
                result.set(status::INVALID);
                result.set(status::INVALID_PID);
            }
            if (packet.payload_unit_start_indicator == 1) {
                result.set(status::INVALID);
                result.set(status::INVALID_PAYLOAD_UNIT_START_INDICATOR);
            }
            if (this->length <= 0) {
                result.set(status::COMPLETED);
            }
        }
        
        if (result.count() == 0) {
            for (auto v: packet.payload) this->container.push_back(v);
            this->length -= packet.payload.length();
            ++this->n;
            
            result.set(status::PUSHED);
            if (this->length <= 0) result.set(status::COMPLETED);
        }
        
        return result;
    }
    
    const ts::payload * payload_builder::payload() const {
        return this->empty() ? nullptr : (const ts::payload *)&this->container[0];
    }
    
    std::size_t payload_builder::size() const {
        return this->n;
    }
    
    int32_t payload_builder::current_pid() const {
        return this->pid;
    }
    
    bool payload_builder::empty() const {
        return this->container.empty();
    }
    
    void payload_builder::clear() {
        this->container.clear();
        this->n = 0;
        this->pid = -1;
    }
}}
