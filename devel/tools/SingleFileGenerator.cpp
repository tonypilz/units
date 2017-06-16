#include "SingleFileGenerator.h"

//1. enable defines
//2. compile with #QMAKE_CXXFLAGS += -E
//3. open SingleFileGenerator.o with notepad
//4. search for "Units\\" to find the starting point
//5. copy "Units\\" code to SingleFile.h
//6. remove "#.+"
//7. replace "\r\n +\r\n" -> "\r\n\r\n"
//7. remove "\}(\r\n)+namespace unit \{\r\n" in notepad


//#define _GLIBCXX_RATIO 1
//#define _GLIBCXX_CTGMATH 1
//#define _GLIBCXX_TYPE_TRAITS 1
//#define _GLIBCXX_IOSTREAM 1
//#define _GLIBCXX_SSTREAM 1
//#define _GLIBCXX_STRING	1



#include <src/quantity/quantityReading.h>
#include <src/quantity/quantityPrinting.h>
#include <src/quantity/quantityOperators.h>
#include <src/quantity/quantityDefinitions.h>




SingleFileGenerator::SingleFileGenerator()
{

}
