#-------------------------------------------------
#
# Project created by QtCreator 2014-12-02T19:23:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Map_2
TEMPLATE = app
CONFIG += c++11


SOURCES += main.cpp \
    mapfacade.cpp

HEADERS  += \
    map_object.h \
    graphics_scene.h \
    surface_object.h \
    mapfacade.h \
    pixmap_item.h \
    surface_map.h \
    personage.h \
    prop_object.h \
    prop_map.h

FORMS    += \
    mapfacade.ui

RESOURCES += \
    resources.qrc
