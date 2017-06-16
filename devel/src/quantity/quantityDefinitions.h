#pragma once

#include "Quantity.h"
#include <src/unit/unitHelper1.h>
#include <src/unit/unitOperators.h>

#include <ratio>
#include <ostream>

//////////////////////////////definitions///////////////////////////////////////////

namespace unit {

namespace u {

//these units are taken from https://en.wikipedia.org/wiki/International_System_of_Units

//base units
using unitless = BaseUnit<-1,7>;// == Unit<0,...,0>

using    metre = BaseUnit<0,7>; // == Unit<1,0,...,0>
using kilogram = BaseUnit<1,7>;
using   second = BaseUnit<2,7>;
using   ampere = BaseUnit<3,7>;
using   kelvin = BaseUnit<4,7>;
using     mole = BaseUnit<5,7>;
using  candela = BaseUnit<6,7>;
using      foo = BaseUnit<7,7>; // == Unit<0,...,0,1>

using metre_per_second_squared = quotient_unit< metre, sqare_unit<second>>;

//derived units
using    radian = unitless;
using steradian = unitless;
using     hertz = quotient_unit< unitless, second>;
using    newton = quotient_unit< product_unit<kilogram, metre>, sqare_unit<second>>;
using    pascal = quotient_unit< newton,  sqare_unit<metre>>;
using     joule = quotient_unit< newton,  metre>;
using      watt = quotient_unit< joule,   second>;
using   coulomb = product_unit<  second,  ampere>;
using      volt = quotient_unit< watt,    ampere>;
using     farad = quotient_unit< coulomb, volt>;
using       ohm = quotient_unit< volt,    ampere>;
using   siemens = quotient_unit< ampere,  volt>;
using     weber = product_unit<  volt,    second>;
using     tesla = quotient_unit< weber,   sqare_unit<metre>>;
using     henry = quotient_unit< weber,   ampere>;
using     lumen = product_unit<  candela, steradian>;
using       lux = quotient_unit< lumen,   sqare_unit<metre>>;
using becquerel = hertz;
using      gray = quotient_unit< joule,   kilogram>;
using   sievert = gray;
using     katal = quotient_unit< mole,    second>;


//useful custom units
using metre_cubed              = product_unit<  metre, sqare_unit<metre>>;
using metre_per_second         = quotient_unit< metre, second>;
using metre_per_second_squared = quotient_unit< metre, sqare_unit<second>>;

using mol_inv   = quotient_unit< unitless, mole>;

}

using def = double; //default representation

//base units
using unitless = Quantity<u::unitless, def>;
using    metre = Quantity<u::metre,    def>;
using kilogram = Quantity<u::kilogram, def>;
using   second = Quantity<u::second,   def>;
using   ampere = Quantity<u::ampere,   def>;
using   kelvin = Quantity<u::kelvin,   def>;
using     mole = Quantity<u::mole,     def>;
using  candela = Quantity<u::candela,  def>;
using      foo = Quantity<u::foo,      def>;

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
using metre_cubed = Quantity<u::metre_cubed, def>;

using mol_inv = Quantity<u::mol_inv,     def>;



namespace conversion {

constexpr long double kilogramsPerPound = 0.45359237;
constexpr long double zeroDegreeCelsiusInKelvin = 273.15;


constexpr double fahrenheitToKelvin(long double v ) { return static_cast<double>((v+459.67)*(5.0/9.0)); }
constexpr double celsiusToKelvin(long double v ) { return static_cast<double>(v+zeroDegreeCelsiusInKelvin); }
constexpr double poundToKilogram(long double v ) { return static_cast<double>(v*kilogramsPerPound); }

}

namespace constants {

constexpr unitless pi{ 3.14159265359 };
constexpr mol_inv Avogadro{ 6.022140857e23 };

}

namespace literals {

//base units
constexpr   unitless operator"" _unitless ( long double v )  {return    unitless {static_cast<double>(v)};}
constexpr   unitless operator""       _ul ( long double v )  {return    unitless {static_cast<double>(v)};}

constexpr    metre operator""    _metre ( long double v )  {return     metre {static_cast<double>(v)};}
constexpr kilogram operator"" _kilogram ( long double v )  {return  kilogram {static_cast<double>(v)};}
constexpr   second operator""   _second ( long double v )  {return    second {static_cast<double>(v)};}
constexpr   ampere operator""   _ampere ( long double v )  {return    ampere {static_cast<double>(v)};}
constexpr   kelvin operator""   _kelvin ( long double v )  {return    kelvin {static_cast<double>(v)};}
constexpr     mole operator""     _mole ( long double v )  {return      mole {static_cast<double>(v)};}
constexpr  candela operator""  _candela ( long double v )  {return   candela {static_cast<double>(v)};}
constexpr      foo operator""      _foo ( long double v )  {return       foo {static_cast<double>(v)};}


//derived units
constexpr    radian operator""    _radian ( long double v )  {return     radian {static_cast<double>(v)};}
constexpr steradian operator"" _steradian ( long double v )  {return  steradian {static_cast<double>(v)};}
constexpr     hertz operator""     _hertz ( long double v )  {return      hertz {static_cast<double>(v)};}
constexpr    newton operator""    _newton ( long double v )  {return     newton {static_cast<double>(v)};}
constexpr    pascal operator""    _pascal_ ( long double v )  {return     pascal {static_cast<double>(v)};} // _pascal is reserved by clang
constexpr     joule operator""     _joule ( long double v )  {return      joule {static_cast<double>(v)};}
constexpr      watt operator""      _watt ( long double v )  {return       watt {static_cast<double>(v)};}
constexpr   coulomb operator""   _coulomb ( long double v )  {return    coulomb {static_cast<double>(v)};}
constexpr      volt operator""      _volt ( long double v )  {return       volt {static_cast<double>(v)};}
constexpr     farad operator""     _farad ( long double v )  {return      farad {static_cast<double>(v)};}
constexpr       ohm operator""       _ohm ( long double v )  {return        ohm {static_cast<double>(v)};}
constexpr   siemens operator""   _siemens ( long double v )  {return    siemens {static_cast<double>(v)};}
constexpr     weber operator""     _weber ( long double v )  {return      weber {static_cast<double>(v)};}
constexpr     tesla operator""     _tesla ( long double v )  {return      tesla {static_cast<double>(v)};}
constexpr     henry operator""     _henry ( long double v )  {return      henry {static_cast<double>(v)};}
constexpr     lumen operator""     _lumen ( long double v )  {return      lumen {static_cast<double>(v)};}
constexpr       lux operator""       _lux ( long double v )  {return        lux {static_cast<double>(v)};}
constexpr becquerel operator"" _becquerel ( long double v )  {return  becquerel {static_cast<double>(v)};}
constexpr      gray operator""      _gray ( long double v )  {return       gray {static_cast<double>(v)};}
constexpr   sievert operator""   _sievert ( long double v )  {return    sievert {static_cast<double>(v)};}
constexpr     katal operator""     _katal ( long double v )  {return      katal {static_cast<double>(v)};}

constexpr    kelvin operator""    _celsius ( long double v ){ return     kelvin {conversion::celsiusToKelvin(v)};}
constexpr  kilogram operator""      _pound ( long double v ){ return   kilogram {conversion::poundToKilogram(v)};}
constexpr     farad operator""  _kilofarad ( long double v ){ return      farad {static_cast<double>(kilo(v))};}
constexpr    kelvin operator"" _fahrenheit ( long double v ){ return     kelvin {conversion::fahrenheitToKelvin(v)}; }


//special case mass since baseunit is prefixed with 'kilo'
constexpr kilogram operator"" _microgram ( long double v )  {return  kilogram {helper::rescale<std::micro,std::kilo>(static_cast<double>(v))};}
constexpr kilogram operator"" _milligram ( long double v )  {return  kilogram {helper::rescale<std::milli,std::kilo>(static_cast<double>(v))};}
constexpr kilogram operator"" _gram      ( long double v )  {return  kilogram {helper::rescale<std::ratio<1>,std::kilo>(static_cast<double>(v))};}

template<typename ratio>
using ratio_cubed = std::ratio_multiply< std::ratio_multiply<ratio,ratio>,ratio>;

//custom units
constexpr metre_cubed operator"" _litre      ( long double v )  {return  metre_cubed {helper::rescaleTo1<ratio_cubed<std::deci>>(static_cast<double>(v))};}
constexpr metre_cubed operator"" _millilitre ( long double v )  {return  metre_cubed {helper::rescaleTo1<ratio_cubed<std::centi>>(static_cast<double>(v))};}


}

//constexpr ampere example = ampere{milli(100.0)};

template<typename U> constexpr const char* unitSymbol();
template<> inline constexpr const char* unitSymbol<   u::metre>(){ return "m";}
template<> inline constexpr const char* unitSymbol<u::kilogram>(){ return "kg";}
template<> inline constexpr const char* unitSymbol<  u::second>(){ return "s";}
template<> inline constexpr const char* unitSymbol<  u::ampere>(){ return "A";}
template<> inline constexpr const char* unitSymbol<  u::kelvin>(){ return "K";}
template<> inline constexpr const char* unitSymbol<    u::mole>(){ return "mol";}
template<> inline constexpr const char* unitSymbol< u::candela>(){ return "cd";}
template<> inline constexpr const char* unitSymbol<     u::foo>(){ return "foo";}

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


//////////////////////////////end definitions///////////////////////////////////////////