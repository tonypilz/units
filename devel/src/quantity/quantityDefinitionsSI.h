#pragma once

#include "Quantity.h"
#include <src/unit/unitHelper.h>
#include <src/unit/unitOperators.h>
#include <src/unit/unitScaling.h>
#include "quantityOperators.h"
#include "quantityMath.h"

#include <ratio>
#include <ostream>


namespace unit {

namespace u { //units

//these units are taken from https://en.wikipedia.org/wiki/International_System_of_Units

//base units
using unitless = BaseUnit<-1,6>;// == Unit<0,...,0>

using    meter = BaseUnit<0,6>; // == Unit<1,0,...,0>
using kilogram = BaseUnit<1,6>;
using   second = BaseUnit<2,6>;
using   ampere = BaseUnit<3,6>;
using   kelvin = BaseUnit<4,6>;
using     mole = BaseUnit<5,6>;
using  candela = BaseUnit<6,6>; // == Unit<0,...,0,1>



//derived units
using    radian = unitless;
using steradian = unitless;
using     hertz = quotient_unit< unitless, second>;
using    newton = quotient_unit< product_unit<kilogram, meter>, sqare_unit<second>>;
using    pascal = quotient_unit< newton,  sqare_unit<meter>>;
using     joule = quotient_unit< newton,  meter>;
using      watt = quotient_unit< joule,   second>;
using   coulomb = product_unit<  second,  ampere>;
using      volt = quotient_unit< watt,    ampere>;
using     farad = quotient_unit< coulomb, volt>;
using       ohm = quotient_unit< volt,    ampere>;
using   siemens = quotient_unit< ampere,  volt>;
using     weber = product_unit<  volt,    second>;
using     tesla = quotient_unit< weber,   sqare_unit<meter>>;
using     henry = quotient_unit< weber,   ampere>;
using     lumen = product_unit<  candela, steradian>;
using       lux = quotient_unit< lumen,   sqare_unit<meter>>;
using becquerel = hertz;
using      gray = quotient_unit< joule,   kilogram>;
using   sievert = gray;
using     katal = quotient_unit< mole,    second>;


//useful custom units
using meter_cubed              = product_unit<  meter, sqare_unit<meter>>;
using meter_per_second         = quotient_unit< meter, second>;
using meter_per_second_squared = quotient_unit< meter, sqare_unit<second>>;

using mol_inv   = quotient_unit< unitless, mole>;

}

namespace t { //quantity types

    using def = double; //default representation

    //base units
    using unitless = Quantity<u::unitless, def>;
    using    meter = Quantity<u::meter,    def>;
    using kilogram = Quantity<u::kilogram, def>;
    using   second = Quantity<u::second,   def>;
    using   ampere = Quantity<u::ampere,   def>;
    using   kelvin = Quantity<u::kelvin,   def>;
    using     mole = Quantity<u::mole,     def>;
    using  candela = Quantity<u::candela,  def>;

    //derived units
    using    radian = Quantity<u::radian,    def>;
    using steradian = Quantity<u::steradian, def>;
    using     hertz = Quantity<u::hertz,     def>;
    using    newton = Quantity<u::newton,    def>;
    using    pascal = Quantity<u::pascal,    def>;
    using     joule = Quantity<u::joule,     def>;
    using      watt = Quantity<u::watt,      def>;
    using   coulomb = Quantity<u::coulomb,   def>;
    using      volt = Quantity<u::volt,      def>;
    using     farad = Quantity<u::farad,     def>;
    using       ohm = Quantity<u::ohm,       def>;
    using   siemens = Quantity<u::siemens,   def>;
    using     weber = Quantity<u::weber,     def>;
    using     tesla = Quantity<u::tesla,     def>;
    using     henry = Quantity<u::henry,     def>;
    using     lumen = Quantity<u::lumen,     def>;
    using       lux = Quantity<u::lux,       def>;
    using becquerel = Quantity<u::becquerel, def>;
    using      gray = Quantity<u::gray,      def>;
    using   sievert = Quantity<u::sievert,   def>;
    using     katal = Quantity<u::katal,     def>;

