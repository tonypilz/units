#pragma once

#include "Quantity.h"
#include <src/unit/unitReading.h>

#include <istream>

namespace unit {

template <typename Unit, typename TValue>
std::istream& operator>>(std::istream& s, Quantity<Unit, TValue>& v) {
    TValue val;
    s >> val;
    if (!s)
        return s;

    if (!read_unit<Unit>(s))
        return s;

     v = Quantity<Unit, TValue>{val};
    return s;
}
}
