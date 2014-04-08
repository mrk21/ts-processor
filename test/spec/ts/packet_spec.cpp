#include <bandit_with_gmock/bandit_with_gmock.hpp>

namespace ts_analyzer { namespace ts {
go_bandit([]{
    using namespace bandit;
    
    describe("ts_analyzer::ts::packet", [&]{
        it("should be true", [&]{
            AssertThat(true, Equals(true));
        });
    });
});
}}