    //custom units
    using meter_cubed = Quantity<u::meter_cubed, def>;
}


constexpr t::unitless unitless{1};
constexpr    t::meter meter{1};
constexpr t::kilogram kilogram{1};
constexpr   t::second second{1};
constexpr   t::ampere ampere{1};
constexpr   t::kelvin kelvin{1};
constexpr     t::mole mole{1};
constexpr  t::candela candela{1};

//derived units
constexpr    t::radian radian{1};
constexpr t::steradian steradian{1};
constexpr     t::hertz hertz{1};
constexpr    t::newton newton{1};
constexpr    t::pascal pascal{1};
constexpr     t::joule joule{1};
constexpr      t::watt watt{1};
constexpr   t::coulomb coulomb{1};
constexpr      t::volt volt{1};
constexpr     t::farad farad{1};
constexpr       t::ohm ohm{1};
constexpr   t::siemens siemens{1};
constexpr     t::weber weber{1};
constexpr     t::tesla tesla{1};
constexpr     t::henry henry{1};
constexpr     t::lumen lumen{1};
constexpr       t::lux lux{1};
constexpr t::becquerel becquerel{1};
constexpr      t::gray gray{1};
constexpr   t::sievert sievert{1};
constexpr     t::katal katal{1};

//according to https://www.nist.gov/sites/default/files/documents/pml/wmd/metric/SP1038.pdf
constexpr       t::meter inch{centi(2.54)}; //(ft)
constexpr       t::meter food{0.3048}; //(ft)
constexpr       t::meter mile{1609.344}; //international (5280 ft)(mi)
constexpr       t::meter yard{0.9144}; //(yd)
constexpr    t::kilogram pound{0.45359237}; //avoirdupois
constexpr    t::kilogram ounce{0.02834952}; //avoirdupois
constexpr    t::kilogram gram{helper::rescale<std::ratio<1>,std::kilo>(1.0)};
constexpr      t::second minute{60};
constexpr      t::second hour{60*60};
constexpr      t::second day{60*60*24};
constexpr       t::joule calorie{4.184}; //pyhsical unit!
constexpr       t::joule watt_hour{3600};
constexpr t::meter_cubed liter{0.001};
constexpr t::meter_cubed gallon{3.785412 * 0.001};
constexpr      t::pascal bar{kilo(100)};
constexpr    t::unitless parts_per_million{micro(1.0)};
constexpr    t::unitless percent{centi(1.0)};




//temperature
constexpr    t::kelvin     celsius ( double v ){ return t::kelvin {static_cast<double>(v+273.15)};}
constexpr    t::kelvin  fahrenheit ( double v ){ return t::kelvin {static_cast<double>((v+459.67)*5.0/9.0)};}


namespace literals {

constexpr   t::unitless operator"" _unitless ( long double v )  {return t::unitless {static_cast<double>(v)};}
constexpr   t::unitless operator""   _number ( long double v )  {return t::unitless {static_cast<double>(v)};}
constexpr   t::unitless operator""        _n ( long double v )  {return t::unitless {static_cast<double>(v)};}
constexpr   t::newton   operator""   _newton ( long double v )  {return   t::newton {static_cast<double>(v)};}

}


template<typename U> constexpr const char* unitSymbol();
template<> inline constexpr const char* unitSymbol<   u::meter>(){ return "m";}
template<> inline constexpr const char* unitSymbol<u::kilogram>(){ return "kg";}
template<> inline constexpr const char* unitSymbol<  u::second>(){ return "s";}
template<> inline constexpr const char* unitSymbol<  u::ampere>(){ return "A";}
template<> inline constexpr const char* unitSymbol<  u::kelvin>(){ return "K";}
template<> inline constexpr const char* unitSymbol<    u::mole>(){ return "mol";}
template<> inline constexpr const char* unitSymbol< u::candela>(){ return "cd";}

//derived units

template<typename U> void print_unit(std::ostream& s);
//template<> void print_unit<   def::radian>(std::ostream& s){ s<<"rad"; }
//template<> inline void print_unit<def::steradian>(std::ostream& s){ s<<"sr"; }
template<> inline void print_unit<    u::hertz>(std::ostream& s){ s<<"Hz"; }
template<> inline void print_unit<   u::newton>(std::ostream& s){ s<<"N"; }
template<> inline void print_unit<   u::pascal>(std::ostream& s){ s<<"Pa"; }
template<> inline void print_unit<    u::joule>(std::ostream& s){ s<<"J"; }
template<> inline void print_unit<     u::watt>(std::ostream& s){ s<<"W"; }
template<> inline void print_unit<  u::coulomb>(std::ostream& s){ s<<"C"; }
template<> inline void print_unit<     u::volt>(std::ostream& s){ s<<"V"; }
template<> inline void print_unit<    u::farad>(std::ostream& s){ s<<"F"; }
template<> inline void print_unit<      u::ohm>(std::ostream& s){ s<<"Ohm"; }  //actually "Ω", but encoding problem
template<> inline void print_unit<  u::siemens>(std::ostream& s){ s<<"S"; }
template<> inline void print_unit<    u::weber>(std::ostream& s){ s<<"Wb"; }
template<> inline void print_unit<    u::tesla>(std::ostream& s){ s<<"T"; }
template<> inline void print_unit<    u::henry>(std::ostream& s){ s<<"H"; }
template<> inline void print_unit<    u::lumen>(std::ostream& s){ s<<"lm"; }
template<> inline void print_unit<      u::lux>(std::ostream& s){ s<<"Lx"; }
//template<> inline void print_unit<becquerel>(std::ostream& s){ s<<"Bq"; }
template<> inline void print_unit<     u::gray>(std::ostream& s){ s<<"Gy"; }
//template<> inline void print_unit<  sievert>(std::ostream& s){ s<<"Sv"; }
template<> inline void print_unit<    u::katal>(std::ostream& s){ s<<"ka"; }

}

