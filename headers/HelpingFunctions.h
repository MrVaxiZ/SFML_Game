#pragma once

#include <string>
#include <sstream>
#include <type_traits>
#include <typeinfo>   // for typeid
#include <iostream>   // for std::declval, std::ostream
#include "Aliases.h"


// 1) Detection idiom: checks if T can be streamed with std::ostream
template <typename T, typename = void>
struct is_streamable : std::false_type {};

template <typename T>
struct is_streamable<T, std::void_t<decltype(std::declval<std::ostream&>() << std::declval<T>())>>
    : std::true_type {
};

// 2) The actual conversion function
template <typename T>
std::string toString(const T& value)
{
    // If arithmetic (int, float, double, etc.), use std::to_string
    if constexpr (std::is_arithmetic_v<T>)
    {
        return std::to_string(value);
    }
    // If the type is implicitly convertible to std::string, just use that
    else if constexpr (std::is_convertible_v<T, std::string>)
    {
        return static_cast<std::string>(value);
    }
    // If T is streamable (operator<< works), use stringstream
    else if constexpr (is_streamable<T>::value)
    {
        std::ostringstream oss;
        oss << value; // this is valid only if T is streamable
        return oss.str();
    }
    // if T is specifically sf::Keyboard::Key, cast to int
    else if constexpr (std::is_same_v<T, sf::Keyboard::Key>)
    {
        return std::to_string(static_cast<int>(value));
    }
    // Fallback: we have no idea how to make it a string, so return a generic name
    else
    {
        return std::string{ "[Unconvertible type: " } + typeid(T).name() + "]";
    }
}