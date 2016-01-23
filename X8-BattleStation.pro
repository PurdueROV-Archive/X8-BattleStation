TEMPLATE = app

QT += core qml quick

SOURCES += main.cpp \
    mainthread.cpp \
    input/inputHandler.cpp


RESOURCES += qml.qrc

CONFIG += c++11

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    mainthread.h \
    input/inputHandler.h

win32{
    INCLUDEPATH += $$PWD/input/SDL/include
    DEPENDPATH += $$PWD/input/SDL/include
    LIBS += -L$$PWD/input/SDL/lib/x86/ -lSDL2
    #will do the fancy stuff you guys did in Cerulean-BattleStation after I get this working first
}

linux-g++ {
    LIBS += -L$$PWD/input/SDL/lib/x64/ -lSDL2
    INCLUDEPATH += $$PWD/input/SDL/include
    DEPENDPATH += $$PWD/input/SDL/include
}
