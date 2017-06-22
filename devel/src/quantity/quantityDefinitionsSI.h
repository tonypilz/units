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

namespace u {

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



namespace convert {

template<typename T> constexpr T celsiusToKelvin(T v ) { return static_cast<double>(v+273.15); }
template<typename T> constexpr T fahrenheitToKelvin(T v ) { return (v+459.67)*5.0/9.0; }

template<typename T> constexpr T feedTometer(T v ){ return static_cast<double>(v*0.3048); }
template<typename T> constexpr T mileTometer(T v ){ return static_cast<double>(v*1609.34); }
template<typename T> constexpr T yardTometer(T v ){ return static_cast<double>(v*0.9144); }

template<typename T> constexpr T poundToKilogram(T v ){ return static_cast<double>(v*0.45359237); }
template<typename T> constexpr T ounceToKilogram(T v ){ return static_cast<double>(v*0.0283495); }


template<typename T> constexpr T minuteTosecond(T v ){ return static_cast<double>(v*60.0); }
template<typename T> constexpr T hourTosecond(T v ){ return static_cast<double>(v*60.0*60.0); }
template<typename T> constexpr T dayTosecond(T v ){ return static_cast<double>(v*60.0*60.0*24); }

template<typename T> constexpr T calorieToJoules(T v ){ return static_cast<double>(v*4184.0); }
template<typename T> constexpr T watt_hourToJoules(T v ){ return static_cast<double>(v*3600.0); }

template<typename T> constexpr T litreToCubicmeter(T v ){ return static_cast<double>(v*0.001); }
template<typename T> constexpr T cubicCentimeterToCubicmeter(T v ){ return static_cast<double>(v*1.0e-6); }
template<typename T> constexpr T gallonsToCubicmeter(T v ){ return static_cast<double>(v*0.00378541); }

}


namespace mathConstant {

constexpr auto pi = unitless{3.141592653589793238462643383279502884};

}

//temperature
constexpr    kelvin     celsius ( double v ){ return kelvin {convert::celsiusToKelvin(v)};}
constexpr    kelvin  fahrenheit ( double v ){ return kelvin {convert::fahrenheitToKelvin(v)};}
//length
constexpr     meter        feed ( double v ){ return meter {convert::feedTometer(v)};}
constexpr     meter        mile ( double v ){ return meter {convert::mileTometer(v)};}
constexpr     meter        yard ( double v ){ return meter {convert::yardTometer(v)};}
//mass
constexpr  kilogram       pound ( double v ){ return kilogram {convert::poundToKilogram(v)};}
constexpr  kilogram       ounce ( double v ){ return kilogram {convert::ounceToKilogram(v)};}
constexpr kilogram         gram ( double v ){return  kilogram {helper::rescale<std::ratio<1>,std::kilo>(v)};} //special case mass since baseunit is prefixed with 'kilo'
//time
constexpr  second        minute ( double v ){ return second {convert::minuteTosecond(v)};}
constexpr  second          hour ( double v ){ return second {convert::hourTosecond(v)};}
constexpr  second           day ( double v ){ return second {convert::dayTosecond(v)};}
//energy
constexpr  joule        calorie ( double v ){ return joule {convert::calorieToJoules(v)};}
constexpr  joule      watt_hour ( double v ){ return joule {convert::watt_hourToJoules(v)};}
//volume
constexpr meter_cubed     litre ( double v ){return meter_cubed {convert::litreToCubicmeter(v)};}
constexpr meter_cubed   gallons ( double v ){return meter_cubed {convert::gallonsToCubicmeter(v)};}
//concentration
constexpr unitless  parts_per_million ( double v ){return  unitless {micro(v)};}
constexpr unitless            percent ( double v ){return  unitless {centi(v)};}


namespace literals {

//base units
constexpr   unitless operator"" _unitless ( long double v )  {return    unitless {static_cast<double>(v)};}
constexpr   unitless operator""   _number ( long double v )  {return    unitless {static_cast<double>(v)};}
constexpr   unitless operator""        _n ( long double v )  {return    unitless {static_cast<double>(v)};}

constexpr    meter operator""    _meter ( long double v )  {return     meter {static_cast<double>(v)};}
constexpr kilogram operator"" _kilogram ( long double v )  {return  kilogram {static_cast<double>(v)};}
constexpr   second operator""   _second ( long double v )  {return    second {static_cast<double>(v)};}
constexpr   ampere operator""   _ampere ( long double v )  {return    ampere {static_cast<double>(v)};}
constexpr   kelvin operator""   _kelvin ( long double v )  {return    kelvin {static_cast<double>(v)};}
constexpr     mole operator""     _mole ( long double v )  {return      mole {static_cast<double>(v)};}
constexpr  candela operator""  _candela ( long double v )  {return   candela {static_cast<double>(v)};}


//derived units
constexpr    radian operator""    _radian ( long double v )  {return     radian {static_cast<double>(v)};}
constexpr steradian operator"" _steradian ( long double v )  {return  steradian {static_cast<double>(v)};}
constexpr     hertz operator""     _hertz ( long double v )  {return      hertz {static_cast<double>(v)};}
constexpr    newton operator""    _newton ( long double v )  {return     newton {static_cast<double>(v)};}
constexpr    pascal operator""    _pascal_( long double v )  {return     pascal {static_cast<double>(v)};} // _pascal is reserved by clang
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

constexpr kelvin      operator"" _celsius ( long double v ){ return celsius (static_cast<double>(v));}
constexpr kelvin      operator"" _fahrenheit ( long double v ){ return fahrenheit (static_cast<double>(v));}
constexpr meter       operator"" _feed ( long double v ){ return feed (static_cast<double>(v));}
constexpr meter       operator"" _mile ( long double v ){ return mile (static_cast<double>(v));}
constexpr meter       operator"" _yard ( long double v ){ return yard (static_cast<double>(v));}
constexpr kilogram    operator"" _pound ( long double v ){ return pound (static_cast<double>(v));}
constexpr kilogram    operator"" _ounce ( long double v ){ return ounce (static_cast<double>(v));}
constexpr kilogram    operator"" _gram ( long double v ){ return gram (static_cast<double>(v));}
constexpr second      operator"" _minute ( long double v ){ return minute (static_cast<double>(v));}
constexpr second      operator"" _hour ( long double v ){ return hour (static_cast<double>(v));}
constexpr second      operator"" _day ( long double v ){ return day (static_cast<double>(v));}
constexpr joule       operator"" _calorie ( long double v ){ return calorie (static_cast<double>(v));}
constexpr joule       operator"" _watt_hour ( long double v ){ return watt_hour (static_cast<double>(v));}
constexpr meter_cubed operator"" _litre ( long double v ){ return litre (static_cast<double>(v));}
constexpr meter_cubed operator"" _gallons ( long double v ){ return gallons (static_cast<double>(v));}
constexpr unitless    operator"" _parts_per_million ( long double v ){ return parts_per_million (static_cast<double>(v));}
constexpr unitless    operator"" _percent ( long double v ){ return percent (static_cast<double>(v));}

}

//constexpr ampere example = ampere{milli(100.0)};

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

