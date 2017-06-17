# units
A minimal compile-time, header-only, dimensional analysis and unit conversion library built on c++11 with no dependencies.

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
- [Description](#description)
- [Target Users](#target-users)
- [Getting started guide](#getting-started-guide)

# Description

The library allows to track the dimensions of physical quantities at compile-time which enforces the the rules of dimension algebra with no runtime overhead. Additionally, the library provides some convenient conversions between different units of mesaure. And finally, having a specific type attached to each dimension makes reading code a lot easier.

## Target Users
There exist quite a few other implementations for dimensional tracking eg. [Boost.Unit](http://www.boost.org/doc/libs/1_64_0/doc/html/boost_units.html), [nholthaus/units](https://github.com/nholthaus/units) or [PhysUnit-CT-Cpp11](https://github.com/martinmoene/PhysUnits-CT-Cpp11). All these implementations have in common that they consist of quite a lot of code (boost >4000 sloc, nholt/unit 3800 sloc, PysUnit 2500 sloc) and that they make strong use of macros. This makes understanding the code and adjusting it for special needs a time intensive task.

This library tries to adress the issue by beeing as small (500 sloc) and simple (macro-free) as possible to allow users to reason faster about the code and adjust it to their needs more easily.  

# Getting started guide
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

The variable `force` is composed of a double having the value = `1.5` and a type beeing `newton`. As seen in this example, units can be used like doubles, an they should be used anywhere double values can be used.

To avoid mistakes, the variable `force` cannot be combined with pure doubles:

```cpp
// force = force + 2.0; -> compile error
force = force + 2.0_newton; // ok
``` 
Also, `force` can only be combined with compatible units according to the rules of dimensional analysis

```cpp
// force = force + 2.0_second; -> compile error, dimensional analysis doesnt allow for summing different units 
// force = force * 2.0_newton; -> compile error, return type is `newton^2`, which cannot be assigned to type 'newton'
newton_squared force2 = force * 2.0_newton; //ok
```

Note that `newton_squared` is currently not defined in the library, but [can be easily added](#defining-new-units).

Due to the dimensional checking, `auto` can savely be used, errors will be caught at compile-time

```cpp
auto a = 2.0_metre;
auto b = 3.0_metre; 
auto c = math::sqr(a*a + b*b);  //pytagoras

auto force1 = c * 3.0_kilogram / math::square(2.0_second);
auto force2 = 5.0_newton;

//force1 += force2; //compile error, force1 is of type m*N since we forgot a 't' in 'sqr' making c of type meter^2  
```

The library provides some math functions which provide the respective unit transformations. If a function is missing is can be [easily added](#adding-a-new-math-function).

Converting units is also possible:

```cpp
auto m = 2.0_pound; //m == 0,907185 meters
auto k = 0.0_celsius; // k == 273.15 kevlin
second s{ milli(5.0) }; // s == 0.005 seconds
```

If a conversion is missing it can be [easily added](#adding-a-new-math-function). Note that all units are always converted to their base-units. This default behaviour [can be changed](#representation-in-non-base-units).

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

```cpp
using newton_squared = Quantity<sqare_unit<u::newton>>;
```

# Adding a new Math Function



# Representation in non-base-units

The representation in non-base-units can be achived by defining a type which remembers its scale and behaves accordingly under aritmetic operations. Such a type is not part of the library.

Note: One should be aware that this form of lazy rescaling might incur runtime overhead since rescaling has to happen each time two values with a different scale are combined.

One should also keep in mind that floating point types like double are especially designed for keeping track of their initial scale. So there should rarely be the need for this scenario. 

