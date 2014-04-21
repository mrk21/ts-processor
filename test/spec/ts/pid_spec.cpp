#include <bandit_with_gmock/bandit_with_gmock.hpp>
#include <ts_processor/ts/pid.hpp>
#include <iostream>

namespace ts_processor { namespace ts {
go_bandit([]{
    using namespace bandit;
    
    describe("ts::pid", [&]{
        describe("::type_of(uint32_t id)", [&]{
            describe("when the id was 0x0000", [&]{
                it("should be type::pid", [&]{
                    AssertThat(pid::type_of(0x0000), Equals(pid::type::pat));
                });
            });
            
            describe("when the id was 0x0002", [&]{
                it("should be type::tsdt", [&]{
                    AssertThat(pid::type_of(0x0002), Equals(pid::type::tsdt));
                });
            });
            
            describe("when the id was 0x0003", [&]{
                it("should be type::reserved", [&]{
                    AssertThat(pid::type_of(0x0003), Equals(pid::type::reserved));
                });
            });
            
            describe("when the id was 0x000F", [&]{
                it("should be type::reserved", [&]{
                    AssertThat(pid::type_of(0x000F), Equals(pid::type::reserved));
                });
            });
            
            describe("when the id was 0x0010", [&]{
                it("should be type::mapped", [&]{
                    AssertThat(pid::type_of(0x0010), Equals(pid::type::mapped));
                });
            });
            
            describe("when the id was 0x1FFE", [&]{
                it("should be type::mapped", [&]{
                    AssertThat(pid::type_of(0x1FFE), Equals(pid::type::mapped));
                });
            });
            
            describe("when the id was 0x1FFF", [&]{
                it("should be type::null", [&]{
                    AssertThat(pid::type_of(0x1FFF), Equals(pid::type::null));
                });
            });
            
            describe("when the id was out of range(13 bit)", [&]{
                it("should be type::invalid", [&]{
                    AssertThat(pid::type_of(-0x0001), Equals(pid::type::invalid));
                    AssertThat(pid::type_of( 0x2000), Equals(pid::type::invalid));
                    AssertThat(pid::type_of(0x10000), Equals(pid::type::invalid));
                });
            });
        });
    });
});
}}
