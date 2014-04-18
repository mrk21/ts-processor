#include <bandit_with_gmock/bandit_with_gmock.hpp>
#include <ts_processor/ts/packet.hpp>
#include <ts_processor/ts/payload.hpp>

namespace ts_processor { namespace ts {
go_bandit([]{
    using namespace bandit;
    
    describe("ts::payload", [&]{
        ts::packet const _PES{
            #include <fixture/ts/pes/minimum.cpp>
        };
        ts::packet const _PSI{
            #include <fixture/ts/psi/pat/single_packet.cpp>
        };
        
        describe("#data_type()", [&]{
            describe("when a type of the packet was the PES", [&]{
                it("should be type::pes", [&]{
                    AssertThat(_PES.payload->data_type(), Equals(payload::type::pes));
                });
            });
            
            describe("when a type of the packet was the PSI", [&]{
                it("should be type::psi", [&]{
                    AssertThat(_PSI.payload->data_type(), Equals(payload::type::psi));
                });
            });
        });
        
        describe("#data_offset()", [&]{
            describe("when a type of the packet was the PES", [&]{
                it("should be 0", [&]{
                    AssertThat(_PES.payload->data_offset(), Equals(0));
                });
            });
            
            describe("when a type of the packet was the PSI", [&]{
                it("should be `sizeof(pointer_field) + pointer_field`", [&]{
                    AssertThat(_PSI.payload->data_offset(),
                        Equals(sizeof(payload::pointer_field_type) + _PSI.payload->pointer_field));
                });
            });
        });
        
        describe("#data_length()", [&]{
            describe("when a type of the packet was the PES", [&]{
                it("should be a length of the PES", [&]{
                    AssertThat(_PES.payload->data_length(), Equals(
                        _PES.payload->pes.pes_packet_length + sizeof(pes::base)
                    ));
                });
            });
            
            describe("when a type of the packet was the PSI", [&]{
                it("should be a length of the PSI", [&]{
                    AssertThat(_PSI.payload->data_length(), Equals(
                        _PSI.payload->psi->section_length + sizeof(psi::base)
                    ));
                });
            });
        });
    });
});
}}
