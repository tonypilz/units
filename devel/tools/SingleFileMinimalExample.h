#pragma once

#include <ratio>
#include <iostream>
#include <sstream>
#include <ctgmath>

namespace singleFileMinimalExample {


namespace unit {

template <typename Unit, typename MagnitudeRepresentation = double>
class Quantity {
    template <typename, typename>
    friend class Quantity;

   public:
    using unit = Unit;
    using magnitude_type = MagnitudeRepresentation;
    using classtype = Quantity<unit, magnitude_type>;

    constexpr explicit Quantity() : m_magnitude(0) {}
    constexpr explicit Quantity(magnitude_type const& v) : m_magnitude(v) {}

    constexpr Quantity(classtype const& v) = default;

    template <typename R>
    constexpr Quantity(Quantity<unit, R> const& v) : m_magnitude(v.m_magnitude) {}

    classtype& operator=(classtype const& v) = default;

    constexpr magnitude_type const& magnitude() const { return m_magnitude; }

   private:
    template <typename U, typename L, typename R>
    friend constexpr Quantity<U, L>& operator+=(Quantity<U, L>&, Quantity<U, R> const&);

    template <typename U, typename L, typename R>
    friend constexpr Quantity<U, L>& operator-=(Quantity<U, L>&, Quantity<U, R> const&);

    template <typename U, typename L, typename R>
    friend constexpr Quantity<U, L>& operator*=(Quantity<U, L>&, Quantity<U, R> const&);

    template <typename U, typename L, typename R>
    friend constexpr Quantity<U, L>& operator/=(Quantity<U, L>&, Quantity<U, R> const&);

    magnitude_type m_magnitude;
};

using TExponent = int;
using ExponentIndex = int;
using DimensionIndex = int;

template <TExponent... dimensionExponents>
struct Unit;

namespace helper {


template <typename Unit, ExponentIndex i>
constexpr TExponent exponent() {
    return Unit::template exponent_value<i>();
}

namespace nthElement {

using Index = unsigned int;

template <Index n, TExponent Arg, TExponent... Args>
struct NthElement {
    static constexpr int value() { return NthElement<n - 1, Args...>::value(); }
};

template <TExponent Arg, TExponent... Args>
struct NthElement<0, Arg, Args...> {
    static constexpr int value() { return Arg; }
};
}

namespace baseunit {

template <DimensionIndex it, DimensionIndex index, TExponent... exponents>
struct BaseUnitGen {
    using type = typename BaseUnitGen<it - 1, index, it == index ? 1 : 0, exponents...>::type;
};

template <DimensionIndex index, TExponent... exponents>
struct BaseUnitGen<-1, index, exponents...> {
    using type = Unit<exponents...>;
};
}
}

template <int dimension, int lastDimension>
using BaseUnit = typename helper::baseunit::BaseUnitGen<lastDimension, dimension>::type;

template<TExponent ... dimensionExponents >
struct Unit{

    using classtype = Unit<dimensionExponents...>;

    static constexpr unsigned exponent_count() {return sizeof...(dimensionExponents);}

    template<ExponentIndex i>
    static constexpr TExponent exponent_value() { return helper::nthElement::NthElement<i,dimensionExponents...>::value(); }
};


namespace helper {

namespace op {

template <typename U1, typename U2, int index>
struct sum {
    static constexpr int value() { return U1::template exponent_value<index>() + U2::template exponent_value<index>(); }
};

template <typename U1, typename U2, int index>
struct difference {
    static constexpr int value() { return U1::template exponent_value<index>() - U2::template exponent_value<index>(); }
};

template <typename U1, typename fract, int index>
struct multiply {
    static_assert(helper::exponent<U1, index>() * fract::num % fract::den == 0,
                  "rasing a unit to a fractional-power is not allowed");
    static constexpr int value() { return helper::exponent<U1, index>() * fract::num / fract::den; }
};

template <ExponentIndex it, typename U1, typename U2, template <class, class, int> class Op, TExponent... exponents>
struct UnitOperator {
    using type = typename UnitOperator<it - 1, U1, U2, Op, Op<U1, U2, it>::value(), exponents...>::type;
};

template <typename U1, typename U2, template <class, class, int> class Op, TExponent... exponents>
struct UnitOperator<-1, U1, U2, Op, exponents...> {
    using type = Unit<exponents...>;
};
}
}

template <typename U1, typename U2>
using product_unit = typename helper::op::UnitOperator<U1::exponent_count() - 1, U1, U2, helper::op::sum>::type;

template <typename U1, typename U2>
using quotient_unit = typename helper::op::UnitOperator<U1::exponent_count() - 1, U1, U2, helper::op::difference>::type;

template <typename U1, typename fract>
using raised_unit = typename helper::op::UnitOperator<U1::exponent_count() - 1, U1, fract, helper::op::multiply>::type;

template <typename U>
using sqare_unit = product_unit<U, U>;




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
pow(Quantity<U, T> const& q)
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




namespace helper {

template <typename ratioIn, typename ratioOut, typename T>
constexpr T rescale(T const& v) {
    using r = std::ratio_divide<ratioIn, ratioOut>;
    return v * T{r::num} / T{r::den};
}

template <typename ratioIn, typename T>
constexpr T rescaleTo1(T const& v) {
    return rescale<ratioIn, std::ratio<1>, T>(v);
}
}

template<typename T> constexpr T femto(T const& v) { return helper::rescaleTo1<std::femto>(v); }
template<typename T> constexpr T pico(T const& v) { return helper::rescaleTo1<std::pico>(v); }
template<typename T> constexpr T nano(T const& v) { return helper::rescaleTo1<std::nano>(v); }
template<typename T> constexpr T micro(T const& v) { return helper::rescaleTo1<std::micro>(v); }
template<typename T> constexpr T milli(T const& v) { return helper::rescaleTo1<std::milli>(v); }
template<typename T> constexpr T centi(T const& v) { return helper::rescaleTo1<std::centi>(v); }
template<typename T> constexpr T deci(T const& v) { return helper::rescaleTo1<std::deci>(v); }
template<typename T> constexpr T deca(T const& v) { return helper::rescaleTo1<std::deca>(v); }
template<typename T> constexpr T hecto(T const& v) { return helper::rescaleTo1<std::hecto>(v); }
template<typename T> constexpr T kilo(T const& v) { return helper::rescaleTo1<std::kilo>(v); }
template<typename T> constexpr T mega(T const& v) { return helper::rescaleTo1<std::mega>(v); }
template<typename T> constexpr T giga(T const& v) { return helper::rescaleTo1<std::giga>(v); }
template<typename T> constexpr T tera(T const& v) { return helper::rescaleTo1<std::tera>(v); }
template<typename T> constexpr T peta(T const& v) { return helper::rescaleTo1<std::peta>(v); }


namespace u {


using unitless = BaseUnit<-1, 0>;
using foo = BaseUnit<0, 0>;


using foo_inv = quotient_unit<unitless, foo>;
}

namespace t {


using unitless = Quantity<u::unitless>;
using foo = Quantity<u::foo>;


using foo_inv = Quantity<u::foo_inv>;
}

constexpr t::unitless number{1};
constexpr t::foo foo{1};
constexpr t::foo_inv foo_inv{1};

namespace literals {


constexpr t::unitless operator"" _n ( long double v ) {return t::unitless {static_cast<double>(v)};}
constexpr t::foo operator"" _foo ( long double v ) {return t::foo {static_cast<double>(v)};}

}
}



}
