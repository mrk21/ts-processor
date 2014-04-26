#include <bandit_with_gmock/bandit_with_gmock.hpp>
#include <ts_processor/writer.hpp>
#include <sstream>

namespace ts_processor {
go_bandit([]{
    using namespace bandit;
    
    describe("writer", [&]{
        ts::packet const PAT_PACKET_{
            #include <fixture/ts/psi/pat/single_packet.cpp>
        };
        ts::packet const INVALID_PACKET_{
            #include <fixture/ts/packet/invalid_sync_byte.cpp>
        };
        
        std::ostringstream * oss;
        ts_processor::writer * writer;
        
        before_each([&]{
            oss = new std::ostringstream;
            writer = new ts_processor::writer(*oss);
        });
        
        describe("#write(ts::packet & packet)", [&]{
            it("should write the packet", [&]{
                std::string packet_data;
                for (auto v: PAT_PACKET_.container) packet_data.push_back(char(v));
                
                AssertThat(writer->write(PAT_PACKET_), Equals(true));
                AssertThat(oss->str(), Equals(packet_data));
            });
            
            describe("when the packet was invalid sync byte", [&]{
                it("should return false, on top of that, not write the packet", [&]{
                    AssertThat(writer->write(INVALID_PACKET_), Equals(false));
                    AssertThat(oss->str(), Equals(""));
                });
            });
        });
    });
});
}
