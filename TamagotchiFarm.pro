#-------------------------------------------------
#
# Project created by QtCreator 2015-05-25T19:43:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TamagotchiFarm
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Tamagotchi.cpp \
    Mensaje.cpp

HEADERS  += mainwindow.h \
    Tamagotchi.h \
    Nodo.h \
    Cola.h \
    Pila.h \
    Mensaje.h

FORMS    += mainwindow.ui
