// Example program

#include "tmp.cpp"
#include "tests/TestMain.h"
#include "tools/SingleFileTester.h"

#include <tools/pysConstsantsGeneration/NistConstantsGenerator.h>

int main()
{
    //NistConstantsGenerator{};

    tests::TestMain{};
    tmp::run();

    SingleFileTester{};

    std::cout<<__FILE__<<" finished\n";

    return 0;
}

