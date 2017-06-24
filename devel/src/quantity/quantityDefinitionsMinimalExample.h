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

namespace t {

// base units
using unitless = Quantity<u::unitless>;
using foo = Quantity<u::foo>;

// derived units
using foo_inv = Quantity<u::foo_inv>;
}

constexpr t::unitless number{1};
constexpr      t::foo foo{1};
constexpr  t::foo_inv foo_inv{1};

namespace literals {

//base units
constexpr   t::unitless operator""   _n ( long double v )  {return    t::unitless {static_cast<double>(v)};}
constexpr        t::foo operator"" _foo ( long double v )  {return         t::foo {static_cast<double>(v)};}

}
}
