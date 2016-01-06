#-------------------------------------------------
#
# Project created by QtCreator 2016-01-05T17:50:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DSIProject
TEMPLATE = app


SOURCES += main.cpp\
        gui.cpp \
    Conversor.cpp \
    Planta.cpp \
    Regulador.cpp \
    Sensor.cpp \
    VComp.cpp \
    FDT.cpp \
    vcomptabla.cpp

HEADERS  += gui.h \
    Conversor.h \
    Planta.h \
    Regulador.h \
    Sensor.h \
    VComp.h \
    FDT.h \
    vcomptabla.h

FORMS    += gui.ui
