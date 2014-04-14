#include <ts_processor/ts/payload_builder.hpp>
#include <iterator>
#include <algorithm>
#include <exception>

namespace ts_processor { namespace ts {
    void payload_builder::push(const ts::packet & packet) {
        if (packet.sync_byte != 0x47) {
            throw invalid_sync_byte_exception("A sync byte of the packet isn't 0x47!");
        }
        
        if (this->empty()) {
            if (packet.payload_unit_start_indicator == 0) {
                throw invalid_payload_unit_start_indicator_exception("A payload unit start indicator of the packet is 0!");
            }
            
            this->pid = packet.pid;
        }
        else {
            if (packet.pid != this->pid) {
                throw invalid_pid_exeption("A PID of the packet is difference!");
            }
            
            if (packet.payload_unit_start_indicator == 1) {
                throw invalid_payload_unit_start_indicator_exception("A payload unit start indicator of the packet is 1!");
            }
        }
        
        std::copy(
            packet.payload.begin(),
            packet.payload.end(),
            std::back_insert_iterator<decltype(this->container)>(this->container)
        );
        
        ++this->n;
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
