#include <bandit_with_gmock/bandit_with_gmock.hpp>
#include <ts_processor/ts/stream_type.hpp>

namespace ts_processor { namespace ts {
go_bandit([]{
    using namespace bandit;
    
    describe("ts::stream_type", [&]{
        describe("::tag_of(uint8_t type)", [&]{
            describe("when the type was 0x02", [&]{
                it("should be the stream_type::tag::video", [&]{
                    AssertThat(stream_type::tag_of(0x02), Equals(stream_type::tag::video));
                });
            });
            
            describe("when the type was 0x03", [&]{
                it("should be the stream_type::tag::audio", [&]{
                    AssertThat(stream_type::tag_of(0x03), Equals(stream_type::tag::audio));
                });
            });
        });
    });
});
}}
