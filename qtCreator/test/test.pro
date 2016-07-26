#-------------------------------------------------
#
# Project created by QtCreator 2016-07-23T06:01:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    worker.cpp \
    trajectory.cpp

HEADERS  += mainwindow.h \
    worker.h \
    trajectory.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++11
