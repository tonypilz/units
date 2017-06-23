#pragma once

#include "Quantity.h"
#include <src/unit/unitOperators.h>

#include <ctgmath>

namespace std{ template<intmax_t, intmax_t > struct ratio;}

namespace unit {
namespace math {

using std::ratio;
using std::abs;
using std::sqrt;
using std::pow;

template <typename U, typename T>
constexpr Quantity<U, decltype(abs(T{}))>
abs(Quantity<U, T> const& q) {
    return Quantity<U, decltype(abs(T{}))>{abs(q.magnitude())};
}

template <typename U, typename T>
constexpr Quantity<raised_unit<U, ratio<1, 2>>, decltype(sqrt(T{}))>
sqrt(Quantity<U, T> const& q) {
    return Quantity<raised_unit<U, ratio<1, 2>>, decltype(sqrt(T{}))>{sqrt(q.magnitude())};
}

namespace helper {
template <typename power, typename T>
constexpr decltype(pow(T{}, T{}))
pow_impl(T const& v) {
    return pow(v, static_cast<double>(power::num) / static_cast<double>(power::den));
}
}

template <typename power, typename U, typename T>
constexpr Quantity<raised_unit<U, power>, decltype(helper::pow_impl<power, T>(T{}))>
pow(
    Quantity<U, T> const& q)  // pow with dynamic exponent has dynamic type
{
    return Quantity<raised_unit<U, power>, decltype(helper::pow_impl<power, T>(T{}))>{
        helper::pow_impl<power, T>(q.magnitude())};
}

template <typename U, typename T>
constexpr auto
cube(Quantity<U, T> const& q)
    -> Quantity<product_unit<product_unit<U, U>, U>, decltype((q.magnitude() * q.magnitude()) * q.magnitude())> {
    return Quantity<product_unit<product_unit<U, U>, U>, decltype((q.magnitude() * q.magnitude()) * q.magnitude())>{
        (q.magnitude() * q.magnitude()) * q.magnitude()};
}

template <typename U, typename T>
constexpr auto
square(Quantity<U, T> const& q) -> Quantity<product_unit<U, U>, decltype(q.magnitude() * q.magnitude())> {
    return Quantity<product_unit<U, U>, decltype(q.magnitude() * q.magnitude())>{q.magnitude() * q.magnitude()};
}
}
}
