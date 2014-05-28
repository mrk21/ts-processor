#ifndef __INCLUDED_TS_PROCESSOR_TS_PID_HPP__
#define __INCLUDED_TS_PROCESSOR_TS_PID_HPP__

#include <symbolset/symbolset.hpp>
#include <vector>
#include <string>
#include <unordered_map>

namespace ts_processor { namespace ts {
    // see: ISO/IEC 13818-1, 2.4.3.3, Table 2-3
    class pid {
        using self = pid;
        
    public:
        SYMBOLSET_DEFINE(type, (
            reserved,
            pat,
            cat,
            tsdt,
            mapped,
            null
        ))
        
        enum id: uint16_t {
            pat  = 0x0000,
            cat  = 0x0001,
            tsdt = 0x0002,
            null = 0x1FFF,
        };
        
   private:
        struct database_schema {
            std::vector<uint16_t> id;
            struct {
                pid::type type;
                std::string description;
            } info;
        };
        
        static const std::vector<database_schema> & database() {
            static std::vector<database_schema> const database{
                {{id::pat}      , {type::pat     , "Program Association Table"                                                             }},
                {{id::cat}      , {type::cat     , "Conditional Access Table"                                                              }},
                {{id::tsdt}     , {type::tsdt    , "Transport Stream Description Table"                                                    }},
                {{0x0003,0x000F}, {type::reserved, "Reserved"                                                                              }},
                {{0x0010,0x1FFE}, {type::mapped  , "May be assigned as network_PID, Program_map_PID, elementary_PID, or for other purposes"}},
                {{id::null}     , {type::null    , "Null packet"                                                                           }},
            };
            return database;
        }
        
        static std::unordered_map<uint16_t, type> types;
        
    public:
        static bool initialize();
        static type type_of(uint32_t id);
    };
}}

#endif // __INCLUDED_TS_PROCESSOR_TS_PID_HPP__
