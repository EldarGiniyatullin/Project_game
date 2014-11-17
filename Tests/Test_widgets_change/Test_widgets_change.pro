#-------------------------------------------------
#
# Project created by QtCreator 2014-11-16T13:55:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Test_widgets_change
TEMPLATE = app


SOURCES += main.cpp\
    main_menu_widget.cpp \
    common_window.cpp \
    create_game_widget.cpp

HEADERS  += \
    create_game_widget.h \
    main_menu_widget.h \
    common_widget.h \
    common_menu_resources.h \
    characters.h \
    field_objects.h

FORMS    += window.ui

RESOURCES += \
    resources.qrc
