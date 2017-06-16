#pragma once

#include "Unit.h"

namespace unit {



namespace helper {


//helper to shorten expressions
template<typename Unit, ExponentIndex i>
constexpr TExponent exponent(){ return Unit::template exponent_value<i>(); }



using DimensionIndex = int;

template<DimensionIndex it, DimensionIndex index, TExponent... exponents>
struct BaseUnitGen {
    using type = typename BaseUnitGen<it-1,index,it==index ? 1 : 0, exponents...>::type;
};

template<DimensionIndex index, TExponent... exponents>
struct BaseUnitGen<-1,index,exponents...> {
    using type = Unit<exponents...>;
};




}

template<int dimension, int lastDimension>
using BaseUnit = typename helper::BaseUnitGen<lastDimension,dimension>::type;


}

