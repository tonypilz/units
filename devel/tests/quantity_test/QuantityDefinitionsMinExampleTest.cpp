#include "QuantityDefinitionsMinExampleTest.h"

#include <src/quantity/quantityDefinitionsMinimalExample.h>
#include <src/quantity/quantityOperators.h>
#include <src/quantity/quantityMath.h>
#include <src/quantity/quantityPrinting.h>
#include <src/unit/unitScaling.h>
#include <iostream>


namespace tests {

using namespace unit;
using namespace literals;

static_assert(square(2.0_n / kilo( 2.0_foo)) == square(0.001_n * foo_inv), "");

QuantityDefinitionsMinExampleTest::QuantityDefinitionsMinExampleTest()
{
    std::cout<<__FILE__<<" finished\n";
}
}
