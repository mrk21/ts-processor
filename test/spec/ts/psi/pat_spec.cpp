#include <bandit_with_gmock/bandit_with_gmock.hpp>
#include <ts_processor/ts/packet.hpp>
#include <ts_processor/ts/psi/pat.hpp>
#include <bitfield/iostream.hpp>

namespace ts_processor { namespace ts { namespace psi {
go_bandit([]{
    using namespace bandit;
    
    describe("ts::psi::pat", [&]{
        ts::packet * packet;
        
        before_each([&]{
            packet = new ts::packet{{{
                #include <fixture/ts/psi/pat/single_packet.cpp>
            }}};
        });
        
        describe("#sections", [&]{
            it("should iterated the sections", [&]{
                auto & sections = packet->payload->pat.sections;
                auto it = sections.begin();
                auto end = sections.end();
                
                AssertThat(it != end, Equals(true));
                AssertThat(it->pid, Equals(0x0010));
                
                ++it;
                AssertThat(it != end, Equals(true));
                AssertThat(it->pid, Equals(0x0101));
                
                ++it;
                AssertThat(it != end, Equals(true));
                AssertThat(it->pid, Equals(0x0102));
                
                ++it;
                AssertThat(it != end, Equals(true));
                AssertThat(it->pid, Equals(0x1FC8));
                
                ++it;
                AssertThat(it != end, Equals(true));
                AssertThat(it->pid, Equals(0x1FC9));
                
                ++it;
                AssertThat(it != end, Equals(false));
            });
        });
    });
});
}}}
