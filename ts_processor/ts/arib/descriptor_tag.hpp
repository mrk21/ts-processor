#ifndef __INCLUDED_TS_PROCESSOR_TS_ARIB_DESCRIPTOR_TAG_HPP__
#define __INCLUDED_TS_PROCESSOR_TS_ARIB_DESCRIPTOR_TAG_HPP__

#include <ts_processor/ts/descriptor_tag.hpp>

namespace ts_processor { namespace ts { namespace arib {
    // see: ARIB STD-B10 v5.3, 5.3, Table 5-3
    class descriptor_tag: public ts::descriptor_tag {
        friend class id_category_helper<descriptor_tag>;
        using helper = id_category_helper<descriptor_tag>;
        
    public:
        using base_type = ts::descriptor_tag::type;
        
        // hack: Divided the type because a size of the tuple of Boost.Preprocessor was up to 64.
        SYMBOLSET_DEFINE(type_1, base_type, (
            carousel_identifier          ,
            association_tag              ,
            deferred_association_tags    ,
            
            avc_video                    ,
            avc_timing_and_hrd           ,
            mpeg_4_audio_extension       ,
            
            network_name                 ,
            service_list                 ,
            stuffing                     ,
            satellite_delivery_system    ,
            terrestrial_delivery_system  ,
            bouquet_name                 ,
            service                      ,
            country_availability         ,
            linkage                      ,
            nvod_reference               ,
            time_shifted_service         ,
            short_event                  ,
            extended_event               ,
            time_shifted_event           ,
            component                    ,
            mosaic                       ,
            stream_identifier            ,
            ca_identifier                ,
            content                      ,
            parental_rating              ,
            local_time_offset            ,
            partial_transport_stream     ,
            data_broadcast_id            ,
            material_information         ,
            
            hierarchical_transmission    ,
            digital_copy_control         ,
            network_identification       ,
            partial_transport_stream_time,
            audio_component              ,
            hyperlink                    ,
            target_region                ,
            data_content                 ,
            video_decode_control         ,
            download_content             ,
            ca_emm_ts                    ,
            ca_contract_information      ,
            ca_service                   ,
            ts_information               ,
            extended_broadcaster         ,
            logo_transmission            ,
            basic_local_event            ,
            reference                    ,
            node_relation                ,
            short_node_information       ,
            stc_reference                ,
            series                       ,
            event_group                  ,
            si_parameter                 ,
            broadcaster_name             ,
            component_group              ,
            si_prime_ts                  ,
            board_information            ,
            ldt_linkage                  ,
            connected_transmission       ,
            content_availability         ,
            
            service_group                ,
            area_broadcasting_information
        ))
        
        SYMBOLSET_DEFINE(type, type_1, (
            access_control               ,
            carousel_compatible_composite,
            conditional_playback         ,
            
            terrestrial_delivery_system  ,
            partial_reception            ,
            emergency_information        ,
            data_component               ,
            system_management
        ))
        
