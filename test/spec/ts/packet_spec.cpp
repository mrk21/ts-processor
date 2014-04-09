#include <bandit_with_gmock/bandit_with_gmock.hpp>
#include <ts_processor/ts/packet.hpp>
#include <bitfield/iostream.hpp>

namespace ts_processor { namespace ts {
go_bandit([]{
    using namespace bandit;
    
    describe("ts::packet", [&]{
        ts::packet * packet;
        
        describe("#adaptation_field()", [&]{
            describe("when the adaptation_field_control_type was 0b01", [&]{
                before_each([&]{ packet = new ts::packet{{{
                    #include <fixture/ts/packet/payload_only.txt>
                }}}; });
                
                it("should be a nullptr", [&]{
                    AssertThat(packet->adaptation_field() == nullptr, Equals(true));
                }); 
            });
            
            describe("when the adaptation_field_control was 0b10", [&]{
                before_each([&]{ packet = new ts::packet{{{
                    #include <fixture/ts/packet/adaptation_field_only.txt>
                }}}; });
                
                it("should not be a nullptr", [&]{
                    AssertThat(packet->adaptation_field() == nullptr, Equals(false));
                });
                
                it("'s adaptation_field_length should be 0xB7", [&]{
                    AssertThat(packet->adaptation_field()->adaptation_field_length, Equals(0xB7));
                });
            });
            
            describe("when the adaptation_field_control was 0b11", [&]{
                before_each([&]{ packet = new ts::packet{{{
                    #include <fixture/ts/packet/adaptation_field_with_payload.txt>
                }}}; });
                
                it("should not be a nullptr", [&]{
                    AssertThat(packet->adaptation_field() == nullptr, Equals(false));
                });
                
                it("'s adaptation_field_length should be 0x3F", [&]{
                    AssertThat(packet->adaptation_field()->adaptation_field_length, Equals(0x3F));
                });
            });
        });
        
        describe("#payload()", [&]{
            describe("when the adaptation_field_control_type was 0b01", [&]{
                before_each([&]{ packet = new ts::packet{{{
                    #include <fixture/ts/packet/payload_only.txt>
                }}}; });
                
                it("should not be a nullptr", [&]{
                    AssertThat(packet->payload() == nullptr, Equals(false));
                });
                
                it("'s first byte should be 0x00", [&]{
                    AssertThat(static_cast<uint32_t>(packet->payload()->container[0]), Equals(0x00));
                });
            });
            
            describe("when the adaptation_field_control_type was 0b10", [&]{
                before_each([&]{ packet = new ts::packet{{{
                    #include <fixture/ts/packet/adaptation_field_only.txt>
                }}}; });
                
                it("should be a nullptr", [&]{
                    AssertThat(packet->payload() == nullptr, Equals(true));
                });
            });
            
            describe("when the adaptation_field_control_type was 0b11", [&]{
                before_each([&]{ packet = new ts::packet{{{
                    #include <fixture/ts/packet/adaptation_field_with_payload.txt>
                }}}; });
                
                it("should not be a nullptr", [&]{
                    AssertThat(packet->payload() == nullptr, Equals(false));
                });
                
                it("'s first byte should be 0x34", [&]{
                    AssertThat(static_cast<uint32_t>(packet->payload()->container[0]), Equals(0x34));
                });
            });
        });
    });
});
}}
