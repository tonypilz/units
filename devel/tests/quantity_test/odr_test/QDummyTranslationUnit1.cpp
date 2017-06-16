#include "QDummyTranslationUnit1.h"

#include "QuantityHeaders.h"
#include <iostream>

namespace tests {
namespace q {
QDummyTranslationUnit1::QDummyTranslationUnit1()
{
    using namespace unit;
    std::cout<< newton{124.0} << "\n";
}

}
}
