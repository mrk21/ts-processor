#include <bandit_with_gmock/bandit_with_gmock.hpp>
#include <ts_processor/id_category.hpp>

namespace ts_processor {
    namespace id_category_test {
        class basic: public id_category<basic> {
            friend class id_category_helper<basic>;
            using helper = id_category_helper<basic>;
            
        public:
            using base_type = id_category::type;
            
            SYMBOLSET_DEFINE(type, base_type, (
                a,
                b
            ))
            
            basic() {
                this->assign({
                    {{2}, type::a},
                    {{3}, type::b},
                    {{4,10}, type::reserved},
                });
            }
            
            static type type_of(uint32_t id) {
                return helper::type_of(id);
            }
        };
        
        class derived: public basic {
            friend class id_category_helper<derived>;
            using helper = id_category_helper<derived>;
            
        public:
            using base_type = basic::type;
            
            SYMBOLSET_DEFINE(type, base_type, (
                d,
                e,
                f
            ))
            
            derived() {
                this->assign({
                    {{4}, type::d},
                    {{5}, type::e},
                    {{6}, type::f},
                });
            }
            
            static type type_of(uint32_t id) {
                return helper::type_of(id);
            }
        };
    }
    
go_bandit([]{
    using namespace bandit;
    
    describe("id_category<T>", [&]{
        using namespace id_category_test;
        
        describe("::type_of(uint32_t id)", [&]{
            it("should be the type of the id", [&]{
                // basic
                AssertThat(basic::type_of(1) == basic::type::invalid, Equals(true));
                AssertThat(basic::type_of(2) == basic::type::a, Equals(true));
                AssertThat(basic::type_of(3) == basic::type::b, Equals(true));
                AssertThat(basic::type_of(4) == basic::type::reserved, Equals(true));
                AssertThat(basic::type_of(5) == basic::type::reserved, Equals(true));
                AssertThat(basic::type_of(9) == basic::type::reserved, Equals(true));
                AssertThat(basic::type_of(10) == basic::type::reserved, Equals(true));
                AssertThat(basic::type_of(11) == basic::type::invalid, Equals(true));
                
                // derived
                AssertThat(derived::type_of(1) == derived::type::invalid, Equals(true));
                AssertThat(derived::type_of(2) == derived::type::a, Equals(true));
                AssertThat(derived::type_of(3) == derived::type::b, Equals(true));
                AssertThat(derived::type_of(4) == derived::type::d, Equals(true));
                AssertThat(derived::type_of(5) == derived::type::e, Equals(true));
                AssertThat(derived::type_of(6) == derived::type::f, Equals(true));
                AssertThat(derived::type_of(7) == derived::type::reserved, Equals(true));
                AssertThat(derived::type_of(8) == derived::type::reserved, Equals(true));
                AssertThat(derived::type_of(9) == derived::type::reserved, Equals(true));
                AssertThat(derived::type_of(10) == derived::type::reserved, Equals(true));
                AssertThat(derived::type_of(11) == derived::type::invalid, Equals(true));
            });
        });
    });
});
}
