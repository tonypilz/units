#pragma once

#include "Quantity.h"
#include <src/unit/unitOperators.h>

#include <ctgmath>
#include <ratio>
#include <type_traits>


namespace unit {
namespace math {

template< typename U, typename T>
constexpr
Quantity<U, decltype(std::abs(T{})) >
abs(Quantity<U, T> const& q)
{
    return Quantity<U, decltype(std::abs(T{})) >{
        std::abs(q.magnitude())};
}

template< typename U, typename T>
constexpr
Quantity<raised_unit<U,std::ratio<1,2>>, decltype(std::sqrt(T{}))>
sqrt(Quantity<U, T> const& q)
{
    return Quantity<raised_unit<U,std::ratio<1,2>>, decltype(std::sqrt(T{}))>{
        std::sqrt(q.magnitude())};
}

namespace helper {
template<typename power, typename T>
constexpr
decltype(std::pow(T{},T{}))
pow_impl(T const& v)
{
    return std::pow(v, static_cast<double>(power::num)/static_cast<double>(power::den));
}

}

template<typename power, typename U, typename T>
constexpr
Quantity<raised_unit<U,power>, decltype(helper::pow_impl<power,T>(T{}))>
pow(Quantity<U, T> const& q) //pow with dynamic exponent has dynamic type
{
    return Quantity<raised_unit<U,power>, decltype(helper::pow_impl<power,T>(T{}))>{
        helper::pow_impl<power,T>(q.magnitude())};
}


template< typename U, typename T>
constexpr auto cube(Quantity<U, T> const& q)
    ->  Quantity<product_unit<product_unit<U,U>,U>, decltype((q.magnitude()*q.magnitude())*q.magnitude())>
{
    return  Quantity<product_unit<product_unit<U,U>,U>, decltype((q.magnitude()*q.magnitude())*q.magnitude())> {
                                                                   (q.magnitude()*q.magnitude())*q.magnitude()};
}

template< typename U, typename T>
constexpr auto square(Quantity<U, T> const& q)
    ->  Quantity<product_unit<U,U>, decltype(q.magnitude()*q.magnitude())>
{
    return  Quantity<product_unit<U,U>, decltype(q.magnitude()*q.magnitude())> {
                                                   q.magnitude()*q.magnitude()};
}

}
}

