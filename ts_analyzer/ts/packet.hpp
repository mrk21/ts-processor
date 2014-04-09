#ifndef __INCLUDED_TS_ANALYZER_TS_PACKET_HPP__
#define __INCLUDED_TS_ANALYZER_TS_PACKET_HPP__

#include <ts_analyzer/ts/adaptation_field.hpp>
#include <ts_analyzer/ts/payload.hpp>
#include <bitfield/bitfield.hpp>
#include <array>

namespace ts_analyzer { namespace ts {
    // see: ISO/IEC 13818-1, 2.4.3.2, Table 2-2
    union packet {
        static constexpr std::size_t SIZE = 188;
        using container_type = std::array<uint8_t, SIZE>;
        
        using sync_byte_type                    =                               bitfield::bitfield< 8>;
        using transport_error_indicator_type    =                    sync_byte_type::next_bitfield< 1>;
        using payload_unit_start_indicator_type =    transport_error_indicator_type::next_bitfield< 1>;
        using transport_priority_type           = payload_unit_start_indicator_type::next_bitfield< 1>;
        using pid_type                          =           transport_priority_type::next_bitfield<13>;
        using transport_scrambling_control_type =                          pid_type::next_bitfield< 2>;
        using adaptation_field_control_type     = transport_scrambling_control_type::next_bitfield< 2>;
        using continuity_counter_type           =     adaptation_field_control_type::next_bitfield< 4>;
        
        container_type container;
        
        sync_byte_type                     sync_byte;
        transport_error_indicator_type     transport_error_indicator;
        payload_unit_start_indicator_type  payload_unit_start_indicator;
        transport_priority_type            transport_priority;
        pid_type                           pid;
        transport_scrambling_control_type  transport_scrambling_control;
        adaptation_field_control_type      adaptation_field_control;
        continuity_counter_type            continuity_counter;
        
        ts::adaptation_field * adaptation_field();
        ts::payload * payload();
    };
}}

#endif // __INCLUDED_TS_ANALYZER_TS_PACKET_HPP__