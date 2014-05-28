#ifndef __INCLUDED_TS_PROCESSOR_TS_DESCRIPTOR_TAG_HPP__
#define __INCLUDED_TS_PROCESSOR_TS_DESCRIPTOR_TAG_HPP__

#include <symbolset/symbolset.hpp>
#include <vector>
#include <string>
#include <unordered_map>

namespace ts_processor { namespace ts {
    // see: ISO/IEC 13818-1, 2.6.1, Table 2-39
    class descriptor_tag {
        using self = descriptor_tag;
        
    public:
        SYMBOLSET_DEFINE(type, (
            reserved                    ,
            defined                     ,
            user_private                ,
            
            video_stream                ,
            audio_stream                ,
            hierarchy                   ,
            registration                ,
            data_stream_alignment       ,
            target_background_grid      ,
            video_window                ,
            ca                          ,
            iso_639_language            ,
            system_clock                ,
            multiplex_buffer_utilization,
            copyright                   ,
            maximum_bitrate             ,
            private_data_indicator      ,
            smoothing_buffer            ,
            std                         ,
            ibp                         ,
            mpeg_4_video                ,
            mpeg_4_audio                ,
            iod                         ,
            sl                          ,
            fmc                         ,
            external_es_id              ,
            muxcode                     ,
            fmxbuffersize               ,
            multiplexbuffer
        ))
        
    private:
        struct database_schema {
            std::vector<uint8_t> id;
            struct {
                descriptor_tag::type type;
                std::string description;
            } info;
        };
        
        static const std::vector<database_schema> & database() {
            static std::vector<database_schema> const database{
                {{0x00     }, {type::reserved                    , "Reserved"                                     }},
                {{0x01     }, {type::reserved                    , "Reserved"                                     }},
                {{0x02     }, {type::video_stream                , "video_stream_descriptor"                      }},
                {{0x03     }, {type::audio_stream                , "audio_stream_descriptor"                      }},
                {{0x04     }, {type::hierarchy                   , "hierarchy_descriptor"                         }},
                {{0x05     }, {type::registration                , "registration_descriptor"                      }},
                {{0x06     }, {type::data_stream_alignment       , "data_stream_alignment_descriptor"             }},
                {{0x07     }, {type::target_background_grid      , "target_background_grid_descriptor"            }},
                {{0x08     }, {type::video_window                , "Video_window_descriptor"                      }},
                {{0x09     }, {type::ca                          , "CA_descriptor"                                }},
                {{0x0A     }, {type::iso_639_language            , "ISO_639_language_descriptor"                  }},
                {{0x0B     }, {type::system_clock                , "System_clock_descriptor"                      }},
                {{0x0C     }, {type::multiplex_buffer_utilization, "Multiplex_buffer_utilization_descriptor"      }},
                {{0x0D     }, {type::copyright                   , "Copyright_descriptor"                         }},
                {{0x0E     }, {type::maximum_bitrate             , "Maximum_bitrate_descriptor"                   }},
                {{0x0F     }, {type::private_data_indicator      , "Private_data_indicator_descriptor"            }},
                {{0x10     }, {type::smoothing_buffer            , "Smoothing_buffer_descriptor"                  }},
                {{0x11     }, {type::std                         , "STD_descriptor"                               }},
                {{0x12     }, {type::ibp                         , "IBP_descriptor"                               }},
                {{0x13,0x1A}, {type::defined                     , "Defined in ISO/IEC 13818-6"                   }},
                {{0x1B     }, {type::mpeg_4_video                , "MPEG-4_video_descriptor"                      }},
                {{0x1C     }, {type::mpeg_4_audio                , "MPEG-4_audio_descriptor"                      }},
                {{0x1D     }, {type::iod                         , "IOD_descriptor"                               }},
                {{0x1E     }, {type::sl                          , "SL_descriptor"                                }},
                {{0x1F     }, {type::fmc                         , "FMC_descriptor"                               }},
                {{0x20     }, {type::external_es_id              , "External_ES_ID_descriptor"                    }},
                {{0x21     }, {type::muxcode                     , "MuxCode_descriptor"                           }},
                {{0x22     }, {type::fmxbuffersize               , "FmxBufferSize_descriptor"                     }},
                {{0x23     }, {type::multiplexbuffer             , "MultiplexBuffer_descriptor"                   }},
                {{0x24,0x3F}, {type::reserved                    , "ITU-T Rec. H.222.0 | ISO/IEC 13818-1 Reserved"}},
                {{0x40,0xFF}, {type::user_private                , "User Private"                                 }},
            };
            return database;
        }
        
        static std::unordered_map<uint8_t, type> types;
        
    public:
        static bool initialize();
        static type type_of(uint32_t id);
    };
}}

#endif // __INCLUDED_TS_PROCESSOR_TS_DESCRIPTOR_TAG_HPP__
