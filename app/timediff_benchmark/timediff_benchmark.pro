QT -= gui
CONFIG *= c++11
CONFIG *= console
win32:LIBS += -lwinmm
SOURCES += *.cpp
DESTDIR = $${PWD}/../../bin
