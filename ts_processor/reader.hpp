#ifndef __INCLUDED_TS_PROCESSOR_READER_HPP__
#define __INCLUDED_TS_PROCESSOR_READER_HPP__

#include <ts_processor/ts/packet.hpp>
#include <iostream>
#include <functional>

namespace ts_processor {
    class reader {
        std::istream & is;
        
    public:
        reader(std::istream & is) : is{is} {}
        
        bool read(ts::packet & packet);
        void each(std::function<bool(ts::packet &)> callback);
    };
}

#endif // __INCLUDED_TS_PROCESSOR_READER_HPP__
