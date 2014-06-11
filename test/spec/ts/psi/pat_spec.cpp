#include <bandit_with_gmock/bandit_with_gmock.hpp>
#include <ts_processor/ts/data.hpp>
#include <ts_processor/ts/psi/pat.hpp>
#include <bitfield/iostream.hpp>

namespace ts_processor { namespace ts { namespace psi {
go_bandit([]{
    using namespace bandit;
    
    describe("ts::psi::pat", [&]{
        ts::data data;
        
        auto equals_v = [](pat::pid_type v){
            return Equals(v);
        };
        
        before_each([&]{
            ts::packet packet{
                #include <fixture/ts/psi/pat/single_packet.cpp>
            };
            data.reset(packet.pid);
            data.push(packet);
        });
        
        describe("#sections", [&]{
            it("should iterate each fieldset in the section list", [&]{
                auto & sections = data->psi.get<pat>()->sections;
                auto it = sections.begin();
                auto end = sections.end();
                
                AssertThat(it, not Equals(end));
                AssertThat(it->type(), equals_v(pat::pid_type::network));
                AssertThat(it->pid, Equals(0x0010));
                
                ++it;
                AssertThat(it, not Equals(end));
                AssertThat(it->type(), equals_v(pat::pid_type::program_map));
                AssertThat(it->pid, Equals(0x0101));
                
                ++it;
                AssertThat(it, not Equals(end));
                AssertThat(it->type(), equals_v(pat::pid_type::program_map));
                AssertThat(it->pid, Equals(0x0102));
                
                ++it;
                AssertThat(it, not Equals(end));
                AssertThat(it->type(), equals_v(pat::pid_type::program_map));
                AssertThat(it->pid, Equals(0x1FC8));
                
                ++it;
                AssertThat(it, not Equals(end));
                AssertThat(it->type(), equals_v(pat::pid_type::program_map));
                AssertThat(it->pid, Equals(0x1FC9));
                
                ++it;
                AssertThat(it, Equals(end));
            });
        });
    });
});
}}}
