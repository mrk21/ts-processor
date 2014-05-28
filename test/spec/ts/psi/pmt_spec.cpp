#include <bandit_with_gmock/bandit_with_gmock.hpp>
#include <ts_processor/ts/data.hpp>
#include <ts_processor/ts/psi/pmt.hpp>
#include <bitfield/iostream.hpp>

namespace ts_processor { namespace ts { namespace psi {
go_bandit([]{
    using namespace bandit;
    
    describe("ts::psi::pmt", [&]{
        ts::data data;
        
        auto equals_v = [](descriptor_tag::type v){
            return Equals(v);
        };
        
        before_each([&]{
            ts::packet packet{
                #include <fixture/ts/psi/pmt/single_packet.cpp>
            };
            data.reset(packet.pid);
            data.push(packet);
        });
        
        describe("#program_info", [&]{
            it("should iterate each descriptor in this list", [&]{
                auto & program_info = data->pmt.program_info;
                auto it = program_info.begin();
                auto end = program_info.end();
                
                AssertThat(it, not Equals(end));
                AssertThat(it->type(), equals_v(descriptor_tag::type::ca));
                
                ++it;
                AssertThat(it, not Equals(end));
                AssertThat(it->type(), equals_v(descriptor_tag::type::reserved));
                
                ++it;
                AssertThat(it, not Equals(end));
                AssertThat(it->type(), equals_v(descriptor_tag::type::user_private));
                
                ++it;
                AssertThat(it, Equals(end));
             });
        });
        
        describe("#sections", [&]{
            it("should iterate each fieldset in the section list", [&]{
                auto & sections = data->pmt.sections;
                auto it = sections.begin();
                auto end = sections.end();
                
                AssertThat(it, not Equals(end));
                AssertThat(it->elementary_pid, Equals(0x0111));
                {
                    auto jt = it->es_info.begin();
                    auto jend = it->es_info.end();
                    
                    AssertThat(jt, not Equals(jend));
                    AssertThat(jt->type(), equals_v(descriptor_tag::type::user_private));
                    
                    ++jt;
                    AssertThat(jt, Equals(jend));
                }
                
                ++it;
                AssertThat(it, not Equals(end));
                AssertThat(it->elementary_pid, Equals(0x0112));
                {
                    auto jt = it->es_info.begin();
                    auto jend = it->es_info.end();
                    
                    AssertThat(jt, not Equals(jend));
                    AssertThat(jt->type(), equals_v(descriptor_tag::type::user_private));
                    
                    ++jt;
                    AssertThat(jt, Equals(jend));
                }
                
                ++it;
                AssertThat(it, not Equals(end));
                AssertThat(it->elementary_pid, Equals(0x0114));
                {
                    auto jt = it->es_info.begin();
                    auto jend = it->es_info.end();
                    
                    AssertThat(jt, not Equals(jend));
                    AssertThat(jt->type(), equals_v(descriptor_tag::type::user_private));
                    
                    ++jt;
                    AssertThat(jt, not Equals(jend));
                    AssertThat(jt->type(), equals_v(descriptor_tag::type::user_private));
                    
                    ++jt;
                    AssertThat(jt, Equals(jend));
                }
                
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
