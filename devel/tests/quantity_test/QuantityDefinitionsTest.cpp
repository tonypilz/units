#include "QuantityDefinitionsTest.h"

#include <src/quantity/quantityDefinitionsSI.h>
#include <src/quantity/quantityOperators.h>
#include <src/quantity/quantityMath.h>
#include <iostream>


namespace tests {

using namespace unit;
using namespace literals;

template<typename T, typename R = std::ratio<1,100000>>
constexpr bool near(T const& l, T const& r){ return math::abs(l-r).magnitude()<(double(R::num)/double(R::den)); }

static_assert(273.15_kelvin == 0.0_celsius,"");
static_assert(near(5.0_pound, 2.26796_kilogram),"");
static_assert(near(1.0_fahrenheit,  255.92778_kelvin),"");

static_assert(farad{kilo(2.0)}==farad{2000.0},"");

static_assert(2001.0_gram==kilogram{2.001},"");
static_assert(2002.0_milligram==2.002_gram,"");
static_assert(2003.0_microgram==2.003_milligram,"");

static_assert(2004.0_litres==metre_cubed{2.004},"");
static_assert(2005.0_millilitre==2.005_litres,"");

using namespace convert;

static_assert(fahrenheitToKelvin(-459.67)< 0.000001,"");
static_assert(fahrenheitToKelvin(-459.67)>-0.000001,"");

static_assert(fahrenheitToKelvin(0.0)>255.372,"");
static_assert(fahrenheitToKelvin(0.0)<255.373,"");

static_assert(fahrenheitToKelvin(100.0)>310.92777777,"");
static_assert(fahrenheitToKelvin(100.0)<310.92777778,"");

static_assert(celsiusToKelvin(100.0)==373.15,"");

static_assert(poundToKilogram(5.5)>2.494758035,"");
static_assert(poundToKilogram(5.5)<2.494758036,"");




QuantityDefinitionsTest::QuantityDefinitionsTest()
{
    std::cout<<__FILE__<<" finished\n";
}
}
