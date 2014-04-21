#ifndef __INCLUDED_TS_PROCESSOR_TS_STREAM_TYPE_HPP__
#define __INCLUDED_TS_PROCESSOR_TS_STREAM_TYPE_HPP__

#include <ts_processor/symbolset.hpp>
#include <vector>
#include <string>
#include <unordered_map>

namespace ts_processor { namespace ts {
    // see: ISO/IEC 13818-1, 2.4.4.10, Table 2-29
    class stream_type {
        using self = stream_type;
        
    public:
        TS_PROCESSOR_SYMBOLSET(type,
            reserved,
            video,
            audio,
            user,
            other,
            invalid,
        )
        
    private:
        struct database_schema {
            std::vector<uint8_t> id;
            struct {
                stream_type::type type;
                std::string description;
            } info;
        };
        
        static const std::vector<database_schema> & database() {
            static std::vector<database_schema> const database{
                {{0x00}     , {type::reserved, "ITU-T | ISO/IEC Reserved"                                                                      }},
                {{0x01}     , {type::video   , "ISO/IEC 11172 Video"                                                                           }},
                {{0x02}     , {type::video   , "ITU-T Rec. H.262 | ISO/IEC 13818-2 Video or ISO/IEC 11172-2 constrained parameter video stream"}},
                {{0x03}     , {type::audio   , "ISO/IEC 11172 Audio"                                                                           }},
                {{0x04}     , {type::audio   , "ISO/IEC 13818-3 Audio"                                                                         }},
                {{0x05}     , {type::other   , "ITU-T Rec. H.222.0 | ISO/IEC 13818-1 private_sections"                                         }},
                {{0x06}     , {type::other   , "ITU-T Rec. H.222.0 | ISO/IEC 13818-1 PES packets containing private data"                      }},
                {{0x07}     , {type::other   , "ISO/IEC 13522 MHEG"                                                                            }},
                {{0x08}     , {type::other   , "ITU-T Rec. H.222.0 | ISO/IEC 13818-1 Annex A DSM-CC"                                           }},
                {{0x09}     , {type::other   , "ITU-T Rec. H.222.1"                                                                            }},
                {{0x0A}     , {type::other   , "ISO/IEC 13818-6 type A"                                                                        }},
                {{0x0B}     , {type::other   , "ISO/IEC 13818-6 type B"                                                                        }},
                {{0x0C}     , {type::other   , "ISO/IEC 13818-6 type C"                                                                        }},
                {{0x0D}     , {type::other   , "ISO/IEC 13818-6 type D"                                                                        }},
                {{0x0E}     , {type::other   , "ITU-T Rec. H.222.0 | ISO/IEC 13818-1 auxiliary"                                                }},
                {{0x0F}     , {type::audio   , "ISO/IEC 13818-7 Audio with ADTS transport syntax"                                              }},
                {{0x10}     , {type::video   , "ISO/IEC 14496-2 Visual"                                                                        }},
                {{0x11}     , {type::audio   , "ISO/IEC 14496-3 Audio with the LATM transport syntax as defined in ISO/IEC 14496-3 / AMD 1"    }},
                {{0x12}     , {type::other   , "ISO/IEC 14496-1 SL-packetized stream or FlexMux stream carried in PES packets"                 }},
                {{0x13}     , {type::other   , "ISO/IEC 14496-1 SL-packetized stream or FlexMux stream carried in ISO/IEC14496_sections."      }},
                {{0x14}     , {type::other   , "ISO/IEC 13818-6 Synchronized Download Protocol"                                                }},
                {{0x15,0x7F}, {type::reserved, "ITU-T Rec. H.222.0 | ISO/IEC 13818-1 Reserved"                                                 }},
                {{0x80,0xFF}, {type::user    , "User Private"                                                                                  }},
            };
            return database;
        }
        
        static std::unordered_map<uint8_t, type> types;
        
    public:
        static bool initialize();
        static type type_of(uint32_t id);
    };
}}

#endif // __INCLUDED_TS_PROCESSOR_TS_STREAM_TYPE_HPP__
