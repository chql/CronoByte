#-------------------------------------------------
#
# Project created by QtCreator 2015-09-07T14:03:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = CronoByte
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    processmanager.cpp

HEADERS  += mainwindow.h \
    processmanager.h

FORMS    += mainwindow.ui

Release: QMAKE_CXXFLAGS += -O2
