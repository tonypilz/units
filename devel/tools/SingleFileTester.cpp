#include "SingleFileTester.h"

#include "SingleFile.h"

#include <src/quantity/quantityDefinitions.h>
#include <src/quantity/quantityOperators.h>

#include <ratio>
#include <ctgmath>
#include <type_traits>
#include <iostream>
#include <sstream>
#include <string>



int rrun(int t) {

    using namespace unit;
    using namespace unit::literals;

    //cast ctor
    newton cz1 = 3.4_newton + Quantity<u::newton, int> {kilo(t)};

    Quantity<u::metre_per_second_squared> cz2 = cz1 / 7.3_milligram;

    for(int i=0;i<t;++i) {
        cz2 += Quantity<u::metre_per_second_squared>{micro(static_cast<double>(i))};
    }

    return unit::static_unit_cast<int>(cz2).magnitude();
}

SingleFileTester::SingleFileTester()
{

    rrun(4);


}
