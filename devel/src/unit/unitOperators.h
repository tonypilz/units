#pragma once

#include "Unit.h"
#include "unitHelper.h"
#include <type_traits>

namespace unit {

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
}
