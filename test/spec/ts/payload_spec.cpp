#include <bandit_with_gmock/bandit_with_gmock.hpp>
#include <ts_processor/ts/packet.hpp>
#include <ts_processor/ts/payload.hpp>

namespace ts_processor { namespace ts {
go_bandit([]{
    using namespace bandit;
    
    describe("ts::payload", [&]{
        describe("#length()", [&]{
            describe("when a packet type was the PES", [&]{
                it("should be a length of the PES", [&]{
                    ts::packet packet{
                        #include <fixture/ts/pes/minimum.cpp>
                    };
                    AssertThat(packet.payload->length(), Equals(
                        packet.payload->pes.pes_packet_length +
                        bitfield::bit_type(pes::base::pes_packet_length_type::NEXT_OFFSET).byte()
                    ));
                });
            });
            
            describe("when a packet type was the PSI", [&]{
                it("should be a length of the PSI", [&]{
                    ts::packet packet{
                        #include <fixture/ts/psi/pat/single_packet.cpp>
                    };
                    AssertThat(packet.payload->length(), Equals(
                        packet.payload->psi.section_length +
                        sizeof(uint8_t) + 
                        bitfield::bit_type(psi::base::section_length_type::NEXT_OFFSET).byte()
                    ));
                });
            });
        });
    });
});
}}
