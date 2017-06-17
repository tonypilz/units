#pragma once

#include "unitTypes.h"

namespace unit {

template <TExponent... dimensionExponents>
struct Unit;

namespace helper {

// helper to shorten access
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
}
