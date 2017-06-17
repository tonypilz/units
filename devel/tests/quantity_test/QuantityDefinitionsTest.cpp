#include "QuantityDefinitionsTest.h"

#include <src/quantity/quantityDefinitionsSI.h>
#include <src/quantity/quantityOperators.h>

#include <iostream>


namespace tests {

using namespace unit;
using namespace literals;

static_assert(273.15_kelvin == 0.0_celsius,"");

static_assert(5.0_pound > 2.26796_kilogram,"");
static_assert(5.0_pound < 2.26797_kilogram,"");

static_assert(1.0_kilofarad == 1000.0_farad,"");
static_assert(1.0_fahrenheit > 255.927_kelvin,"");
static_assert(1.0_fahrenheit < 255.928_kelvin,"");

static_assert(farad{kilo(2.0)}==farad{2000.0},"");

static_assert(2001.0_gram==kilogram{2.001},"");
static_assert(2002.0_milligram==2.002_gram,"");
static_assert(2003.0_microgram==2.003_milligram,"");

static_assert(2004.0_litre==metre_cubed{2.004},"");
static_assert(2005.0_millilitre==2.005_litre,"");

using namespace conversion;

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
