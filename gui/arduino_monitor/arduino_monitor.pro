#-------------------------------------------------
#
# Project created by QtCreator 2016-03-14T06:55:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = arduino_monitor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    console.cpp \
    communicator.cpp \
    parser.cpp \
    communicatorparser.cpp

HEADERS  += mainwindow.h \
    console.h \
    communicator.h \
    parser.h \
    communicatorparser.h
