QT -= gui
CONFIG *= c++11
CONFIG *= console
include(../../gtimediff.pri)
DEFINES *= GTEST
SOURCES += *.cpp
DESTDIR = $${PWD}/../../bin
linux: LIBS *= -lgtest_main -lgtest
