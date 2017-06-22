#include "SingleFileTester.h"

#include "SingleFileSi.h"
#include "SingleFileMinimalExample.h"



int run_si(int t) {

    using namespace singleFileSi::unit;
    using namespace singleFileSi::unit::literals;

    //cast ctor
    t::newton cz1 = 3.4_n * newton + Quantity<u::newton, int> {kilo(t)};

    Quantity<u::meter_per_second_squared> cz2 = cz1 / 7.3_n / milli(gram);

    for(int i=0;i<t;++i) {
        cz2 += Quantity<u::meter_per_second_squared>{micro(static_cast<double>(i))};
    }

    return static_unit_cast<int>(cz2).magnitude();
}

int run_minimalExample(int t) {

    using namespace singleFileMinimalExample::unit;
    using namespace singleFileMinimalExample::unit::literals;

    //cast ctor
    t::foo cz1 = 3.4_foo + Quantity<u::foo, int> {kilo(t)};

    t::unitless cz2 = cz1 / 7.3_n / foo;

    for(int i=0;i<t;++i) {
        cz2 += t::unitless{micro(static_cast<double>(i))};
    }

    return static_unit_cast<int>(cz2).magnitude();
}


SingleFileTester::SingleFileTester()
{

    run_si(4);

    std::cout<<__FILE__<<"\n";


}
