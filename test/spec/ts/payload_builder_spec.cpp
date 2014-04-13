#include <bandit_with_gmock/bandit_with_gmock.hpp>
#include <bitfield/iostream.hpp>
#include <bitfield/util.hpp>
#include <ts_processor/ts/payload_builder.hpp>

namespace ts_processor { namespace ts {
go_bandit([]{
    using namespace bandit;
    
    describe("ts::payload_builder", [&]{
        payload_builder * builder;
        
        before_each([&]{
            builder = new payload_builder;
        });
        
        describe("#clear()", [&]{
            it("should empty the container", [&]{
                builder->push(ts::packet{
                    #include <fixture/ts/psi/pmt/multi_packet_1.cpp>
                });
                AssertThat(builder->payload() == nullptr, Equals(false));
                builder->clear();
                AssertThat(builder->payload() == nullptr, Equals(true));
            });
        });
        
        describe("#payload()", [&]{
            describe("when emptied the container", [&]{
                it("should be nullptr", [&]{
                    AssertThat(builder->payload() == nullptr, Equals(true));
                });
            });
            
            describe("when not emptied the container", [&]{
                before_each([&]{
                    builder = new payload_builder;
                    builder->push(ts::packet{
                        #include <fixture/ts/psi/pmt/multi_packet_1.cpp>
                    });
                    builder->push(ts::packet{
                        #include <fixture/ts/psi/pmt/multi_packet_2.cpp>
                    });
                });
                
                it("should build a payload data from the each packets.", [&]{
                    auto & sections = builder->payload()->pmt.sections;
                    auto it = sections.begin();
                    auto end = sections.end();
                    
                    AssertThat(it, not Equals(end));
                    AssertThat(it->elementary_pid, Equals(0x0121));
                    
                    ++it;
                    AssertThat(it, not Equals(end));
                    AssertThat(it->elementary_pid, Equals(0x0112));
                    
                    ++it;
                    AssertThat(it, not Equals(end));
                    AssertThat(it->elementary_pid, Equals(0x0740));
                    
                    ++it;
                    AssertThat(it, not Equals(end));
                    AssertThat(it->elementary_pid, Equals(0x0750));
                    
                    ++it;
                    AssertThat(it, not Equals(end));
                    AssertThat(it->elementary_pid, Equals(0x0751));
                    
                    ++it;
                    AssertThat(it, not Equals(end));
                    AssertThat(it->elementary_pid, Equals(0x0752));
                    
                    ++it;
                    AssertThat(it, not Equals(end));
                    AssertThat(it->elementary_pid, Equals(0x0960));
                    
                    ++it;
                    AssertThat(it, not Equals(end));
                    AssertThat(it->elementary_pid, Equals(0x0961));
                    
                    ++it;
                    AssertThat(it, not Equals(end));
                    AssertThat(it->elementary_pid, Equals(0x075E));
                    
                    ++it;
                    AssertThat(it, not Equals(end));
                    AssertThat(it->elementary_pid, Equals(0x075F));
                    
                    ++it;
                    AssertThat(it, not Equals(end));
                    AssertThat(it->elementary_pid, Equals(0x096E));
                    
                    ++it;
                    AssertThat(it, Equals(end));
                });
            });
        });
    });
});
}}
