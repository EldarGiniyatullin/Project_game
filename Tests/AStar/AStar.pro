#-------------------------------------------------
#
# Project created by QtCreator 2014-11-23T22:59:01
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AStar
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    astar.cpp \
    astarpoint.cpp

HEADERS  += widget.h \
    project_objects.h \
    astar.h \
    astarpoint.h

FORMS    += widget.ui
