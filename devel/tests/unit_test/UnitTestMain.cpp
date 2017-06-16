#include "UnitTestMain.h"
#include "odr_test/DummyTranslationUnit1.h"
#include "odr_test/DummyTranslationUnit2.h"

#include <src/unit/Unit.h>
#include <src/unit/unitHelper.h>
#include <src/unit/unitHelper1.h>
#include <src/unit/unitOperators.h>
#include <src/unit/unitPrinting.h>
#include <src/unit/UnitReading.h>


#include <string>
#include <cassert>
#include <sstream>


namespace unit {

template<typename U> constexpr const char* unitSymbol();
template<> constexpr const char* unitSymbol<   Unit<1,0,0>>(){ return "u0";}
template<> constexpr const char* unitSymbol<   Unit<0,1,0>>(){ return "u1";}
template<> constexpr const char* unitSymbol<   Unit<0,0,1>>(){ return "u2";}

}

using namespace unit;

namespace tests {



static_assert(std::is_same<typename helper::BaseUnitGen<3,1>::type,Unit<0,1,0,0>>::value,"");
static_assert(helper::exponent<Unit<0,7,0,0,0,0,0>,1>()==7,"");
static_assert(Unit<0,7,0,0,0,0,0>::exponent_count() == 7,"");

using U_ = Unit<0,0,0,0,0,0,0,0>;
using U1 = Unit<1,2,3,4,5,6,7,8>;
using U2 = Unit<11,12,13,14,15,16,17,18>;
using U1_times_U2 = Unit<11+1,12+2,13+3,14+4,15+5,16+6,17+7,18+8>;

template<int pow>
using U1_pow = Unit<1*pow,2*pow,3*pow,4*pow,5*pow,6*pow,7*pow,8*pow>;

static_assert(std::is_same<product_unit<U1,U2>,U1_times_U2>::value,"");
static_assert(std::is_same<product_unit<U1,U_>,U1>::value,"");

static_assert(std::is_same<quotient_unit<U1_times_U2,U2>,U1>::value,"");

static_assert(std::is_same<raised_unit<U1,std::ratio<5>>,U1_pow<5>>::value,"");
static_assert(std::is_same<raised_unit<U1_pow<5>,std::ratio<1,5>>,U1>::value,"");
static_assert(std::is_same<raised_unit<U1_pow<5>,std::ratio<3,5>>,U1_pow<3>>::value,"");


static_assert(kilo(2.5)==2500.0,"");
static_assert(milli(0.5)==0.0005,"");
static_assert(milli(2)==0,""); //rounding
static_assert(milli(2002)==2,"");

static_assert(helper::rescale<std::milli,std::micro>(2.5)==2500.0,"");
static_assert(helper::rescaleTo1<std::milli>(2.5)==helper::rescale<std::milli,std::ratio<1>>(2.5),"");

void print_unit_test()
{

    {
        std::ostringstream s;
        print_unit<Unit<1,1,0>>(s);
        if (s.str()!="u0u1") assert(false);
    }
    {
        std::ostringstream s;
        print_unit<Unit<10,-11,12>>(s);
        if (s.str()!="u0^10u1^-11u2^12") assert(false);
    }

    {
        std::ostringstream s;
        print_unit<Unit<0,0,0>>(s);
        if (s.str()!="") assert(false);
    }

}

void read_unit_test()
{

    {
        std::istringstream s{"xxxxx"};
        read_unit<Unit<1,1,0>>(s);
        assert(!s);
    }

    {
        std::istringstream s{"u0^10u1^-11u2^12"};
        read_unit<Unit<10,-11,12>>(s);
        assert(s);
    }

    {
        std::istringstream s{"u0^10u1^-11u2^1"};
        read_unit<Unit<10,-11,12>>(s);
        assert(!s);
    }

}



UnitTestMain::UnitTestMain()
{
    u::DummyTranslationUnit1{};
    u::DummyTranslationUnit2{};

    print_unit_test();
    read_unit_test();

}
}
