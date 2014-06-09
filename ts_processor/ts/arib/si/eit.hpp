#ifndef __INCLUDED_TS_PROCESSOR_TS_ARIB_PS_EIT_HPP__
#define __INCLUDED_TS_PROCESSOR_TS_ARIB_PS_EIT_HPP__

#include <ts_processor/ts/psi/base.hpp>
#include <ts_processor/ts/descriptor/base.hpp>
#include <bitfield/section/list.hpp>

namespace ts_processor { namespace ts { namespace arib { namespace si {
    // see: ARIB STD-B10 v5.3, 5.2.7, Table 5-7
    struct eit: public psi::base {
        using base_class = psi::base;
        
        using service_id_type                  =                              bitfield::field<16>;
        using reserved2_type                   =                  service_id_type::next_field< 2>;
        using version_number_type              =                   reserved2_type::next_field< 5>;
        using current_next_indicator_type      =              version_number_type::next_field< 1>;
        using section_number_type              =      current_next_indicator_type::next_field< 8>;
        using last_section_number_type         =              section_number_type::next_field< 8>;
        using transport_stream_id_type         =         last_section_number_type::next_field<16>;
        using original_network_id_type         =         transport_stream_id_type::next_field<16>;
        using segment_last_section_number_type =         original_network_id_type::next_field< 8>;
        using last_table_id_type               = segment_last_section_number_type::next_field< 8>;
        
        union event_type {
            using event_id_type                =                 bitfield::field<16>;
            using start_time_type              =       event_id_type::next_field<40>;
            using duration_type                =     start_time_type::next_field<24>;
            using running_status_type          =       duration_type::next_field< 3>;
            using free_ca_mode_type            = running_status_type::next_field< 1>;
            using descriptors_loop_length_type =   free_ca_mode_type::next_field<12>;
            
            struct descroptor_list_type: public bitfield::section::list<descroptor_list_type, descriptor::base, event_type> {
                const uint8_t * base_addr() const;
                std::size_t length() const;
            };
            
            event_id_type                event_id;
            start_time_type              start_time;
            duration_type                duration;
            running_status_type          running_status;
            free_ca_mode_type            free_ca_mode;
            descriptors_loop_length_type descriptors_loop_length;
            
            descroptor_list_type descriptors;
            
            std::size_t length() const;
        };
        
        struct event_list_type: public bitfield::section::list<event_list_type, event_type, eit> {
            const uint8_t * base_addr() const;
            std::size_t length() const;
        };
        
        union {
            service_id_type                  service_id;
            reserved2_type                   reserved2;
            version_number_type              version_number;
            current_next_indicator_type      current_next_indicator;
            section_number_type              section_number;
            last_section_number_type         last_section_number;
            transport_stream_id_type         transport_stream_id;
            original_network_id_type         original_network_id;
            segment_last_section_number_type segment_last_section_number;
            last_table_id_type               last_table_id;
            
            event_list_type events;
        };
    };
}}}}

#endif // __INCLUDED_TS_PROCESSOR_TS_ARIB_PS_EIT_HPP__
