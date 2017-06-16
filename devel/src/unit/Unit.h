#pragma once

#include "unitHelper.h"

namespace unit {

using TExponent = int;
using ExponentIndex = int; //cannot be unsigned since UnitOperator uses -1 for recursion abortion

template<TExponent ... dimensionExponents >
struct Unit{

    using classtype = Unit<dimensionExponents...>;

    static constexpr unsigned exponent_count() {return sizeof...(dimensionExponents);}

    template<ExponentIndex i>
    static constexpr TExponent exponent_value() { return helper::NthElement<i,dimensionExponents...>::value(); }
};


}
