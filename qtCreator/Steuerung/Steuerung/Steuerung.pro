#-------------------------------------------------
#
# Project created by QtCreator 2016-07-26T11:19:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Steuerung
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    worker.cpp \
    trajectory.cpp

HEADERS  += mainwindow.h \
    worker.h \
    shrd_mem.h \
    trajectory.h

FORMS    += mainwindow.ui
