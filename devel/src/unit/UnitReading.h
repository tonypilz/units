#pragma once

#include "unitPrinting.h"
#include <iosfwd>
#include <sstream>
namespace unit {

template <typename Unit>
std::istream& read_unit(std::istream& s) {
    std::ostringstream expectedBuff;
    print_unit<Unit>(expectedBuff);

    for (auto const& expected : expectedBuff.str()) {
        char found;
        s >> found;
        if (!s || found != expected) {
            s.setstate(std::ios::failbit);
            return s;
        }
    }
    return s;
}
}
