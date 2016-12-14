#-------------------------------------------------
#
# Project created by QtCreator 2016-11-15T11:15:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CH
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    sortbyyasc.cpp \
    sortbyxasc.cpp \
    algorithms.cpp \
    draw.cpp

HEADERS  += widget.h \
    sortbyyasc.h \
    sortbyxasc.h \
    algorithms.h \
    draw.h

FORMS    += widget.ui
