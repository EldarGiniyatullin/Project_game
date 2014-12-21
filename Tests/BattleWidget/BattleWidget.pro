#-------------------------------------------------
#
# Project created by QtCreator 2014-12-21T03:47:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BattleWidget
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    personage.cpp

HEADERS  += widget.h \
    personage.h \
    map_object.h \
    surface_object.h \
    pixmap_item.h

FORMS    += widget.ui
