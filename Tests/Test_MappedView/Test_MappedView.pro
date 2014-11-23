#-------------------------------------------------
#
# Project created by QtCreator 2014-11-22T18:24:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Test_MappedView
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        userview.cpp

HEADERS  += userview.h \
    graphicsscene.h

FORMS    += userview.ui

RESOURCES += \
    res.qrc
