#-------------------------------------------------
#
# Project created by QtCreator 2016-01-05T17:50:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

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
    graf.cpp \
    qcustomplot.cpp \
    vcomptabla.cpp \
    RegistroControl.cpp

HEADERS  += gui.h \
    Conversor.h \
    Planta.h \
    Regulador.h \
    Sensor.h \
    VComp.h \
    FDT.h \
    graf.h \
    qcustomplot.h \
    vcomptabla.h \
    RegistroControl.h

FORMS    += gui.ui
