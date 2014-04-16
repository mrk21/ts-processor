#include <bandit_with_gmock/bandit_with_gmock.hpp>
#include <bitfield/iostream.hpp>
#include <bitfield/util.hpp>
#include <ts_processor/ts/payload_builder.hpp>

namespace ts_processor { namespace ts {
    namespace payload_builder_test {
        template<class Exception>
        struct push_test {
            void operator ()(payload_builder * builder, const ts::packet & packet, bool expected_is_throw_exception){
                using namespace bandit;
                
                bool is_throw_exception = false;
                std::size_t size = builder->size();
                
                try {
                    builder->push(packet);
                }
                catch (Exception & e) {
                    is_throw_exception = true;
                }
                catch (...) {}
                
                AssertThat(is_throw_exception, Equals(expected_is_throw_exception));
                AssertThat(builder->size(), Equals(size + (expected_is_throw_exception ? 0:1)));
            }
        };
    }
    
go_bandit([]{
    using namespace bandit;
    using namespace payload_builder_test;
    
    describe("ts::payload_builder", [&]{
        payload_builder * builder;
        
        ts::packet const _MULTI_PACKET_1{
            #include <fixture/ts/psi/pmt/multi_packet_1.cpp>
        };
        ts::packet const _MULTI_PACKET_2{
            #include <fixture/ts/psi/pmt/multi_packet_2.cpp>
        };
        ts::packet const _DIFFERENT_PID_PACKET{
            #include <fixture/ts/psi/pat/single_packet.cpp>
        };
        ts::packet const _INVALID_PACKET{
            #include <fixture/ts/packet/invalid_sync_byte.cpp>
        };
        
        before_each([&]{
            builder = new payload_builder;
        });
        
        describe("#push(const ts::packet & packet)", [&]{
            describe("return value", [&]{
                describe("when the payload was not constructed", [&]{
                    it("should be false", [&]{
                        AssertThat(builder->push(_MULTI_PACKET_1), Equals(false));
                    });
                });
                
                describe("when the payload was completed construction", [&]{
                    it("should be true", [&]{
                        builder->push(_MULTI_PACKET_1);
                        AssertThat(builder->push(_MULTI_PACKET_2), Equals(true));
                    });
                });
                
                describe("after the payload was constructed", [&]{
                    it("should return true, on top of that, not push the packet to this container", [&]{
                        builder->push(_MULTI_PACKET_1);
                        AssertThat(builder->push(_MULTI_PACKET_2), Equals(true));
                        std::size_t size = builder->size();
                        AssertThat(builder->push(_MULTI_PACKET_2), Equals(true));
                        AssertThat(builder->size(), Equals(size));
                    });
                });
            });
            
            describe("packet", [&]{
                describe("a sync byte of the packet", [&]{
                    describe("when it was 0x47", [&]{
                        it("should push the packet to this container", [&]{
                            push_test<payload_builder::invalid_sync_byte_exception>()(builder, _MULTI_PACKET_1, false);
                        });
                    });
                    
                    describe("when it wasn't 0x47", [&]{
                        it("should throw a invalid_sync_byte_exception, on top of that, not push the packet to this container", [&]{
                            push_test<payload_builder::invalid_sync_byte_exception>()(builder, _INVALID_PACKET, true);
                        });
                    });
                });
                
                describe("a PID of the packet", [&]{
                    describe("when not emptied this container" ,[&]{
                        describe("when pushed the packet of a different PID", [&]{
                            it("should throw a invalid_pid_exeption, on top of that, not push the packet to this container", [&]{
                                builder->push(_DIFFERENT_PID_PACKET);
                                push_test<payload_builder::invalid_pid_exeption>()(builder, _MULTI_PACKET_2, true);
                            });
                        });
                    });
                });
                
                describe("a payload_unit_start_indicator of the packet", [&]{
                    describe("when emptied this container", [&]{
                        describe("when it was 1", [&]{
                            it("should push the packet to this container", [&]{
                                push_test<payload_builder::invalid_payload_unit_start_indicator_exception>()(builder, _MULTI_PACKET_1, false);
                            });
                        });
                        
                        describe("when it was 0", [&]{
                            it("should throw a invalid_payload_unit_start_indicator_exception, on top of that, not push the packet to this container", [&]{
                                push_test<payload_builder::invalid_payload_unit_start_indicator_exception>()(builder, _MULTI_PACKET_2, true);
                            });
                        });
                    });
                    
                    describe("when not emptied this container", [&]{
                        describe("when it was 1", [&]{
                            it("should throw a invalid_payload_unit_start_indicator_exception, on top of that, not push the packet to this container", [&]{
                                builder->push(_MULTI_PACKET_1);
                                push_test<payload_builder::invalid_payload_unit_start_indicator_exception>()(builder, _MULTI_PACKET_1, true);
                            });
                        });
                        
                        describe("when it was 0", [&]{
                            it("should push the packet to this container", [&]{
                                builder->push(_MULTI_PACKET_1);
                                push_test<payload_builder::invalid_payload_unit_start_indicator_exception>()(builder, _MULTI_PACKET_2, false);
                            });
                        });
                     });
                });
            });
        });
        
        describe("#current_pid()", [&]{
            describe("when emptied this container", [&]{
                it("should be -1", [&]{
                    AssertThat(builder->current_pid(), Equals(-1));
                });
            });
            
            describe("when not emptied this container", [&]{
                it("should be a PID of the pushed packet", [&]{
                    builder->push(_MULTI_PACKET_1);
                    AssertThat(builder->current_pid(), Equals(_MULTI_PACKET_1.pid.get()));
                });
            });
        });
        
        describe("#empty()", [&]{
            describe("when emptied this container", [&]{
                it("should be true", [&]{
                    AssertThat(builder->empty(), Equals(true));
                });
            });
            
            describe("when not emptied this container", [&]{
                it("should be false", [&]{
                    builder->push(_MULTI_PACKET_1);
                    AssertThat(builder->empty(), Equals(false));
                });
            });
        });
        
        describe("#clear()", [&]{
            before_each([&]{
                builder->push(_MULTI_PACKET_1);
            });
            
            it("should empty this container", [&]{
                AssertThat(builder->empty(), Equals(false));
                builder->clear();
                AssertThat(builder->empty(), Equals(true));
            });
            
            it("should be changed to 0 a size", [&]{
                AssertThat(builder->size(), Equals(1));
                builder->clear();
                AssertThat(builder->size(), Equals(0));
            });
            
            it("should be changed to -1 a current pid", [&]{
                AssertThat(builder->current_pid(), not Equals(-1));
                builder->clear();
                AssertThat(builder->current_pid(), Equals(-1));
            });
        });
        
        describe("#payload()", [&]{
            describe("when emptied this container", [&]{
                it("should be nullptr", [&]{
                    AssertThat(builder->payload() == nullptr, Equals(true));
                });
            });
            
            describe("when not emptied this container", [&]{
                before_each([&]{
                    builder->push(_MULTI_PACKET_1);
                    builder->push(_MULTI_PACKET_2);
                });
                
                it("should build a payload data from the each packets", [&]{
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
