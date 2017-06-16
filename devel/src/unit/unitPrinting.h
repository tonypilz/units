#pragma once

#include "unitHelper1.h"
#include <ostream>

namespace unit {

    template<typename U>
    constexpr const char* unitSymbol();

namespace  helper{

    template<typename U, DimensionIndex pos>
    void print_dimension_symbol_and_exponent(std::ostream& s)
    {
        static constexpr TExponent e = helper::exponent<U,pos>();
        if (e==0) return;
        s << unitSymbol<typename BaseUnitGen<U::exponent_count()-1,pos>::type>();
        if (e!=1) {
            s << "^" << e;
        }
    }



    template<typename U, DimensionIndex pos>
    struct DimensionsPrinter {
        static void print_unit(std::ostream& s){
              DimensionsPrinter<U,pos-1>::print_unit(s);
              print_dimension_symbol_and_exponent<U,pos>(s);
        }

    };

    template<typename U>
    struct DimensionsPrinter<U,0> {
        static void print_unit(std::ostream& s){
            print_dimension_symbol_and_exponent<U,0>(s);
        }
    };

}


/**
 * generic unit printing, can be spezialized for custom unit symbols
 *
 * eg prints
 *
 * - "m^10kg^11s^12A^13K^14mol^-15cd^16"
 *     for calling print_unit<Unit<10,11,12,13,14,-15,16>>(cout)
 * - "mkg"
 *     for calling print_unit<Unit<1,1,0,0,0,0,0>>(cout);
 */
template<typename U>
void print_unit(std::ostream& s){
    helper::DimensionsPrinter<U,U::exponent_count()-1>::print_unit(s);
}



}

