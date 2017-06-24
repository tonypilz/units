#include "QuantityDefinitionsSiTest.h"

#include <src/quantity/quantityDefinitionsSI.h>
#include <src/quantity/quantityOperators.h>
#include <src/quantity/quantityMath.h>
#include <src/quantity/quantityPrinting.h>
#include <iostream>


namespace tests {

using namespace unit;
using namespace literals;

template<typename T, typename R = std::ratio<1,100000>>
constexpr bool near(T const& l, T const& r){ return abs(l-r).magnitude()<(double(R::num)/double(R::den)); }

//celsius
static_assert(273.15_n * kelvin == celsius(0.0), "");
static_assert(0.0_n * kelvin == celsius(-273.15), "");
static_assert(near(celsius(100.0),373.15_n * kelvin),"");

//fahrenheit
static_assert(near(fahrenheit(1.0), 255.92778_n * kelvin), "");
static_assert(near(fahrenheit(-459.67),0.0_n * kelvin),"");
static_assert(near(fahrenheit(0),255.37222222_n * kelvin),"");
static_assert(near(fahrenheit(100.0),310.92777777_n * kelvin),"");


static_assert(5.0_n * inch == 0.127_n * meter,"");
static_assert(5.0_n * food == 1.524_n * meter,"");
static_assert(5.0_n * mile == 8046.72_n * meter,"");
static_assert(5.0_n * yard == 4.572_n * meter,"");

static_assert(near(5.5_n * pound, 2.494758035_n * kilogram),"");
static_assert(near(5.0_n * pound, 2.26796_n * kilogram), "");
static_assert(5.0_n * gram  == 0.005_n * kilogram,"");
static_assert(2001.0_n * gram == t::kilogram{2.001}, "");
static_assert(2002.0_n * milli(gram) == 2.002_n * gram, "");
static_assert(2003.0_n * micro(gram) == 2.003_n * milli(gram), "");

static_assert(2.0_n * minute == 120.0_n * second,"");
static_assert(2.0_n * hour == 120.0_n * minute,"");
static_assert(2.0_n * day == 48.0_n * hour,"");

static_assert(2000.0_n * calorie == 8368.0_n * joule,"");
static_assert(2.0_n * watt_hour == 7200.0_n * joule,"");

static_assert(2004.0_n * liter == 2.004_n * cube(meter), "");
static_assert(2005.0_n * milli(liter) == 2.005_n * liter, "");
static_assert(near(10.0_n * gallon,37.8541_n * liter),"");

static_assert(2.0_n * bar == 200000.0_n * pascal,"");

static_assert(mega(2.0_n) * parts_per_million == 2.0_n,"");
static_assert(200.0_n * percent == 2.0_n,"");


static_assert(2.0_n * kilo(farad) == 2000.0_n * farad, "");
static_assert(kilo( 2.0_n * farad) == t::farad{2000.0}, "");
static_assert(kilo( 2.0_n * farad) == t::farad{kilo(2)}, "");



QuantityDefinitionsSiTest::QuantityDefinitionsSiTest()
{
    std::cout<<__FILE__<<" finished\n";
}
}
