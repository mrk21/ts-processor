#ifndef __INCLUDED_TS_PROCESSOR_TS_PACKET_HPP__
#define __INCLUDED_TS_PROCESSOR_TS_PACKET_HPP__

#include <ts_processor/ts/adaptation_field.hpp>
#include <ts_processor/ts/payload.hpp>
#include <bitfield/field.hpp>
#include <bitfield/container/initializer_list.hpp>
#include <bitfield/section/base.hpp>
#include <iostream>

namespace ts_processor { namespace ts {
    // see: ISO/IEC 13818-1, 2.4.3.2, Table 2-2
    union packet {
        static constexpr std::size_t SIZE = 188;
        using container_type = bitfield::container::array<SIZE>;
        
        using sync_byte_type                    =                               bitfield::field< 8>;
        using transport_error_indicator_type    =                    sync_byte_type::next_field< 1>;
        using payload_unit_start_indicator_type =    transport_error_indicator_type::next_field< 1>;
        using transport_priority_type           = payload_unit_start_indicator_type::next_field< 1>;
        using pid_type                          =           transport_priority_type::next_field<13>;
        using transport_scrambling_control_type =                          pid_type::next_field< 2>;
        using adaptation_field_control_type     = transport_scrambling_control_type::next_field< 2>;
        using continuity_counter_type           =     adaptation_field_control_type::next_field< 4>;
        
        struct adaptation_field_section_type: public bitfield::section::base<adaptation_field_section_type, ts::adaptation_field, packet> {
            const uint8_t * base_addr() const;
            std::size_t length() const;
        };
        
        struct payload_section_type: public bitfield::section::base<payload_section_type, ts::payload, packet> {
            const uint8_t * base_addr() const;
            std::size_t length() const;
        };
        
        
        container_type container;
        
        sync_byte_type                     sync_byte;
        transport_error_indicator_type     transport_error_indicator;
        payload_unit_start_indicator_type  payload_unit_start_indicator;
        transport_priority_type            transport_priority;
        pid_type                           pid;
        transport_scrambling_control_type  transport_scrambling_control;
        adaptation_field_control_type      adaptation_field_control;
        continuity_counter_type            continuity_counter;
        
        adaptation_field_section_type  adaptation_field;
        payload_section_type           payload;
        
        
        packet() = default;
        packet(bitfield::container::initializer_list list);
        packet & operator =(bitfield::container::initializer_list list);
        
        packet(const ts::packet & packet);
        packet & operator =(const ts::packet & packet);
    };
    
    bool operator ==(const ts::packet & rop, const ts::packet & lop);
    bool operator !=(const ts::packet & rop, const ts::packet & lop);
    std::ostream & operator <<(std::ostream & os, const ts::packet & packet);
}}

#endif // __INCLUDED_TS_PROCESSOR_TS_PACKET_HPP__
