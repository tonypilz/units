#include "TestMain.h"

#include "quantity_test/QuantityTestMain.h"
#include "unit_test/UnitTestMain.h"

namespace tests {

TestMain::TestMain()
{
    QuantityTestMain{};
    UnitTestMain{};
}

}
