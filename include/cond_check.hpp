#pragma once

#include <type_traits>

//some helper aliases/templates to make reasoning about what happens a little easier
template <bool Value = true>
using Boolean = std::integral_constant<bool, Value>;

using TrueType = Boolean<true>::type;
using FalseType = Boolean<false>::type;

using True = Boolean<true>;
using False = Boolean<false>;

template <typename Cond>
using TrueOrFail = typename std::enable_if<Cond::value, True>::type;

//can evaluate the condition into its bool value and a type
//Cond is expected to be Boolean, otherwise weird things may happen...
template <typename Cond>
struct Eval
{
    static_assert(std::is_same<Cond, TrueType>::value || std::is_same<Cond, FalseType>::value);

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
