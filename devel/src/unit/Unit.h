#pragma once

#include "unitHelper.h"
#include "unitTypes.h"

namespace unit {

template<TExponent ... dimensionExponents >
struct Unit{

    using classtype = Unit<dimensionExponents...>;

    static constexpr unsigned exponent_count() {return sizeof...(dimensionExponents);}

    template<ExponentIndex i>
    static constexpr TExponent exponent_value() { return helper::nthElement::NthElement<i,dimensionExponents...>::value(); }
};

}
