#pragma once

#include "type_traits"

//enum is just an integer

struct EnumToString {
    template<typename T>
    constexpr void ToString(const int&) const;
};

template<typename T>
constexpr void EnumToString::ToString(const int& value) const {
    static_assert(std::is_enum<T>()); //make sure its an enum

    
}


