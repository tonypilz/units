include($$PWD/pysConstsantsGeneration/pysConstsantsGeneration.pri)

SOURCES +=  \
    $$PWD/SingleFileGenerator.cpp \
    $$PWD/SingleFileTester.cpp

HEADERS += \
    $$PWD/SingleFileGenerator.h \
    $$PWD/SingleFileTester.h \
    $$PWD/SingleFileMinimalExample.h \
    $$PWD/SingleFileSi.h
