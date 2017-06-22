#include "QuantityDefinitionsTest.h"
#include "QuantityTestMain.h"

#include "odr_test/QDummyTranslationUnit1.h"
#include "odr_test/QDummyTranslationUnit2.h"

#include <src/quantity/Quantity.h>
#include <src/quantity/quantityDefinitionsSI.h>
#include <src/quantity/quantityMath.h>
#include <src/quantity/quantityOperators.h>
#include <src/quantity/quantityPrinting.h>
#include <src/quantity/quantityReading.h>

#include <complex>
#include <cassert>
#include <iostream>
#include <type_traits>

// array comparisons

#include <array>


namespace tests {


using namespace unit;



namespace u {

using    newton = Unit<1,1,-2,0>;
using    unitless = Unit<0,0,0,0>;

}

namespace t {
using    newton = Quantity<u::newton,    double>;
using    unitless = Quantity<u::unitless,    double>;

}

constexpr t::unitless unitless{1};
constexpr t::newton newton{1};


constexpr    t::newton operator""    _newton ( long double v )  {return     t::newton {static_cast<double>(v)};}
constexpr    t::unitless operator""  _unitless ( long double v )  {return   t::unitless {static_cast<double>(v)};}
constexpr    t::unitless operator""  _n ( long double v )  {return   t::unitless {static_cast<double>(v)};}
}

namespace unit {
template<> inline void print_unit<   tests::u::newton>(std::ostream& s){ s<<"N"; }
}

