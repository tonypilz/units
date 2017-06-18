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
- [Latest Release - v1.1.0](#latest-release---v110)
  - [Tested on](#tested-on)
  - [Compiles Under](#compiles-under)
- [Contents](#contents)
- [Motivation](#motivation)
- [Features](#features)
- [Limitations](#limitations)
- [Getting Started Guide](#getting-started-guide)
- [Adding a new Math Function](#adding-a-new-math-munction)
- [Representation in non-base-units](#representation-in-non-base-units)
- [Adjusting the Library](#adjusting-the-library)
- [Under the Hood](#under-the-hood)


# Description

The library allows to track the dimensions of physical quantities at compile-time which enforces the the rules of dimension algebra with no runtime overhead. Additionally, the library provides some convenient conversions between different units of mesaure. And having the dimension attached to a value also makes stating the intent easier.

## Motivation
There exist quite a few other implementations for dimensional tracking eg. [Boost.Unit](http://www.boost.org/doc/libs/1_64_0/doc/html/boost_units.html), [nholthaus/units](https://github.com/nholthaus/units) or [martinmoene/PhysUnits-CT-Cpp11](https://github.com/martinmoene/PhysUnits-CT-Cpp11)(a more comprehensive list can be found at [PhysUnit-CT-Cpp11](https://github.com/martinmoene/PhysUnits-CT-Cpp11#other-libraries). All these implementations consist of a considerable amount of code (boost >4000 sloc, nholt/unit 3800 sloc, PysUnit 2500 sloc) and that they make strong use of macros. This makes understanding the code and adjusting it for special needs a time intensive task.

This library tries to adress the issue by beeing small (500 sloc*) and simple to allow users understand the code and adjust it to their needs more easily.  

Note that 500 sloc includes SI-Unit-Definitions an input/output. The [essential code without input/output and predefined units](https://github.com/tonypilz/units/blob/master/devel/tools/SingleFileMinimalExample.h) consists of 250sloc.

# Features
This library can be used for
 - dimensional analysis on unrestricted value types (double, int, complex ...)
 - printing dimensioned values
 - reading dimensioned values
 - easy extension to special needs
 
 The library is well tested and incurs no runtime overhead.  
 
# Limitations
Storing values in non-base-units (e.g. millisecs) cannot be done with this library (see [Representation in non-base-units](#representation-in-non-base-units)). 

Also printing and reading is rather simple and in terms of baseunits, so eg
```cpp
cout<<3.0_milliNewton; // prints "0.003N"
```
More advanced printing can be added if reqired.
 
# Getting Started Guide
The library consists of a single file ([units.h](include/units.h)), plus tests. To incorporate the library into your project, simply copy the header into a location in your include path.

Add `units.h` to your project, along with the `using` directive for literals which allows for a first simple example.

```cpp
#include <units.h>

int main() {

    using namespace unit;
    using namespace unit::literals;


    newton force = 2.0_metre * 3.0_kilogram / math::square(2.0_second);

    std::cout<<force<<"\n"; //prints "1.5N"
    
    return 0;
}
```

The quantity variable `force` is composed of a double having the value = `1.5` and a type beeing `newton`. As seen in this example, quantities can be used like doubles, an they should be used anywhere double values can be used.

To avoid mistakes, the variable `force` cannot be combined with pure doubles:

```cpp
force = force + 2.0; // compile error
force = force + 2.0_newton; // ok
``` 
Also, `force` can only be combined with compatible units according to the rules of dimensional analysis

```cpp
force = force + 2.0_second; // compile error due to summing different units 
force = force * 2.0_newton; // compile error due to return type mismatch 
                            // return type is `newton^2`, which cannot be assigned to type 'newton'
newton_squared force2 = force * 2.0_newton; // ok
```

Note that `newton_squared` is currently not defined in the library, but [can be easily added](#defining-new-units) if desired.

Due to the dimensional checking, `auto` can savely be used, errors will be caught at compile-time

```cpp
auto a = 2.0_metre;
auto b = 3.0_metre; 
auto c = math::sqr(a*a + b*b);  // pytagoras intended

auto force1 = c * 3.0_kilogram / math::square(2.0_second);
auto force2 = 5.0_newton;

force1 += force2; // compile error since force1 is of different type m*N
                  // since we forgot a 't' in 'sqr' making c of type meter^2  
```

The library provides some math functions (from <cmath>) which provide the respective unit transformations. If a math function is missing it can be [easily added](#adding-a-new-math-function) if desired.

Converting units is also possible:

```cpp
auto m = 2.0_pound; //m == 0,907185 meters
auto k = 0.0_celsius; // k == 273.15 kevlin
second s{ milli(5.0) }; // s == 0.005 seconds
```

If a conversion is missing it can be [easily added](#adding-a-new-math-function) if desired. Note that all units are always converted to their base-units. This default behaviour [can be changed](#representation-in-non-base-units).

Sometimes there is the need to combine a unit with a unitless scalar:

```cpp
double s = sin(45);
auto a = 2.0_metre; 
auto c = a * unitless{s};
```

For a fallback there is always to the option to extract the double value from the unit:

```cpp
auto a = 2.0_metre; 
double v = a.magnitude();
```


# Defining New Units

Units can be defined anywhere. The existing definitions can be found in namespace, just search for `namespace u` in [units.h](https://github.com/tonypilz/units/blob/master/include/units.h) to find examples.

```cpp
using newton_squared = Quantity<sqare_unit<u::newton>>;
```

# Adding a new Math Function

Math functions can be added anywhere. The existing math functions can be found in the namespace math, just search for `sqrt` in [units.h](https://github.com/tonypilz/units/blob/master/include/units.h) to find examples.

# Representation in non-base-units

The representation in non-base-units can be achived by defining a type which remembers its scale and behaves accordingly under aritmetic operations. Such a type is not part of the library.

Note: One should be aware that this form of lazy rescaling might incur runtime overhead since rescaling has to happen each time two values with a different scale are combined.

One should also keep in mind that floating point types like double are especially designed for keeping track of their initial scale. So there should rarely be the need for lazy rescaling. 

# Adjusting the Library

The library can adjusted to special needs by adjusting the lower part of [units.h](https://github.com/tonypilz/units/blob/master/include/units.h). The section to change starts with `namespace u` wich can be searched for. Everything below this line can be changed to meet special needs. In case of questions the [next chapter](#under-the-hood) might be of use.

# Under the Hood

The library consists essentially of 2 classes

```cpp

template< int ... dimensionExponents > struct Unit{};

template <typename Unit, typename MagnitudeRepresentation = double>
class Quantity {

    MagnitudeRepresentation m_magnitude;
};
```

The class `Quanitity` combines a magnitude-value and a unit-type. The class `unit` is a pure type wich is different for each pyhsical dimension by storing the exponents of all possible base-units as its template parameter. The following example illustrates the idea:

```cpp
using metre    = Unit<1,0,0>;  // represents the factors m^1 * kg^0 * s^0
using kilogram = Unit<0,1,0>;  // represents the factors m^0 * kg^1 * s^0
using second   = Unit<0,0,1>;  // represents the factors m^0 * kg^0 * s^1

using meters_per_second = Unit<1,0,-1>  // m^1 * kg^0 * s^-1
using acceleration = Unit<1,0,-2>       // m^1 * kg^0 * s^-2

using newton_force = Unit<1,1,-2>              // m^1 * kg^1 * s^-2
};
```

A Quantity of 5 newton would thus be defined as 

```cpp
Quantity< Unit<1,1,-2>, double > q{5};
```

or

```cpp
Quantity< newton_force > q{5};
```

Note that the definitions `metre`, `kilogram` and `second` are arbitraritly chosen and can be changed as well as the amount of units.

The rest of the library code past those 2 classes deals mainly with supporting them wich means improving their usage:
 - deriving units from operators eg `Unit<1,0,0> * Unit<0,0,1>` -> `Unit<1,0,1>`
 - deriving units from math functions eg `sqrt< Unit<6,0,0> >()` -> `Unit<3,0,0>`
 - printing units eg `print_unit< Unit<0,2,0> >();` -> prints `kg^2`
 - providing operators and math for class Quantity
 - convenicence stuff

