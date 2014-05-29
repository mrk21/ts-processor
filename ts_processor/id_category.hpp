#ifndef __INCLUDED_TS_PROCESSOR_ID_CATEGORY_HPP__
#define __INCLUDED_TS_PROCESSOR_ID_CATEGORY_HPP__

#include <symbolset/symbolset.hpp>
#include <unordered_map>
#include <initializer_list>

namespace ts_processor {
    // Template parameter T is derived class.
    // You must define as shown below to the all derived class:
    // 
    // class derived_class: public base_class {
    //     friend class id_category_helper<derived_class>;
    //     using helper = id_category_helper<derived_class>;
    //     
    // public:
    //     using base_type = base_class::type;
    //     
    //     SYMBOLSET_DEFINE(type, base_type, (value1,...));
    //     
    //     derived_class() {
    //         this->assign({
    //             {{1}, type::value1},
    //             ...
    //         });
    //     }
    //     
    //     static type type_of(uint32_t id) {
    //         return helper::type_of(id);
    //     }
    // };
    // 
    template<class T>
    class id_category {
    public:
        SYMBOLSET_DEFINE(type, (
            reserved
        ))
        
    protected:
        std::unordered_map<uint32_t, typename type::value_type> data;
        
        struct database_schema {
            std::vector<uint32_t> id;
            typename type::value_type type;
        };
        
        void assign(std::initializer_list<database_schema> data) {
            for (auto & v: data) {
                switch (v.id.size()) {
                case 1:
                    this->data[v.id[0]] = v.type;
                    break;
                    
                case 2:
                    for (uint16_t id = v.id[0]; id <= v.id[1]; ++id) {
                        this->data[id] = v.type;
                    }
                    break;
                }
            }
        }
    };
    
    
    template<class IDCategory>
    class id_category_helper {
        using self = id_category_helper;
        
    protected:
        static IDCategory instance;
        
    public:
        static typename IDCategory::type type_of(uint32_t id) {
            try {
                return self::instance.data.at(id);
            }
            catch (std::out_of_range &) {
                return IDCategory::type::invalid;
            }
        }
    };
    
    template<class IDCategory>
    IDCategory id_category_helper<IDCategory>::instance;
}

#endif // __INCLUDED_TS_PROCESSOR_ID_CATEGORY_HPP__
