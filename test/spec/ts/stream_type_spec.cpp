#include <bandit_with_gmock/bandit_with_gmock.hpp>
#include <ts_processor/ts/stream_type.hpp>
#include <iostream>

namespace ts_processor { namespace ts {
go_bandit([]{
    using namespace bandit;
    
    describe("ts::stream_type", [&]{
        describe("::type_of(uint32_t id)", [&]{
            auto equals_v = [](stream_type::type v){
                return Equals(v);
            };
            
            describe("when the id was 0x00", [&]{
                it("should be the type::reserved", [&]{
                    AssertThat(stream_type::type_of(0x00), equals_v(stream_type::type::reserved));
                });
            });
            
            describe("when the id was 0x01", [&]{
                it("should be the type::video", [&]{
                    AssertThat(stream_type::type_of(0x01), equals_v(stream_type::type::video));
                });
            });
            
            describe("when the id was 0x14", [&]{
                it("should be the type::other", [&]{
                    AssertThat(stream_type::type_of(0x14), equals_v(stream_type::type::other));
                });
            });
            
            describe("when the id was 0x15", [&]{
                it("should be the type::reserved", [&]{
                    AssertThat(stream_type::type_of(0x15), equals_v(stream_type::type::reserved));
                });
            });
            
            describe("when the id was 0x16", [&]{
                it("should be the type::reserved", [&]{
                    AssertThat(stream_type::type_of(0x16), equals_v(stream_type::type::reserved));
                });
            });
            
            describe("when the id was 0x7F", [&]{
                it("should be the type::reserved", [&]{
                    AssertThat(stream_type::type_of(0x7E), equals_v(stream_type::type::reserved));
                });
            });
            
            describe("when the id was 0x80", [&]{
                it("should be the type::user", [&]{
                    AssertThat(stream_type::type_of(0x80), equals_v(stream_type::type::user));
                });
            });
            
            describe("when the id was 0x81", [&]{
                it("should be the type::user", [&]{
                    AssertThat(stream_type::type_of(0x81), equals_v(stream_type::type::user));
                });
            });
            
            describe("when the id was 0xFF", [&]{
                it("should be the type::user", [&]{
                    AssertThat(stream_type::type_of(0xFF), equals_v(stream_type::type::user));
                });
            });
            
            describe("when the id was out of range(8 bit)", [&]{
                it("should be the type::invalid", [&]{
                    AssertThat(stream_type::type_of(-0x01), equals_v(stream_type::type::invalid));
                    AssertThat(stream_type::type_of(0x100), equals_v(stream_type::type::invalid));
                });
            });
        });
    });
});
}}
