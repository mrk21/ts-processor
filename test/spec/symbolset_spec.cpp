#include <bandit_with_gmock/bandit_with_gmock.hpp>
#include <ts_processor/symbolset.hpp>
#include <algorithm>

namespace ts_processor {
    struct enum_symbol_test {
        TS_PROCESSOR_SYMBOLSET(type,
            value1,
            value2,
            value3,
        )
    };
    
go_bandit([]{
    using namespace bandit;
    
    describe("symbolset<T>::info", [&]{
        symbolset<enum_symbol_test::type>::info const info("  value1,value2,\n value3\n,  ");
        
        describe("#name_of(T symbol)", [&]{
            it("should be a name of the symbol", [&]{
                AssertThat(info.name_of(enum_symbol_test::type::value1), Equals("value1"));
            });
            
            describe("when the symbol was invalid", [&]{
                it("should throw the std::invalid_argument", [&]{
                    bool is_throw_exception = false;
                    
                    try {
                        info.name_of(static_cast<enum_symbol_test::type>(100));
                    }
                    catch (std::invalid_argument &) {
                        is_throw_exception = true;
                    }
                    catch (...) {}
                    
                    AssertThat(is_throw_exception, Equals(true));
                });
            });
        });
        
        describe("#symbol_of(const std::string & name)", [&]{
            it("should be a symbol of the name", [&]{
                AssertThat(info.symbol_of("value2"), Equals(enum_symbol_test::type::value2));
            });
            
            describe("when the name was invalid", [&]{
                it("should throw the std::invalid_argument", [&]{
                    bool is_throw_exception = false;
                    
                    try {
                        info.symbol_of("aaa");
                    }
                    catch (std::invalid_argument &) {
                        is_throw_exception = true;
                    }
                    catch (...) {}
                    
                    AssertThat(is_throw_exception, Equals(true));
                });
            });
        });
    });
    
    describe("TS_PROCESSOR_SYMBOLSET(T, ...)", [&]{
        describe("T_info().name_of(T symbol)", [&]{
            it("should be the string of the symbol", [&]{
                AssertThat(enum_symbol_test::type_info().name_of(enum_symbol_test::type::value1), Equals("value1"));
            });
        });
    });
});
}
