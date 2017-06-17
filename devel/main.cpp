// Example program

#include "tmp.cpp"
#include "tests/TestMain.h"
#include "tools/SingleFileTester.h"

int main()
{
    tests::TestMain{};
    //tmp::run();

    SingleFileTester{};

    std::cout<<__FILE__<<" finished\n";

    return 0;
}

