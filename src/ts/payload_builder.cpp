#include <ts_processor/ts/payload_builder.hpp>
#include <iterator>
#include <algorithm>

namespace ts_processor { namespace ts {
    void payload_builder::push(const ts::packet & packet) {
        std::copy(
            packet.payload.begin(),
            packet.payload.end(),
            std::back_insert_iterator<decltype(this->container)>(this->container)
        );
    }
    
    const ts::payload * payload_builder::payload() const {
        return this->container.empty() ?
            nullptr : (const ts::payload *)&this->container[0];
    }
    
    void payload_builder::clear() {
        this->container.clear();
    }
}}
