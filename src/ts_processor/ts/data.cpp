#include <ts_processor/ts/data.hpp>
#include <algorithm>
#include <iterator>

namespace ts_processor { namespace ts {
    data::push_states data::push(const ts::packet & packet) {
        push_states states = this->validate(packet);
        
        if (states.count() > 0) return states;
        
        auto & payload = packet.payload;
        auto begin = payload.begin();
        auto end = payload.end();
        
        if (this->container_.empty()) {
            this->data_length = payload->data_length();
            this->data_type_ = payload->data_type();
            begin += payload->data_offset();
        }
        
        std::size_t remainder_length = this->data_length - this->container_.size();
        std::size_t payload_length = end - begin;
        
        if (remainder_length < payload_length) {
            end = begin + remainder_length;
        }
        
        std::copy(begin, end, std::back_insert_iterator<decltype(this->container_)>(this->container_));
        states.set(push_state::pushed);
        
        if (this->container_.size() == this->data_length) {
            states.set(push_state::ready);
            this->is_ready_ = true;
        }
        
        return states;
    }
    
    data::push_states data::validate(const ts::packet & packet) {
        push_states states;
        
        if (packet.sync_byte != 0x47) {
            states.set(push_state::invalid);
            states.set(push_state::invalid_sync_byte);
            return states;
        }
        
        if (packet.pid != this->pid_) {
            states.set(push_state::invalid);
            states.set(push_state::invalid_pid);
        }
        
        if (this->container_.empty()) {
            if (packet.payload_unit_start_indicator == 0) {
                states.set(push_state::invalid);
                states.set(push_state::invalid_payload_unit_start_indicator);
            }
        }
        else {
            if (packet.payload_unit_start_indicator == 1) {
                states.set(push_state::invalid);
                states.set(push_state::invalid_payload_unit_start_indicator);
            }
            if (this->container_.size() == this->data_length) {
                states.set(push_state::ready);
            }
        }
        
        return states;
    }
    
    void data::reset(uint32_t pid) {
        this->container_.clear();
        this->pid_ = pid;
        this->data_length = 0;
        this->data_type_ = type::none;
        this->is_ready_ = false;
    }
    
    
    std::size_t data::length() const {
        return this->container_.size();
    }
    
    uint32_t data::pid() const {
        return this->pid_;
    }
    
    data::type data::data_type() const {
        return this->data_type_;
    }
    
    bool data::is_ready() const {
        return this->is_ready_;
    }
    
    
    data::fieldset_type * data::fieldset() {
        return const_cast<fieldset_type *>(const_cast<const data *>(this)->fieldset());
    }
    data::fieldset_type * data::operator ->() { return  this->fieldset(); }
    data::fieldset_type & data::operator  *() { return *this->fieldset(); }
    
    const data::fieldset_type * data::fieldset() const {
        return this->is_ready() ? (const fieldset_type *)&this->container_[0] : nullptr;
    }
    const data::fieldset_type * data::operator ->() const { return  this->fieldset(); }
    const data::fieldset_type & data::operator  *() const { return *this->fieldset(); }
    
    const data::container_type & data::container() const {
        return this->container_;
    }
}}
