#ifndef __INCLUDED_TS_PROCESSOR_WRITER_HPP__
#define __INCLUDED_TS_PROCESSOR_WRITER_HPP__

#include <ts_processor/ts/packet.hpp>
#include <iostream>

namespace ts_processor {
    class writer {
        std::ostream & os;
        
    public:
        writer(std::ostream & os) : os{os} {}
        
        bool write(const ts::packet & packet);
    };
}

#endif // __INCLUDED_TS_PROCESSOR_WRITER_HPP__
