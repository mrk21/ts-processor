#ifndef __INCLUDED_TS_PROCESSOR_TS_ARIB_PID_HPP__
#define __INCLUDED_TS_PROCESSOR_TS_ARIB_PID_HPP__

#include <ts_processor/ts/pid.hpp>

namespace ts_processor { namespace ts { namespace arib {
    // see: ISO/IEC 13818-1, 2.4.3.3, Table 2-3
    class pid: public ts::pid {
        friend class id_category_helper<pid>;
        using helper = id_category_helper<pid>;
        
    public:
        using base_type = ts::pid::type;
        
        SYMBOLSET_DEFINE(type, base_type, (
            nit ,
            sdt ,
            bat ,
            eit ,
            rst ,
            tdt ,
            tot ,
            pcat,
            bit ,
            nbit,
            ldt ,
            amt ,
            st  ,
            int_
        ))
        
        struct id: public ts::pid::id {
            static constexpr uint16_t nit  = 0x0010;
            static constexpr uint16_t sdt  = 0x0011;
            static constexpr uint16_t bat  = 0x0011;
            static constexpr uint16_t eit  = 0x0012;
            static constexpr uint16_t rst  = 0x0013;
            static constexpr uint16_t tdt  = 0x0014;
            static constexpr uint16_t tot  = 0x0014;
            static constexpr uint16_t pcat = 0x0022;
            static constexpr uint16_t bit  = 0x0024;
            static constexpr uint16_t nbit = 0x0025;
            static constexpr uint16_t ldt  = 0x0025;
            static constexpr uint16_t amt  = 0x002E;
        };
        
        // Exclude duplicate PIDs and INT(TOT, LDT and INT).
        pid() {
            this->assign({
                {{id::nit }, type::nit },
                {{id::sdt }, type::sdt },
                {{id::bat }, type::bat },
                {{id::eit }, type::eit },
                {{0x0026  }, type::eit },
                {{0x0027  }, type::eit },
                {{id::rst }, type::rst },
                {{id::tdt }, type::tdt },
                {{id::pcat}, type::pcat},
                {{id::bit }, type::bit },
                {{id::nbit}, type::nbit},
                {{id::amt }, type::amt },
           });
        }
        
        static type type_of(uint32_t id) {
            return helper::type_of(id);
        }
    };
}}}

#endif // __INCLUDED_TS_PROCESSOR_TS_ARIB_PID_HPP__
