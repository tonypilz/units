#pragma once

#include "Quantity.h"
#include <src/unit/unitHelper.h>
#include <src/unit/unitOperators.h>

namespace unit {

namespace u {

// base units
using unitless = BaseUnit<-1, 0>;  // == Unit<0>
using foo = BaseUnit<0, 0>;        // == Unit<1>

// derived units
using foo_inv = quotient_unit<unitless, foo>;
}

using def = double;  // default representation

// base units
using unitless = Quantity<u::unitless, def>;
using foo = Quantity<u::foo, def>;

// derived units
using foo_inv = Quantity<u::foo_inv, def>;

namespace literals {

//base units
constexpr   unitless operator"" _unitless ( long double v )  {return    unitless {static_cast<double>(v)};}
constexpr      foo operator""      _foo ( long double v )  {return       foo {static_cast<double>(v)};}

//derived units
constexpr    foo_inv operator""    _foo_inv ( long double v )  {return     foo_inv {static_cast<double>(v)};}
}
}
