#ifndef __INCLUDED_TS_PROCESSOR_TS_DATA_HPP__
#define __INCLUDED_TS_PROCESSOR_TS_DATA_HPP__

#include <ts_processor/ts/packet.hpp>
#include <ts_processor/ts/psi/pat.hpp>
#include <ts_processor/ts/psi/pmt.hpp>
#include <ts_processor/ts/arib/si/eit.hpp>
#include <bitfield/container/vector.hpp>
#include <bitset>

namespace ts_processor { namespace ts {
    class data {
    public:
        using type = payload::type;
        
        union fieldset_type {
            psi::pmt pmt;
            psi::pat pat;
            pes::base pes;
            
            arib::si::eit eit;
        };
        
        enum push_state: uint8_t {
            pushed,
            ready,
            invalid,
            invalid_sync_byte,
            invalid_pid,
            invalid_payload_unit_start_indicator,
            
            SIZE
        };
        
        using push_states = std::bitset<push_state::SIZE>;
        using container_type = bitfield::container::vector;
        
    private:
        container_type container_;
        uint32_t pid_;
        std::size_t data_length;
        type data_type_;
        bool is_ready_;
        
    public:
        data(uint32_t pid = 0) : pid_(pid), data_length(0), data_type_(type::none), is_ready_(false) {}
        
        push_states push(const ts::packet & packet);
        void reset(uint32_t pid = 0);
        
        std::size_t length() const;
        uint32_t pid() const;
        type data_type() const;
        bool is_ready() const;
        
        fieldset_type * fieldset();
        fieldset_type * operator ->();
        fieldset_type & operator *();
        
        const fieldset_type * fieldset() const;
        const fieldset_type * operator ->() const;
        const fieldset_type & operator *() const;
        
        const container_type & container() const;
        
    private:
        push_states validate(const ts::packet & packet);
    };
}}

#endif // __INCLUDED_TS_PROCESSOR_TS_DATA_HPP__
