#-------------------------------------------------
#
# Project created by QtCreator 2014-11-23T21:06:12
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SaverTest
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    saver.cpp

HEADERS  += widget.h \
    project_objects.h \
    saver.h

FORMS    += widget.ui
