#include <tests/quantity_test/odr_test/QuantityHeaders.h>
#include <tests/unit_test/odr_test/UnitHeaders.h>
#include <src/quantity/quantityDefinitionsSI.h>
#include <tools/pysConstsantsGeneration/generated/physicalConstants.h>

#include <iostream>
#include <sstream>
#include <ratio>
#include <sstream>

namespace tmp {


int run()
{

    using namespace unit;
    using namespace unit::literals;

    std::cout<<(physicalConstant::atomic_unit_of_2nd_hyperpolarizability* physicalConstant::uncertaintiy::atomic_unit_of_2nd_hyperpolarizability)<<"\n";

    newton force = 2.0_meter * 3.0_kilogram / math::square(2.0_second);

    std::cout<<force<<"\n"; //prints "1.5N"

    force+=5.0_newton;

    std::cout<<force<<"\n"; //prints "6.5N"

    return 0;

}


}