        descriptor_tag() {
            this->assign({
                {{0x13}, type::carousel_identifier          }, // Carousel Identifier Descriptor
                {{0x14}, type::association_tag              }, // Association Tag Descriptor
                {{0x15}, type::deferred_association_tags    }, // Deferred Association tags Descriptor
                
                {{0x28}, type::avc_video                    }, // AVC Video Descriptor
                {{0x2A}, type::avc_timing_and_hrd           }, // AVC timing and HRD Descriptor
                {{0x2E}, type::mpeg_4_audio_extension       }, // MPEG-4 Audio Extension Descriptor
                
                {{0x40}, type::network_name                 }, // Network Name Descriptor
                {{0x41}, type::service_list                 }, // Service List Descriptor
                {{0x42}, type::stuffing                     }, // Stuffing Descriptor
                {{0x43}, type::satellite_delivery_system    }, // Satellite Delivery System Descriptor
                {{0x44}, type::terrestrial_delivery_system  }, // Terrestrial Delivery System Descriptor
                {{0x47}, type::bouquet_name                 }, // Bouquet Name Descriptor
                {{0x48}, type::service                      }, // Service Descriptor
                {{0x49}, type::country_availability         }, // Country Availability Descriptor
                {{0x4A}, type::linkage                      }, // Linkage Descriptor
                {{0x4B}, type::nvod_reference               }, // NVOD Reference Descriptor
                {{0x4C}, type::time_shifted_service         }, // Time Shifted Service Descriptor
                {{0x4D}, type::short_event                  }, // Short Event Descriptor
                {{0x4E}, type::extended_event               }, // Extended Event Descriptor
                {{0x4F}, type::time_shifted_event           }, // Time Shifted Event Descriptor
                {{0x50}, type::component                    }, // Component Descriptor
                {{0x51}, type::mosaic                       }, // Mosaic Descriptor
                {{0x52}, type::stream_identifier            }, // Stream Identifier Descriptor
                {{0x53}, type::ca_identifier                }, // CA Identifier Descriptor
                {{0x54}, type::content                      }, // Content Descriptor
                {{0x55}, type::parental_rating              }, // Parental Rating Descriptor
                {{0x58}, type::local_time_offset            }, // Local Time Offset Descriptor
                {{0x63}, type::partial_transport_stream     }, // Partial Transport Stream Descriptor
                {{0x66}, type::data_broadcast_id            }, // Data Broadcast Id Descriptor
                {{0x67}, type::material_information         }, // Material Information Descriptor
                
                {{0xC0}, type::hierarchical_transmission    }, // Hierarchical Transmission Descriptor
                {{0xC1}, type::digital_copy_control         }, // Digital Copy Control Descriptor
                {{0xC2}, type::network_identification       }, // Network Identification Descriptor
                {{0xC3}, type::partial_transport_stream_time}, // Partial Transport Stream Time Descriptor
                {{0xC4}, type::audio_component              }, // Audio Component Descriptor
                {{0xC5}, type::hyperlink                    }, // Hyperlink Descriptor
                {{0xC6}, type::target_region                }, // Target Region Descriptor
                {{0xC7}, type::data_content                 }, // Data Content Descriptor
                {{0xC8}, type::video_decode_control         }, // Video Decode Control Descriptor
                {{0xC9}, type::download_content             }, // Download Content Descriptor
                {{0xCA}, type::ca_emm_ts                    }, // CA EMM TS Descriptor
                {{0xCB}, type::ca_contract_information      }, // CA Contract Information Descriptor
                {{0xCC}, type::ca_service                   }, // CA Service Descriptor
                {{0xCD}, type::ts_information               }, // TS Information Descriptor
                {{0xCE}, type::extended_broadcaster         }, // Extended Broadcaster Descriptor
                {{0xCF}, type::logo_transmission            }, // Logo Transmission Descriptor
                {{0xD0}, type::basic_local_event            }, // Basic Local Event Descriptor
                {{0xD1}, type::reference                    }, // Reference Descriptor
                {{0xD2}, type::node_relation                }, // Node Relation Descriptor
                {{0xD3}, type::short_node_information       }, // Short Node Information Descriptor
                {{0xD4}, type::stc_reference                }, // STC Reference Descriptor
                {{0xD5}, type::series                       }, // Series Descriptor
                {{0xD6}, type::event_group                  }, // Event Group Descriptor
                {{0xD7}, type::si_parameter                 }, // SI Parameter Descriptor
                {{0xD8}, type::broadcaster_name             }, // Broadcaster Name Descriptor
                {{0xD9}, type::component_group              }, // Component Group Descriptor
                {{0xDA}, type::si_prime_ts                  }, // SI Prime TS Descriptor
                {{0xDB}, type::board_information            }, // Board Information Descriptor
                {{0xDC}, type::ldt_linkage                  }, // LDT linkage Descriptor
                {{0xDD}, type::connected_transmission       }, // Connected Transmission Descriptor
                {{0xDE}, type::content_availability         }, // Content Availability Descriptor
                
                {{0xE0}, type::service_group                }, // Service Group Descriptor
                {{0xE1}, type::area_broadcasting_information}, // Area Broadcasting Information Descriptor
                
                {{0xF6}, type::access_control               }, // Access Control Descriptor
                {{0xF7}, type::carousel_compatible_composite}, // Carousel Compatible Composite Descriptor
                {{0xF8}, type::conditional_playback         }, // Conditional Playback Descriptor
                
                {{0xFA}, type::terrestrial_delivery_system  }, // Terrestrial Delivery System Descriptor
                {{0xFB}, type::partial_reception            }, // Partial Reception Descriptor
                {{0xFC}, type::emergency_information        }, // Emergency Information Descriptor
                {{0xFD}, type::data_component               }, // Data Component Descriptor
                {{0xFE}, type::system_management            }, // System Management Descriptor
            });
        }
        
        static type type_of(uint32_t id) {
            return helper::type_of(id);
        }
    };
}}}

#endif // __INCLUDED_TS_PROCESSOR_TS_ARIB_DESCRIPTOR_TAG_HPP__
