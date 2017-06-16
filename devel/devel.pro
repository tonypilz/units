TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

#QMAKE_CXXFLAGS += -E

include($$PWD/src/src.pri)
include($$PWD/tests/tests.pri)
include($$PWD/tools/tools.pri)

SOURCES += \
    main.cpp \
    tmp.cpp

HEADERS += \

