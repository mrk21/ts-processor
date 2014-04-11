#include <bandit_with_gmock/bandit_with_gmock.hpp>
#include <ts_processor/ts/packet.hpp>
#include <bitfield/iostream.hpp>

namespace ts_processor { namespace ts {
go_bandit([]{
    using namespace bandit;
    
    describe("ts::packet", [&]{
        ts::packet * packet;
        
        describe("adaptation_field_container_type", [&]{
            describe("#base_addr()", [&]{
                describe("when the adaptation_field_control_type was 0b01", [&]{
                    before_each([&]{ packet = new ts::packet{{{
                        #include <fixture/ts/packet/payload_only.cpp>
                    }}}; });
                    
                    it("should be a nullptr", [&]{
                        AssertThat(packet->adaptation_field.base_addr() == nullptr, Equals(true));
                    }); 
                });
                
                describe("when the adaptation_field_control was 0b10", [&]{
                    before_each([&]{ packet = new ts::packet{{{
                        #include <fixture/ts/packet/adaptation_field_only.cpp>
                    }}}; });
                    
                    it("should not be a nullptr", [&]{
                        AssertThat(packet->adaptation_field.base_addr() == nullptr, Equals(false));
                    });
                    
                    it("'s adaptation_field_length should be 0xB7", [&]{
                        AssertThat(packet->adaptation_field->adaptation_field_length, Equals(0xB7));
                    });
                });
                
                describe("when the adaptation_field_control was 0b11", [&]{
                    before_each([&]{ packet = new ts::packet{{{
                        #include <fixture/ts/packet/adaptation_field_and_payload.cpp>
                    }}}; });
                    
                    it("should not be a nullptr", [&]{
                        AssertThat(packet->adaptation_field.base_addr() == nullptr, Equals(false));
                    });
                    
                    it("'s adaptation_field_length should be 0x3F", [&]{
                        AssertThat(packet->adaptation_field->adaptation_field_length, Equals(0x3F));
                    });
                });
            });
        });
        
        describe("payload_container_type", [&]{
            describe("#base_addr()", [&]{
                describe("when the adaptation_field_control_type was 0b01", [&]{
                    before_each([&]{ packet = new ts::packet{{{
                        #include <fixture/ts/packet/payload_only.cpp>
                    }}}; });
                    
                    it("should not be a nullptr", [&]{
                        AssertThat(packet->payload.base_addr() == nullptr, Equals(false));
                    });
                    
                    it("'s first byte should be 0x00", [&]{
                        AssertThat(static_cast<uint32_t>(*packet->payload.base_addr()), Equals(0x00));
                    });
                });
                
                describe("when the adaptation_field_control_type was 0b10", [&]{
                    before_each([&]{ packet = new ts::packet{{{
                        #include <fixture/ts/packet/adaptation_field_only.cpp>
                    }}}; });
                    
                    it("should be a nullptr", [&]{
                        AssertThat(packet->payload.base_addr() == nullptr, Equals(true));
                    });
                });
                
                describe("when the adaptation_field_control_type was 0b11", [&]{
                    before_each([&]{ packet = new ts::packet{{{
                        #include <fixture/ts/packet/adaptation_field_and_payload.cpp>
                    }}}; });
                    
                    it("should not be a nullptr", [&]{
                        AssertThat(packet->payload.base_addr() == nullptr, Equals(false));
                    });
                    
                    it("'s first byte should be 0x34", [&]{
                        AssertThat(static_cast<uint32_t>(*packet->payload.base_addr()), Equals(0x34));
                    });
                });
            });
        });
    });
});
}}
