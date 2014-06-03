#ifndef __INCLUDED_TS_PROCESSOR_TS_PID_HPP__
#define __INCLUDED_TS_PROCESSOR_TS_PID_HPP__

#include <ts_processor/id_category.hpp>

namespace ts_processor { namespace ts {
    // see: ISO/IEC 13818-1, 2.4.3.3, Table 2-3
    class pid: public id_category<pid> {
        friend class id_category_helper<pid>;
        using helper = id_category_helper<pid>;
        
    public:
        using base_type = id_category::type;
        
        SYMBOLSET_DEFINE(type, base_type, (
            pat,
            cat,
            tsdt,
            mapped,
            null
        ))
        
        struct id {
            static constexpr uint16_t pat  = 0x0000;
            static constexpr uint16_t cat  = 0x0001;
            static constexpr uint16_t tsdt = 0x0002;
            static constexpr uint16_t null = 0x1FFF;
        };
        
        pid() {
            this->assign({
                {{id::pat}      , type::pat     }, // Program Association Table
                {{id::cat}      , type::cat     }, // Conditional Access Table
                {{id::tsdt}     , type::tsdt    }, // Transport Stream Description Table
                {{0x0003,0x000F}, type::reserved}, // Reserved
                {{0x0010,0x1FFE}, type::mapped  }, // May be assigned as network_PID, Program_map_PID, elementary_PID, or for other purposes
                {{id::null}     , type::null    }, // Null packet
            });
        }
        
        static type type_of(uint32_t id) {
            return helper::type_of(id);
        }
    };
}}

#endif // __INCLUDED_TS_PROCESSOR_TS_PID_HPP__
