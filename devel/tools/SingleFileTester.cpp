#include "SingleFileTester.h"

#include "SingleFile.h"



int rrun(int t) {

    using namespace singleFile::unit;
    using namespace singleFile::unit::literals;

    //cast ctor
    newton cz1 = 3.4_newton + Quantity<u::newton, int> {kilo(t)};

    Quantity<u::metre_per_second_squared> cz2 = cz1 / 7.3_milligram;

    for(int i=0;i<t;++i) {
        cz2 += Quantity<u::metre_per_second_squared>{micro(static_cast<double>(i))};
    }

    return static_unit_cast<int>(cz2).magnitude();
}

SingleFileTester::SingleFileTester()
{

    rrun(4);

    std::cout<<__FILE__<<"\n";


}
