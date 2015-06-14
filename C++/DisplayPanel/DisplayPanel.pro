#-------------------------------------------------
#
# Project created by QtCreator 2015-06-11T09:17:24
#
#-------------------------------------------------

QT       += core gui serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DisplayPanel
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    serialcommunication.cpp \
    weathersettings.cpp \
    inifunctions.cpp \
    downloadfile.cpp \
    fileparsing.cpp

HEADERS  += mainwindow.h \
    serialcommunication.h \
    weathersettings.h \
    inifunctions.h \
    downloadfile.h \
    fileparsing.h

FORMS    += mainwindow.ui \
    weathersettings.ui
