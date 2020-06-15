#pragma once

#include <type_traits>

template <bool Value = true>
using Boolean = std::integral_constant<bool, Value>;

using TrueType = Boolean<true>::type;
using FalseType = Boolean<false>::type;

//can evaluate the condition into values and a type
//Cond is expected to be Boolean, otherwise weird things may happen...
template <typename Cond>
struct Eval
{
    template <typename U = Cond>
    static constexpr bool value(typename std::enable_if<std::is_same<U, TrueType>::value, void *>::type = nullptr)
    {
        return std::true_type::value;
    }

    template <typename U = Cond>
    static constexpr bool value(typename std::enable_if<std::is_same<U, FalseType>::value, void *>::type = nullptr)
    {
        return std::false_type::value;
    }

    using type = typename Cond::type;
};
