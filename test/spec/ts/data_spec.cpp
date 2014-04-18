#include <bandit_with_gmock/bandit_with_gmock.hpp>
#include <ts_processor/ts/data.hpp>
#include <bitfield/iostream.hpp>
#include <initializer_list>

namespace ts_processor { namespace ts {
go_bandit([]{
    using namespace bandit;
    
    describe("ts::data", [&]{
        ts::data * data = nullptr;
        
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
        ts::packet const _PSI_PACKET{
            #include <fixture/ts/psi/pmt/single_packet.cpp>
        };
        ts::packet const _PES_PACKET{
            #include <fixture/ts/pes/minimum.cpp>
        };
        
        auto _init = [&](uint32_t pid = 0){
            if (data == nullptr) data = new ts::data(pid);
        };
        
        after_each([&]{
            delete data;
            data = nullptr;
        });
        
        describe("#push(const ts::packet & packet)", [&]{
            auto _assert = [&](const ts::packet & target, std::initializer_list<data::push_state> expected_state_list) {
                _init(target.pid);
                
                data::push_states expected_states;
                std::size_t before_length = data->length();
                bool is_push = false;
                
                for (auto state: expected_state_list) {
                    expected_states.set(state);
                    if (state == data::push_state::pushed) is_push = true;
                }
                
                AssertThat(data->push(target), Equals(expected_states));
                AssertThat(before_length < data->length(), Equals(is_push));
            };
            
            describe("when the payload was not constructed", [&]{
                it("should contain a state of the pushed into the state_set", [&]{
                    _assert(_MULTI_PACKET_1, {data::push_state::pushed});
                });
            });
            
            describe("when the payload was completed construction", [&]{
                it("should contain a state of the ready into the state_set", [&]{
                    _assert(_MULTI_PACKET_1, {data::push_state::pushed});
                    _assert(_MULTI_PACKET_2, {data::push_state::pushed, data::push_state::ready});
                });
            });
            
            describe("after the payload was constructed", [&]{
                it("should contain a state of the ready into the state_set, on top of that, not push the packet to this container", [&]{
                    _assert(_MULTI_PACKET_1, {data::push_state::pushed});
                    _assert(_MULTI_PACKET_2, {data::push_state::pushed, data::push_state::ready});
                    _assert(_MULTI_PACKET_2, {                          data::push_state::ready});
                });
            });
            
            describe("a traits of the packet", [&]{
                describe("in case of the sync byte", [&]{
                    describe("when it was 0x47", [&]{
                        it("should push the packet to this container", [&]{
                            _assert(_MULTI_PACKET_1, {data::push_state::pushed});
                        });
                    });
                    
                    describe("when it wasn't 0x47", [&]{
                        it("should contain a state of the invalid_sync_byte into the state_set, on top of that, not push the packet to this container", [&]{
                            _assert(_INVALID_PACKET, {
                                data::push_state::invalid,
                                data::push_state::invalid_sync_byte
                            });
                        });
                    });
                });
                
                describe("in case of the PID", [&]{
                    describe("when not emptied this container" ,[&]{
                        describe("when pushed the packet of a different PID", [&]{
                            it("should contain a state of the invalid_pid into the state_set, on top of that, not push the packet to this container", [&]{
                                _assert(_DIFFERENT_PID_PACKET, {
                                    data::push_state::pushed,
                                    data::push_state::ready
                                });
                                _assert(_MULTI_PACKET_2, {
                                    data::push_state::ready,
                                    data::push_state::invalid,
                                    data::push_state::invalid_pid
                                });
                            });
                        });
                    });
                });
                
                describe("in case of the payload_unit_start_indicator", [&]{
                    describe("when emptied this container", [&]{
                        describe("when it was 1", [&]{
                            it("should push the packet to this container", [&]{
                                _assert(_MULTI_PACKET_1, {data::push_state::pushed});
                            });
                        });
                        
                        describe("when it was 0", [&]{
                            it("should contain a state of the invalid_payload_unit_start_indicator into the state_set, on top of that, not push the packet to this container", [&]{
                                _assert(_MULTI_PACKET_2, {
                                    data::push_state::invalid,
                                    data::push_state::invalid_payload_unit_start_indicator
                                });
                            });
                        });
                    });
                    
                    describe("when not emptied this container", [&]{
                        describe("when it was 1", [&]{
                            it("should contain a state of the invalid_payload_unit_start_indicator into the state_set, on top of that, not push the packet to this container", [&]{
                                _assert(_MULTI_PACKET_1, {data::push_state::pushed});
                                _assert(_MULTI_PACKET_1, {
                                    data::push_state::invalid,
                                    data::push_state::invalid_payload_unit_start_indicator
                                });
                            });
                        });
                        
                        describe("when it was 0", [&]{
                            it("should push the packet to this container", [&]{
                                _assert(_MULTI_PACKET_1, {data::push_state::pushed});
                                _assert(_MULTI_PACKET_2, {data::push_state::pushed, data::push_state::ready});
                            });
                        });
                     });
                });
            });
        });
        
        describe("#pid()", [&]{
            describe("when emptied this container", [&]{
                it("should be 0", [&]{
                    _init();
                    AssertThat(data->pid(), Equals(0));
                });
            });
            
            describe("when not emptied this container", [&]{
                it("should be a PID of the pushed packet", [&]{
                    _init(_MULTI_PACKET_1.pid);
                    data->push(_MULTI_PACKET_1);
                    AssertThat(data->pid(), Equals(_MULTI_PACKET_1.pid.get()));
                });
            });
        });
        
        describe("#reset(uint32_t pid)", [&]{
            before_each([&]{
                _init(_PSI_PACKET.pid);
                data->push(_PSI_PACKET);
            });
            
            it("should be changed to 0 this length", [&]{
                AssertThat(data->length(), not Equals(0));
                data->reset();
                AssertThat(data->length(), Equals(0));
            });
            
            it("should be changed to 0 this pid", [&]{
                AssertThat(data->pid(), not Equals(0));
                data->reset();
                AssertThat(data->pid(), Equals(0));
            });
            
            it("should be changed to the type::none this data_type", [&]{
                AssertThat(data->data_type(), Equals(data::type::psi));
                data->reset();
                AssertThat(data->data_type(), Equals(data::type::none));
            });
            
            it("should be changed to false to this is_ready", [&]{
                AssertThat(data->is_ready(), Equals(true));
                data->reset();
                AssertThat(data->is_ready(), Equals(false));
            });
        });
        
        describe("#data_type()", [&]{
            describe("when a type of this data was PSI", [&]{
                it("should be type::psi", [&]{
                    _init(_PSI_PACKET.pid);
                    data->push(_PSI_PACKET);
                    AssertThat(data->data_type(), Equals(data::type::psi));
                });
            });
            
            describe("when a type of this data was PES", [&]{
                it("should be type::pes", [&]{
                    _init(_PES_PACKET.pid);
                    data->push(_PES_PACKET);
                    AssertThat(data->data_type(), Equals(data::type::pes));
                });
            });
        });
        
        describe("#fieldset()", [&]{
            describe("when the is_ready was false", [&]{
                it("should be nullptr", [&]{
                    _init(_MULTI_PACKET_1.pid);
                    data->push(_MULTI_PACKET_1);
                    AssertThat(data->fieldset() == nullptr, Equals(true));
                });
            });
            
            describe("when the is_ready was true", [&]{
                before_each([&]{
                    _init(_MULTI_PACKET_1.pid);
                    data->push(_MULTI_PACKET_1);
                    data->push(_MULTI_PACKET_2);
                });
                
                it("should build a payload data from the each packets", [&]{
                    auto & sections = data->fieldset()->pmt.sections;
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
