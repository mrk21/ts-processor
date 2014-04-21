#ifndef __INCLUDED_TS_PROCESSOR_SYMBOLSET_HPP__
#define __INCLUDED_TS_PROCESSOR_SYMBOLSET_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <regex>

namespace ts_processor {
    template<class T>
    struct symbolset {
        class info {
            std::unordered_map<uint8_t, std::string> names;
            std::unordered_map<std::string, T> symbols;
            
        public:
            info(const std::string & names_str) {
                std::regex const regex("\\w+");
                std::vector<std::string> names{
                    std::sregex_token_iterator(names_str.begin(), names_str.end(), regex),
                    std::sregex_token_iterator()
                };
                for (auto i = 0; i < names.size(); ++i) {
                    this->names[i] = names[i];
                    this->symbols[names[i]] = static_cast<T>(i);
                }
            }
            
            std::string name_of(T symbol) const {
                try {
                    return this->names.at(static_cast<uint8_t>(symbol));
                }
                catch (std::out_of_range &) {
                    throw std::invalid_argument("invalid symbol!");
                }
            }
            
            T symbol_of(const std::string & name) const {
                try {
                    return this->symbols.at(name);
                }
                catch (std::out_of_range &) {
                    throw std::invalid_argument("invalid name!");
                }
            }
        };
    };
    
#define TS_PROCESSOR_SYMBOLSET(T, ...) \
    enum class T: uint8_t { \
        __VA_ARGS__ \
    }; \
    static const ::ts_processor::symbolset<T>::info & T##_info() { \
        static ::ts_processor::symbolset<T>::info const info(#__VA_ARGS__); \
        return info; \
    } \
    friend std::ostream & operator <<(std::ostream & out, T v_) { \
        return out << T##_info().name_of(v_); \
    }
}

#endif // __INCLUDED_TS_PROCESSOR_SYMBOLSET_HPP__
