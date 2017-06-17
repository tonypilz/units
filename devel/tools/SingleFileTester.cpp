#include "SingleFileTester.h"

#include "SingleFileSi.h"
#include "SingleFileMinimalExample.h"



int run_si(int t) {

    using namespace singleFileSi::unit;
    using namespace singleFileSi::unit::literals;

    //cast ctor
    newton cz1 = 3.4_newton + Quantity<u::newton, int> {kilo(t)};

    Quantity<u::metre_per_second_squared> cz2 = cz1 / 7.3_milligram;

    for(int i=0;i<t;++i) {
        cz2 += Quantity<u::metre_per_second_squared>{micro(static_cast<double>(i))};
    }

    return static_unit_cast<int>(cz2).magnitude();
}

int run_minimalExample(int t) {

    using namespace singleFileMinimalExample::unit;
    using namespace singleFileMinimalExample::unit::literals;

    //cast ctor
    foo cz1 = 3.4_foo + Quantity<u::foo, int> {kilo(t)};

    unitless cz2 = cz1 / 7.3_foo;

    for(int i=0;i<t;++i) {
        cz2 += unitless{micro(static_cast<double>(i))};
    }

    return static_unit_cast<int>(cz2).magnitude();
}


SingleFileTester::SingleFileTester()
{

    run_si(4);

    std::cout<<__FILE__<<"\n";


}
