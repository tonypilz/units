#include "QDummyTranslationUnit2.h"
#include "QuantityHeaders.h"
#include <iostream>

namespace tests {
namespace q {
QDummyTranslationUnit2::QDummyTranslationUnit2()
{
    using namespace unit::literals;
    std::cout<< 123.0_newton << "\n";
}

}
}
