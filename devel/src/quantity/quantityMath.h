#pragma once

#include "Quantity.h"
#include <src/unit/unitOperators.h>

#include <ctgmath>
#include <ratio>


namespace unit {


template <typename U, typename T>
constexpr auto
abs(Quantity<U, T> const& q)
        -> Quantity<U, decltype(abs(q.magnitude()))>
{
    using std::abs;
    return Quantity<U, decltype(abs(q.magnitude()))>{
                                abs(q.magnitude())};
}

template <typename U, typename T>
constexpr auto
sqrt(Quantity<U, T> const& q)
        -> Quantity<raised_unit<U, std::ratio<1, 2>>, decltype(sqrt(q.magnitude()))>
{
    using std::sqrt;
    return Quantity<raised_unit<U, std::ratio<1, 2>>, decltype(sqrt(q.magnitude()))>{
                                                               sqrt(q.magnitude())};
}

namespace helper {

template <typename power, typename T>
constexpr auto
pow_impl(T const& v)
 -> decltype(pow(v, static_cast<double>(power::num) / static_cast<double>(power::den)))

{
    using std::pow;
    return pow(v, static_cast<double>(power::num) / static_cast<double>(power::den));
}

}

template <typename power, typename U, typename T>
constexpr auto
pow(Quantity<U, T> const& q)  // cmath pow function has dynamic exponent and therefore dynamic return unit type and therefore cannot be realized by Quantity
        -> Quantity<raised_unit<U, power>, decltype(helper::pow_impl<power, T>(q.magnitude()))>
{
    return Quantity<raised_unit<U, power>, decltype(helper::pow_impl<power, T>(q.magnitude()))>{
                                                    helper::pow_impl<power, T>(q.magnitude())};
}

template <typename U, typename T>
constexpr auto
cube(Quantity<U, T> const& q)
        -> Quantity<product_unit<product_unit<U, U>, U>, decltype((q.magnitude() * q.magnitude()) * q.magnitude())>
{
    return Quantity<product_unit<product_unit<U, U>, U>, decltype((q.magnitude() * q.magnitude()) * q.magnitude())>{
                                                                  (q.magnitude() * q.magnitude()) * q.magnitude()};
}

template <typename U, typename T>
constexpr auto
square(Quantity<U, T> const& q)
        -> Quantity<product_unit<U, U>, decltype(q.magnitude() * q.magnitude())>
{
    return Quantity<product_unit<U, U>, decltype(q.magnitude() * q.magnitude())>{
                                                 q.magnitude() * q.magnitude()};
}




}
