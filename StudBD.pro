#-------------------------------------------------
#
# Project created by QtCreator 2014-08-03T17:15:22
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StudBD
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    loginform.cpp \
    registerform.cpp \
    addstudentform.cpp

HEADERS  += mainwindow.h \
    loginform.h \
    registerform.h \
    addstudentform.h

FORMS    += mainwindow.ui \
    loginform.ui \
    registerform.ui \
    addstudentform.ui
