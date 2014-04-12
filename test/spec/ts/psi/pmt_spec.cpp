#include <bandit_with_gmock/bandit_with_gmock.hpp>
#include <ts_processor/ts/packet.hpp>
#include <ts_processor/ts/psi/pmt.hpp>
#include <bitfield/iostream.hpp>

namespace ts_processor { namespace ts { namespace psi {
go_bandit([]{
    using namespace bandit;
    
    describe("ts::psi::pmt", [&]{
        ts::packet packet;
        
        before_each([&]{
            packet = {
                #include <fixture/ts/psi/pmt/single_packet.cpp>
            };
        });
        
        describe("#sections", [&]{
            it("should iterate each fieldset in the section list", [&]{
                auto & sections = packet.payload->pmt.sections;
                auto it = sections.begin();
                auto end = sections.end();
                
                AssertThat(it, not Equals(end));
                AssertThat(it->elementary_pid, Equals(0x0111));
                
                ++it;
                AssertThat(it, not Equals(end));
                AssertThat(it->elementary_pid, Equals(0x0112));
                
                ++it;
                AssertThat(it, not Equals(end));
                AssertThat(it->elementary_pid, Equals(0x0114));
                
                ++it;
                AssertThat(it, not Equals(end));
                AssertThat(it->elementary_pid, Equals(0x0810));
                
                ++it;
                AssertThat(it, not Equals(end));
                AssertThat(it->elementary_pid, Equals(0x0811));
                
                ++it;
                AssertThat(it, not Equals(end));
                AssertThat(it->elementary_pid, Equals(0x0812));
                
                ++it;
                AssertThat(it, not Equals(end));
                AssertThat(it->elementary_pid, Equals(0x0813));
                
                ++it;
                AssertThat(it, not Equals(end));
                AssertThat(it->elementary_pid, Equals(0x0816));
                
                ++it;
                AssertThat(it, not Equals(end));
                AssertThat(it->elementary_pid, Equals(0x081A));
                
                ++it;
                AssertThat(it, not Equals(end));
                AssertThat(it->elementary_pid, Equals(0x081B));
                
                ++it;
                AssertThat(it, not Equals(end));
                AssertThat(it->elementary_pid, Equals(0x081F));
                
                ++it;
                AssertThat(it, Equals(end));
            });
        });
    });
});
}}}
