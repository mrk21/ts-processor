#include <bandit_with_gmock/bandit_with_gmock.hpp>
#include <bitfield/iostream.hpp>
#include <bitfield/util.hpp>
#include <ts_processor/ts/payload_builder.hpp>
#include <initializer_list>

namespace ts_processor { namespace ts {
go_bandit([]{
    using namespace bandit;
    
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
            auto _assert = [&](const ts::packet & target, std::initializer_list<payload_builder::status> expected_statuses) {
                payload_builder::status_set expected_status_set;
                std::size_t expected_size = builder->size();
                
                for (auto status: expected_statuses) {
                    expected_status_set.set(status);
                    if (status == payload_builder::status::PUSHED) ++expected_size;
                }
                
                AssertThat(builder->push(target), Equals(expected_status_set));
                AssertThat(builder->size(), Equals(expected_size));
            };
            
            describe("when the payload was not constructed", [&]{
                it("should contain a status of the PUSHED into the status_set", [&]{
                    _assert(_MULTI_PACKET_1, {payload_builder::status::PUSHED});
                });
            });
            
            describe("when the payload was completed construction", [&]{
                it("should contain a status of the COMPLETED into the status_set", [&]{
                    _assert(_MULTI_PACKET_1, {payload_builder::status::PUSHED});
                    _assert(_MULTI_PACKET_2, {payload_builder::status::PUSHED, payload_builder::status::COMPLETED});
                });
            });
            
            describe("after the payload was constructed", [&]{
                it("should contain a status of the COMPLETED into the status_set, on top of that, not push the packet to this container", [&]{
                    _assert(_MULTI_PACKET_1, {payload_builder::status::PUSHED});
                    _assert(_MULTI_PACKET_2, {payload_builder::status::PUSHED, payload_builder::status::COMPLETED});
                    _assert(_MULTI_PACKET_2, {                                 payload_builder::status::COMPLETED});
                });
            });
            
            describe("a traits of the packet", [&]{
                describe("in case of the sync byte", [&]{
                    describe("when it was 0x47", [&]{
                        it("should push the packet to this container", [&]{
                            _assert(_MULTI_PACKET_1, {payload_builder::status::PUSHED});
                        });
                    });
                    
                    describe("when it wasn't 0x47", [&]{
                        it("should contain a status of the INVALID_SYNC_BYTE into the status_set, on top of that, not push the packet to this container", [&]{
                            _assert(_INVALID_PACKET, {
                                payload_builder::status::INVALID,
                                payload_builder::status::INVALID_SYNC_BYTE
                            });
                        });
                    });
                });
                
                describe("in case of the PID", [&]{
                    describe("when not emptied this container" ,[&]{
                        describe("when pushed the packet of a different PID", [&]{
                            it("should contain a status of the INVALID_PID into the status_set, on top of that, not push the packet to this container", [&]{
                                _assert(_DIFFERENT_PID_PACKET, {
                                    payload_builder::status::PUSHED,
                                    payload_builder::status::COMPLETED
                                });
                                _assert(_MULTI_PACKET_2, {
                                    payload_builder::status::COMPLETED,
                                    payload_builder::status::INVALID,
                                    payload_builder::status::INVALID_PID
                                });
                            });
                        });
                    });
                });
                
                describe("in case of the payload_unit_start_indicator", [&]{
                    describe("when emptied this container", [&]{
                        describe("when it was 1", [&]{
                            it("should push the packet to this container", [&]{
                                _assert(_MULTI_PACKET_1, {payload_builder::status::PUSHED});
                            });
                        });
                        
                        describe("when it was 0", [&]{
                            it("should contain a status of the INVALID_PAYLOAD_UNIT_START_INDICATOR into the status_set, on top of that, not push the packet to this container", [&]{
                                _assert(_MULTI_PACKET_2, {
                                    payload_builder::status::INVALID,
                                    payload_builder::status::INVALID_PAYLOAD_UNIT_START_INDICATOR
                                });
                            });
                        });
                    });
                    
                    describe("when not emptied this container", [&]{
                        describe("when it was 1", [&]{
                            it("should contain a status of the INVALID_PAYLOAD_UNIT_START_INDICATOR into the status_set, on top of that, not push the packet to this container", [&]{
                                _assert(_MULTI_PACKET_1, {payload_builder::status::PUSHED});
                                _assert(_MULTI_PACKET_1, {
                                    payload_builder::status::INVALID,
                                    payload_builder::status::INVALID_PAYLOAD_UNIT_START_INDICATOR
                                });
                            });
                        });
                        
                        describe("when it was 0", [&]{
                            it("should push the packet to this container", [&]{
                                _assert(_MULTI_PACKET_1, {payload_builder::status::PUSHED});
                                _assert(_MULTI_PACKET_2, {payload_builder::status::PUSHED, payload_builder::status::COMPLETED});
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
