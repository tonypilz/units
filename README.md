# units
A lightweight, compile-time, header-only, dimensional analysis and unit conversion library built on c++11 with no dependencies.

# Latest Release - v1.0.0

Initial release.

## Tested on
 - gcc-5.3.0

## Compiles Under
 - icc-16 + 17
 - gcc-7 .. gcc-4.7
 - clang 4.0 .. clang 3.4
 
# Contents
- [UNITS](#units)
- [Latest Release - v1.1.0](#latest-release---v100)
  - [Tested on](#tested-on)
  - [Compiles Under](#compiles-under)
- [Contents](#contents)
- [Description](#description)
- [Motivation](#motivation)
- [Features](#features)
- [Limitations](#limitations)
- [Getting Started Guide](#getting-started-guide)
- [Adding a new Math Function](#adding-a-new-math-function)
- [Representation in non-base-units](#representation-in-non-base-units)
- [Adjusting the Library](#adjusting-the-library)
- [Under the Hood](#under-the-hood)


# Description

The library allows to track the dimensions of physical quantities at compile-time which enforces the the rules of dimension algebra with no runtime overhead. Additionally, the library provides some convenient conversions between different units of mesaure.

## Motivation
There exist quite a few other implementations for dimensional tracking eg. [Boost.Unit](http://www.boost.org/doc/libs/1_64_0/doc/html/boost_units.html), [nholthaus/units](https://github.com/nholthaus/units) or [martinmoene/PhysUnits-CT-Cpp11](https://github.com/martinmoene/PhysUnits-CT-Cpp11). A more comprehensive list can be found at [PhysUnit-CT-Cpp11](https://github.com/martinmoene/PhysUnits-CT-Cpp11#other-libraries). All these implementations consist of a considerable amount of code (boost >4000 sloc, nholt/unit 3800 sloc, PysUnit 2500 sloc) and that they make strong use of macros. This makes understanding the code and adjusting it for special needs a time intensive task.

This library tries to adress the issue by beeing small (500 sloc*) and simple to allow users understand the code and adjust it to their needs more easily.  

*Note that 500 sloc includes SI-Unit-Definitions an input/output and excludes [physicalConstants.h](include/physicalConstants.h). The [essential code without input/output and predefined units](https://github.com/tonypilz/units/blob/master/devel/tools/SingleFileMinimalExample.h) consists of 250sloc.

# Features
The library can be used for
 - dimensional analysis on unrestricted value-types (double, int, complex ...)
 - printing dimensioned values
 - reading dimensioned values
 - convert units of measure
 
It is designed to be extendable to special needs. Its mostly constexpr, well tested and incurs no runtime overhead (at optimization -O1). All constants from [nist](http://physics.nist.gov/cuu/Constants/Table/allascii.txt) are available (see [physicalConstants.h](include/physicalConstants.h)).
 
# Limitations
Storing values in non-base-units (e.g. millisecs) cannot be done with this library (see [Representation in non-base-units](#representation-in-non-base-units)). 

Therefore printing and reading is done in terms of baseunits, so eg
```cpp
cout << 3.0_n * milli(newton); // prints "0.003N"
```
More advanced printing and reading can be added if reqired.
 
# Getting Started Guide
The library consists of a single file ([units.h](include/units.h)). To incorporate the library into your project, simply copy the header into a location in your include path.

Add `units.h` to your project, along with the `using` directive for literals which allows for a first simple example.

```cpp
#include <units.h>

int main() {

    using namespace unit;
    using namespace unit::literals;


    t::newton some_force = 2.0_n*meter * 3.0_n*kilogram / math::square(2.0_n*second);

    std::cout<<some_force<<"\n"; //prints "1.5N"
    
    return 0;
}
```

The variable `some_force` is a double value of `1.5` having a unit type `newton` attached to it. Quantities like `some_force` can be used like doubles, an they should be used anywhere double values can be used.

To avoid mistakes, the variable `some_force` cannot be combined with pure doubles:

```cpp
some_force = some_force + 2.0;            // compile error
some_force = some_force + 2.0_n*newton; // ok
``` 
Also, `some_force` can only be combined with compatible units according to the rules of dimensional analysis

```cpp
some_force = some_force + 2.0_n*second; // compile error due to summing different units 
some_force = some_force * 2.0_n*newton; // compile error due to return type mismatch 
                            // return type is `newton^2`, which cannot be assigned to type 'newton'
newton_squared some_force2 = some_force * 2.0_n*newton; // ok
```

Note that `newton_squared` is currently not defined in the library, but [can be easily added](#defining-new-units) if desired.

Due to the dimensional checking, `auto` can savely be used, errors will be caught at compile-time

```cpp
auto a = 2.0_n*meter;
auto b = 3.0_n*meter; 
auto c = math::sqr(a*a + b*b);  // pytagoras intended

auto force1 = c * 3.0_n*kilogram / math::square(2.0_n*second);
auto force2 = 5.0_n*newton;

force1 += force2; // compile error since force1 is of different type m*N
                  // since we forgot a 't' in 'sqr' making c of type meter^2  
```

The library provides some math functions (from <cmath>) which provide the respective unit transformations. If a math function is missing it can be [easily added](#adding-a-new-math-function) if desired.

Converting to base units is also possible:

```cpp
auto m = 2.0_n*pound; //m == 0,907185 meters
auto f = cube( 500.0_n * deci(inch) ); //f == 2.04838 m^3
auto k = celsius(0); // k == 273.15 kevlin
auto s = 5.0_n*milli(second); // s == 0.005 seconds
```

If a conversion is missing it can be [easily added](#adding-a-new-math-function) if desired. Note that all units are always converted to their base-units. This default behaviour [can be changed](#representation-in-non-base-units).

Sometimes there is the need to combine a unit with a unitless scalar:

```cpp
double s = sin(45);
auto a = 2.0_n*meter; 
auto c = a * number{s};
```

For a fallback there is always to the option to extract the double value from the unit:

```cpp
auto a = 2.0_n*meter; 
double v = a.magnitude();
```


# Defining New Units

Units can be defined anywhere. The existing definitions can be found in namespace u in [units.h](https://github.com/tonypilz/units/blob/master/include/units.h), just search there for `namespace u` to find example definitions.

# Adding a new Math Function

Math functions can be added anywhere. The existing math functions can be found in the namespace math in [units.h](https://github.com/tonypilz/units/blob/master/include/units.h), just search there for `sqrt` to find examples.

# Representation in non-base-units

The representation in non-base-units can be achived by using the type [ScaledValue](https://github.com/tonypilz/ScaledValue) as magnitude-type. This type remembers its scale and behaves accordingly under aritmetic operations. The following example illustrates the usage:

```cpp
#include <units.h>
#include <ScaledValue.h>

using namespace unit;
using namespace sv;

using SvMilli = ScaledValue<std::milli,double>;
using SvKilo = ScaledValue<std::kilo,double>;
using Sv1 = ScaledValue<std::ratio<1>,double>;

constexpr Quantity<u::newton,Sv1> s_newton {1.0};
constexpr Quantity<u::unitless,Sv1> s_unitLess{1.0};

constexpr Quantity<u::unitless,SvKilo> operator"" _kilo ( long double v )  {return Quantity<u::unitless,SvKilo> {static_cast<double>(v)};}
constexpr Quantity<u::unitless,SvMilli> operator"" _milli ( long double v )  {return Quantity<u::unitless,SvMilli> {static_cast<double>(v)};}

int main() {


    using namespace unit;
    using namespace sv;

    //define unit values on different scales
    auto a = 2.0_kilo * s_newton;
    auto b = 500.0_milli * s_newton;

    //combination
    auto c = a + b;
    auto d = a * b;

    //conversion
    auto e = Quantity<u::newton,Sv1>{b};

    //printing
    std::cout << a << std::endl; // prints "2*kiloN"
    std::cout << b << std::endl; // prints "500*milliN"
    std::cout << c << std::endl; // prints "2.0005*kiloN"
    std::cout << d << std::endl; // prints "1*kilom^2kg^2s^-4" (which is 1*kilo N^2)
    std::cout << e << std::endl; // prints "0.5N"
    
    return 0;
}
```
The definitions above `main` improve the usability. They are similar to the ones in [units.h](https://github.com/tonypilz/units/blob/master/include/units.h). So to make efficient use of scaled units one should update the definitions in [units.h](https://github.com/tonypilz/units/blob/master/include/units.h). Also be aware that the math functions need to be updated too due to current adl lookup issues. 

Note: One should be aware that this form of delayed rescaling might incur runtime overhead since rescaling has to happen each time two values with different scales are combined.

One should also keep in mind that floating point types like double are especially good at keeping track of their scale. So there should rarely be the need for this form of customization. 

# Adjusting the Library

The library is specially designed to be adjusted to special needs. It can be done by changing the lower part of the [units.h](https://github.com/tonypilz/units/blob/master/include/units.h) file, which begins at `namespace u` (which can be searched for). Everything below `namespace u` be changed to meet special needs. In case of questions the [next chapter](#under-the-hood) might be of use.

# Under the Hood

The library essentially consists of 2 classes

```cpp

template< int ... dimensionExponents > 
struct Unit{};

template <typename Unit, typename MagnitudeRepresentation = double>
class Quantity {

    MagnitudeRepresentation m_magnitude;
};
```

The class `Quanitity` combines a magnitude-value and a unit-type. The class `unit` is a pure type wich is different for each physical dimension by storing the exponents of all possible base-units in its template parameter. The following example illustrates the idea of units:

```cpp
using metre    = Unit<1,0,0>;  // represents m^1 * kg^0 * s^0
using kilogram = Unit<0,1,0>;  //            m^0 * kg^1 * s^0
using second   = Unit<0,0,1>;  //            m^0 * kg^0 * s^1

using meters_per_second = Unit<1,0,-1> //  m^1 * kg^0 * s^-1
using acceleration = Unit<1,0,-2>      //  m^1 * kg^0 * s^-2

using newton_force = Unit<1,1,-2>       // m^1 * kg^1 * s^-2
};
```

With these definitions a value of 5 newton would therefore be defined as 

```cpp
Quantity< Unit<1,1,-2>, double > q{5};
```

or

```cpp
Quantity< newton_force, double > q{5};
```

Note that the definitions `metre`, `kilogram` and `second` are arbitraritly chosen and can be changed as well as their count.

The remaining library code past those 2 classes deals mainly with supporting them:
 - deriving return unit-types for operators eg `Unit<1,0,0> * Unit<0,0,1>` -> `Unit<1,0,1>`
 - deriving return unit-types for math functions eg `sqrt< Unit<6,0,0> >()` -> `Unit<3,0,0>`
 - printing units eg `print_unit< Unit<0,2,0> >();` -> prints `kg^2`
 - providing operators and math for class `Quantity`
 - conversions between units and scales

Further information can be found in the file [units.h](https://github.com/tonypilz/units/blob/master/include/units.h).

