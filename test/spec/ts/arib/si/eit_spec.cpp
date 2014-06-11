#include <bandit_with_gmock/bandit_with_gmock.hpp>
#include <ts_processor/ts/data.hpp>
#include <ts_processor/ts/arib/si/eit.hpp>
#include <ts_processor/ts/arib/pid.hpp>
#include <bitfield/iostream.hpp>

namespace ts_processor { namespace ts { namespace arib { namespace si {
go_bandit([]{
    using namespace bandit;
    
    describe("ts::arib::ps::eit", [&]{
        ts::data data;
        
        before_each([&]{
            ts::packet packet{
                #include <fixture/ts/arib/si/eit/single_packet.cpp>
            };
            data.reset(ts::arib::pid::id::eit);
            data.push(packet);
        });
        
        describe("#events", [&]{
            it("should iterate each fieldset in the event list", [&]{
                auto & events = data->psi.get<eit>()->events;
                auto it = events.begin();
                auto end = events.end();
                
                AssertThat(it, not Equals(end));
                AssertThat(it->event_id, Equals(0x0001));
                {
                    auto jt = it->descriptors.begin();
                    auto jend = it->descriptors.end();
                    
                    AssertThat(jt, not Equals(jend));
                    AssertThat(jt->descriptor_tag, Equals(0x4D));
                    AssertThat(jt->descriptor_length, Equals(0x03));
                    
                    ++jt;
                    AssertThat(jt, not Equals(jend));
                    AssertThat(jt->descriptor_tag, Equals(0x4D));
                    AssertThat(jt->descriptor_length, Equals(0x02));
                    
                    ++jt;
                    AssertThat(jt, not Equals(jend));
                    AssertThat(jt->descriptor_tag, Equals(0x4D));
                    AssertThat(jt->descriptor_length, Equals(0x04));
                    
                    ++jt;
                    AssertThat(jt, Equals(jend));
                }
                
                ++it;
                AssertThat(it, not Equals(end));
                AssertThat(it->event_id, Equals(0x0002));
                {
                    auto jt = it->descriptors.begin();
                    auto jend = it->descriptors.end();
                    
                    AssertThat(jt, not Equals(jend));
                    AssertThat(jt->descriptor_tag, Equals(0x4D));
                    AssertThat(jt->descriptor_length, Equals(0x01));
                    
                    ++jt;
                    AssertThat(jt, not Equals(jend));
                    AssertThat(jt->descriptor_tag, Equals(0x4D));
                    AssertThat(jt->descriptor_length, Equals(0x04));
                    
                    ++jt;
                    AssertThat(jt, not Equals(jend));
                    AssertThat(jt->descriptor_tag, Equals(0x4D));
                    AssertThat(jt->descriptor_length, Equals(0x02));
                    
                    ++jt;
                    AssertThat(jt, Equals(jend));
                }
                
                ++it;
                AssertThat(it, Equals(end));
            });
        });
    });
});
}}}}
