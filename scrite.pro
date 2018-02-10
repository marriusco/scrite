#QT += core
QT -= gui

TARGET = scrite
CONFIG += console
CONFIG -= app_bundle
QMAKE_CXXFLAGS +=  -std=c++11
TEMPLATE = app

QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O0  -Wno-unused-parameter

QMAKE_CXXFLAGS_DEBUG -= -O2
QMAKE_CXXFLAGS_DEBUG += -O0  -Wno-unused-parameter
DEFINES += DEBUG

#DEFINES += SCRAT_NO_ERROR_CHECKING

INCLUDEPATH += sq/include
INCLUDEPATH += sq/squirrel
INCLUDEPATH += sq/sqrat/include
INCLUDEPATH += sq/sqrat
INCLUDEPATH += sq/sqrat/include/sqrat

SOURCES += main.cpp \
    sqwrap.cpp \
    demo.cpp

HEADERS += \
    main.h \
    sqwrap.h \
    demo.h \
    osthread.h



LIBS += -ldl -lpthread


DISTFILES += \

target.path = ./bin
INSTALLS += target




unix:!macx: LIBS += -L$$PWD/lib/ -lsquirrel

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

unix:!macx: PRE_TARGETDEPS += $$PWD/lib/libsquirrel.a

unix:!macx: LIBS += -L$$PWD/lib/ -lsqstdlib

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

unix:!macx: PRE_TARGETDEPS += $$PWD/lib/libsqstdlib.a
