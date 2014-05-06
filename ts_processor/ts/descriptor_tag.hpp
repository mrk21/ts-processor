#ifndef __INCLUDED_TS_PROCESSOR_TS_DESCRIPTOR_TAG_HPP__
#define __INCLUDED_TS_PROCESSOR_TS_DESCRIPTOR_TAG_HPP__

#include <ts_processor/symbolset.hpp>
#include <vector>
#include <string>
#include <unordered_map>

namespace ts_processor { namespace ts {
    // see: ISO/IEC 13818-1, 2.6.1, Table 2-39
    class descriptor_tag {
        using self = descriptor_tag;
        
    public:
        TS_PROCESSOR_SYMBOLSET(type,
            invalid                     ,
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
            multiplexbuffer             ,
        )
        
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
                {{0     }, {type::reserved                    , "Reserved"                                     }},
                {{1     }, {type::reserved                    , "Reserved"                                     }},
                {{2     }, {type::video_stream                , "video_stream_descriptor"                      }},
                {{3     }, {type::audio_stream                , "audio_stream_descriptor"                      }},
                {{4     }, {type::hierarchy                   , "hierarchy_descriptor"                         }},
                {{5     }, {type::registration                , "registration_descriptor"                      }},
                {{6     }, {type::data_stream_alignment       , "data_stream_alignment_descriptor"             }},
                {{7     }, {type::target_background_grid      , "target_background_grid_descriptor"            }},
                {{8     }, {type::video_window                , "Video_window_descriptor"                      }},
                {{9     }, {type::ca                          , "CA_descriptor"                                }},
                {{10    }, {type::iso_639_language            , "ISO_639_language_descriptor"                  }},
                {{11    }, {type::system_clock                , "System_clock_descriptor"                      }},
                {{12    }, {type::multiplex_buffer_utilization, "Multiplex_buffer_utilization_descriptor"      }},
                {{13    }, {type::copyright                   , "Copyright_descriptor"                         }},
                {{14    }, {type::maximum_bitrate             , "Maximum_bitrate_descriptor"                   }},
                {{15    }, {type::private_data_indicator      , "Private_data_indicator_descriptor"            }},
                {{16    }, {type::smoothing_buffer            , "Smoothing_buffer_descriptor"                  }},
                {{17    }, {type::std                         , "STD_descriptor"                               }},
                {{18    }, {type::ibp                         , "IBP_descriptor"                               }},
                {{19,26 }, {type::defined                     , "Defined in ISO/IEC 13818-6"                   }},
                {{27    }, {type::mpeg_4_video                , "MPEG-4_video_descriptor"                      }},
                {{28    }, {type::mpeg_4_audio                , "MPEG-4_audio_descriptor"                      }},
                {{29    }, {type::iod                         , "IOD_descriptor"                               }},
                {{30    }, {type::sl                          , "SL_descriptor"                                }},
                {{31    }, {type::fmc                         , "FMC_descriptor"                               }},
                {{32    }, {type::external_es_id              , "External_ES_ID_descriptor"                    }},
                {{33    }, {type::muxcode                     , "MuxCode_descriptor"                           }},
                {{34    }, {type::fmxbuffersize               , "FmxBufferSize_descriptor"                     }},
                {{35    }, {type::multiplexbuffer             , "MultiplexBuffer_descriptor"                   }},
                {{36,63 }, {type::reserved                    , "ITU-T Rec. H.222.0 | ISO/IEC 13818-1 Reserved"}},
                {{64,255}, {type::user_private                , "User Private"                                 }},
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
