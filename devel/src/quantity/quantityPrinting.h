#pragma once

#include "Quantity.h"
#include <src/unit/unitPrinting.h>

namespace unit {



template<typename Unit, typename TValue>
std::ostream& operator<<(std::ostream& s, Quantity<Unit,TValue> const& v){
    s << v.magnitude();
    print_unit<Unit>(s);
    return s;
}

}