namespace tests {


using u_newton_sqr = product_unit<u::newton,u::newton>;
using u_newton_cub = product_unit<u_newton_sqr,u::newton>;

void quantity_test()
{
    static_assert(Quantity<u::newton,int>(4).magnitude()==4,"");
    static_assert(Quantity<u::newton,int>(Quantity<u::newton,int>{4}).magnitude()==4,"");

    {
        Quantity<u::newton,int> x(4);
        x=Quantity<u::newton,int>{5};
        assert(x.magnitude()==5);
    }
    {
        Quantity<u::newton,int> x(4);
        x.setMagnitude(Quantity<u::newton,int> (5));
        assert(x.magnitude()==5);
    }
    {
        Quantity<u::newton,int> x(4);
        x+=Quantity<u::newton,int>{5};
        assert(x.magnitude()==9);
    }
    {
        Quantity<u::newton,int> x(4);
        x-=Quantity<u::newton,int>{5};
        assert(x.magnitude()==-1);
    }
    {
        Quantity<u::newton,int> x(4);
        x*=Quantity<u::newton,int>{5};
        assert(x.magnitude()==20);
    }
    {
        Quantity<u::newton,int> x(4);
        x/=Quantity<u::newton,int>{5};
        assert(x.magnitude()==0);
    }
    {
        Quantity<u::newton,double> x(4);
        x = Quantity<u::newton,int>{5};
        assert(x.magnitude()==5);
    }


}

void complex_math_test() //complex functions are not constexpr, therefore non-static tests
{

    using T = double;
    using TComplex = std::complex<T>;
    using cnewton = Quantity<u::newton, TComplex> ;
    using ncnewton = Quantity<u::newton, T> ;
    using cnewton_sqr = Quantity<u_newton_sqr, TComplex> ;
    using cnewton_cub = Quantity<u_newton_cub, TComplex> ;


    assert(math::abs(cnewton{-7})==ncnewton{7});
    assert(math::abs(cnewton{TComplex{3,4}})==ncnewton{5});

    {
        const bool b = math::square(cnewton{TComplex{3,4}})==cnewton_sqr{TComplex{-7,24}};
        assert(b);
    }
    {
        const bool b = math::cube(cnewton{TComplex{3,4}})==cnewton_cub{TComplex{-117,44}};
        assert(b);
    }
    {
        const bool b = math::sqrt(cnewton_sqr{TComplex{-7,24}})==cnewton{TComplex{3,4}};
        assert(b);
    }

    {
        using e = std::ratio<3,2>;
        using u_src = u_newton_sqr;
        using u_dst = raised_unit<u_src,e>;
        using src = Quantity<u_src, TComplex> ;
        using dst = Quantity<u_dst, TComplex> ;

        const auto expected = dst{TComplex{2,11}};
        const auto actual = math::pow<e>(src{TComplex{3,4}});

        const auto d = math::abs(expected-actual); //rounding error
        assert(d.magnitude()<1.0e-14);
    }

    {
        const bool b = (cnewton{TComplex{1,2}} + Quantity<u::newton,double>{5}) == cnewton{TComplex{6,2}};
        assert(b);
    }

}



static_assert(math::abs(-7.0_newton)==7.0_newton,"");
static_assert(math::square(-7.5_newton)== Quantity<product_unit<u::newton,u::newton>>{56.25},"");
static_assert(math::cube(-7.5_newton)== Quantity<product_unit<u::newton,product_unit<u::newton,u::newton>>>{-421.875},"");
static_assert(math::sqrt(Quantity<product_unit<u::newton,u::newton>>{56.25})==7.5_newton,"");
//static_assert(math::sqrt(Quantity<u::newton>{56.25})==7.5_newton,""); //mustnt compile
static_assert(math::pow<std::ratio<1,2>>(math::square(-7.5_newton))==7.5_newton,"");
static_assert(math::pow<std::ratio<1>>(-7.5_newton)==-7.5_newton,"");
static_assert(math::pow<std::ratio<2>>(-7.5_newton)==math::square(-7.5_newton),"");


static_assert(math::pow<std::ratio<0>>(-7.5_newton)==1.0_unitless,"");

static_assert( 4.3_newton == 4.3_newton,"");
static_assert( 4.3_newton >= 4.3_newton,"");
static_assert( 4.3_newton <= 4.3_newton,"");
static_assert((4.3_newton != 4.3_newton) == false,"");
static_assert((4.3_newton <  4.3_newton) == false,"");
static_assert((4.3_newton >  4.3_newton) == false,"");

static_assert( 4.2_newton <  4.3_newton,"");
static_assert( 4.3_newton >  4.2_newton,"");

static_assert(4.0_newton + 5.0_newton == 9.0_newton,"");
static_assert(4.0_newton - 5.0_newton == -1.0_newton,"");
static_assert(-4.0_newton * 5.0_newton == Quantity<product_unit<u::newton,u::newton>>{-20.0},"");
static_assert(-4.0_newton / 5.0_newton == -0.8_unitless,"");

static_assert(static_unit_cast<double>(Quantity<u::newton,int>{-4})==-4.0_newton,"");


static_assert(Quantity<u::newton>{-4}==-4.0_newton,"");



static_assert(2.0_n * math::square(newton) == 20000.0_n * math::square(centi(newton)),"");




void print_derived_unit_test_v()
{
    {
        std::ostringstream s;
        s << -4.5_newton;
        if (s.str()!="-4.5N") assert(false);
    }
}

void read_unit_test_v()
{
    {
        std::istringstream s{"-4.5N"};
        Quantity<u::newton> n{1};
        s >> n;
        assert(n==-4.5_newton);
    }
    {
        std::istringstream s{"-4.5Hz"};
        Quantity<u::newton> n{1};
        s >> n;

        assert(!s);
        assert(n==1.0_newton);
    }
}

static_assert(-4.0_newton / 5.0_newton == -0.8_unitless,"");

void array_test ()
{
    using T = std::array<int,5>;
    using anewton = Quantity<u::newton, T> ;

    constexpr anewton a{T{10, 20, 30, 40, 50}};
    constexpr anewton b{T{0, 0, 0, 0, 0}};

    if (a!=a) assert(false);
    if (a<a) assert(false);
    if (a>a) assert(false);
    if (!(a==a)) assert(false);
    if (!(a>=a)) assert(false);
    if (!(a<=a)) assert(false);

    if (a==b) assert(false);
    if (a<=b) assert(false);
}




QuantityTestMain::QuantityTestMain()
{
    q::QDummyTranslationUnit1{};
    q::QDummyTranslationUnit2{};
    QuantityDefinitionsTest{};

    read_unit_test_v();
    print_derived_unit_test_v();
    complex_math_test();
    quantity_test();

    array_test();
}
}
