#include <bandit_with_gmock/bandit_with_gmock.hpp>
#include <ts_processor/ts/stream_type.hpp>
#include <iostream>

namespace ts_processor { namespace ts {
    std::ostream & operator <<(std::ostream & out, stream_type::tag tag) {
        out << static_cast<uint32_t>(tag);
        return out;
    }
    
go_bandit([]{
    using namespace bandit;
    
    describe("ts::stream_type", [&]{
        describe("::tag_of(uint32_t id)", [&]{
            describe("when the id was 0x00", [&]{
                it("should be the stream_type::tag::reserved", [&]{
                    AssertThat(stream_type::tag_of(0x00), Equals(stream_type::tag::reserved));
                });
            });
            
            describe("when the id was 0x01", [&]{
                it("should be the stream_type::tag::video", [&]{
                    AssertThat(stream_type::tag_of(0x01), Equals(stream_type::tag::video));
                });
            });
            
            describe("when the id was 0x14", [&]{
                it("should be the stream_type::tag::other", [&]{
                    AssertThat(stream_type::tag_of(0x14), Equals(stream_type::tag::other));
                });
            });
            
            describe("when the id was 0x15", [&]{
                it("should be the stream_type::tag::reserved", [&]{
                    AssertThat(stream_type::tag_of(0x15), Equals(stream_type::tag::reserved));
                });
            });
            
            describe("when the id was 0x16", [&]{
                it("should be the stream_type::tag::reserved", [&]{
                    AssertThat(stream_type::tag_of(0x16), Equals(stream_type::tag::reserved));
                });
            });
            
            describe("when the id was 0x7F", [&]{
                it("should be the stream_type::tag::reserved", [&]{
                    AssertThat(stream_type::tag_of(0x7E), Equals(stream_type::tag::reserved));
                });
            });
            
            describe("when the id was 0x80", [&]{
                it("should be the stream_type::tag::user", [&]{
                    AssertThat(stream_type::tag_of(0x80), Equals(stream_type::tag::user));
                });
            });
            
            describe("when the id was 0x81", [&]{
                it("should be the stream_type::tag::user", [&]{
                    AssertThat(stream_type::tag_of(0x81), Equals(stream_type::tag::user));
                });
            });
            
            describe("when the id was 0xFF", [&]{
                it("should be the stream_type::tag::user", [&]{
                    AssertThat(stream_type::tag_of(0xFF), Equals(stream_type::tag::user));
                });
            });
            
            describe("when converted to the uint8_t from the value that to overflow and underflow", [&]{
                describe("when the id was -0x01(uint8_t: 0xFF)", [&]{
                    it("should be the stream_type::tag::user", [&]{
                        AssertThat(stream_type::tag_of(-0x01), Equals(stream_type::tag::user));
                    });
                });
                
                describe("when the id was -0x81(uint8_t: 0x7F)", [&]{
                    it("should be the stream_type::tag::reserved", [&]{
                        AssertThat(stream_type::tag_of(-0x81), Equals(stream_type::tag::reserved));
                    });
                });
                
                describe("when the id was 0x100(uint8_t: 0x00)", [&]{
                    it("should be the stream_type::tag::reserved", [&]{
                        AssertThat(stream_type::tag_of(0x100), Equals(stream_type::tag::reserved));
                    });
                });
                
                describe("when the id was 0x101(uint8_t: 0x01)", [&]{
                    it("should be the stream_type::tag::video", [&]{
                        AssertThat(stream_type::tag_of(0x101), Equals(stream_type::tag::video));
                    });
                });
            });
        });
    });
});
}}
