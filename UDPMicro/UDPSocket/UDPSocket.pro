QT += core
QT += network
QT -= gui

TARGET = UDPSocket
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    udp.cpp

HEADERS += \
    udp.h

