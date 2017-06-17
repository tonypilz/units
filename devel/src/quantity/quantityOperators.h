#pragma once

#include "Quantity.h"
#include <src/unit/unitOperators.h>

namespace unit {

/**
 *  This function casts eg from Quantity<x,double> -> Quantity<x,int>
 */
template <typename TDst, typename QSrc>
constexpr Quantity<typename QSrc::unit, TDst> static_unit_cast(QSrc const& l) {
    return Quantity<typename QSrc::unit, TDst>{static_cast<TDst>(l.magnitude())};
}

template <typename U, typename LT, typename RT>
constexpr Quantity<U, LT>& operator+=(Quantity<U, LT>& l, Quantity<U, RT> const& r) {
    return l.m_magnitude += r.m_magnitude, l;
}

template <typename U, typename LT, typename RT>
constexpr Quantity<U, LT>& operator-=(Quantity<U, LT>& l, Quantity<U, RT> const& r) {
    return l.m_magnitude -= r.m_magnitude, l;
}

template <typename U, typename LT, typename RT>
constexpr Quantity<U, LT>& operator*=(Quantity<U, LT>& l, Quantity<U, RT> const& r) {
    return l.m_magnitude *= r.m_magnitude, l;
}

template <typename U, typename LT, typename RT>
constexpr Quantity<U, LT>& operator/=(Quantity<U, LT>& l, Quantity<U, RT> const& r) {
    return l.m_magnitude /= r.m_magnitude, l;
}

template <typename LU, typename LT, typename RU, typename RT>
constexpr auto operator*(Quantity<LU, LT> const& l, Quantity<RU, RT> const& r)
    -> Quantity<product_unit<LU, RU>, decltype(l.magnitude() * r.magnitude())> {
    return Quantity<product_unit<LU, RU>, decltype(l.magnitude() * r.magnitude())>{l.magnitude() * r.magnitude()};
}

template <typename LU, typename LT, typename RU, typename RT>
constexpr auto operator/(Quantity<LU, LT> const& l, Quantity<RU, RT> const& r)
    -> Quantity<quotient_unit<LU, RU>, decltype(l.magnitude() / r.magnitude())> {
    return Quantity<quotient_unit<LU, RU>, decltype(l.magnitude() / r.magnitude())>{l.magnitude() / r.magnitude()};
}

template <typename U, typename LT, typename RT>
constexpr auto operator+(Quantity<U, LT> const& l, Quantity<U, RT> const& r)
    -> Quantity<U, decltype(l.magnitude() + r.magnitude())> {
    return Quantity<U, decltype(l.magnitude() + r.magnitude())>{l.magnitude() + r.magnitude()};
}

template <typename U, typename LT, typename RT>
constexpr auto operator-(Quantity<U, LT> const& l, Quantity<U, RT> const& r)
    -> Quantity<U, decltype(l.magnitude() - r.magnitude())> {
    return Quantity<U, decltype(l.magnitude() - r.magnitude())>{l.magnitude() - r.magnitude()};
}

template <typename U, typename LT, typename RT>
constexpr bool operator<(Quantity<U, LT> const& l, Quantity<U, RT> const& r) {
    return l.magnitude() < r.magnitude();
}

template <typename U, typename LT, typename RT>
constexpr bool operator<=(Quantity<U, LT> const& l, Quantity<U, RT> const& r) {
    return l.magnitude() <= r.magnitude();
}

template <typename U, typename LT, typename RT>
constexpr bool operator>(Quantity<U, LT> const& l, Quantity<U, RT> const& r) {
    return l.magnitude() > r.magnitude();
}

template <typename U, typename LT, typename RT>
constexpr bool operator>=(Quantity<U, LT> const& l, Quantity<U, RT> const& r) {
    return l.magnitude() >= r.magnitude();
}

template <typename U, typename LT, typename RT>
constexpr bool operator==(Quantity<U, LT> const& l, Quantity<U, RT> const& r) {
    return l.magnitude() == r.magnitude();
}

template <typename U, typename LT, typename RT>
constexpr bool operator!=(Quantity<U, LT> const& l, Quantity<U, RT> const& r) {
    return l.magnitude() != r.magnitude();
}

template <typename LU, typename LT>
constexpr Quantity<LU, LT> operator-(Quantity<LU, LT> const& l) {
    return Quantity<LU, LT>{-l.magnitude()};
}
}
