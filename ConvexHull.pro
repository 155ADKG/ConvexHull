#-------------------------------------------------
#
# Project created by QtCreator 2016-12-15T10:15:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ConvexHull
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    algorithms.cpp \
    sortbyxasc.cpp \
    sortbyyasc.cpp \
    draw.cpp \
    sortdouble.cpp \
    removeduplicatepoints.cpp

HEADERS  += widget.h \
    algorithms.h \
    sortbyxasc.h \
    sortbyyasc.h \
    draw.h \
    sortdouble.h \
    removeduplicatepoints.h \
    customtypes.h

FORMS    += widget.ui
