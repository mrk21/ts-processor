#include <bandit_with_gmock/bandit_with_gmock.hpp>
#include <ts_processor/ts/psi/base.hpp>
#include <ts_processor/ts/packet.hpp>
#include <bitfield/iostream.hpp>

namespace ts_processor { namespace ts { namespace psi {
go_bandit([]{
    using namespace bandit;
    
    describe("ts::psi::base", [&]{
        describe("#crc_32()", [&]{
            it("should be last 4 bytes", [&]{
                ts::packet packet{
                    #include <fixture/ts/psi/pat/single_packet.cpp>
                };
                AssertThat(packet.payload->psi->crc_32(), Equals(0x903F0A85));
            });
        });
    });
});
}}}
