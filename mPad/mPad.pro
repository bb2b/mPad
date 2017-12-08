#-------------------------------------------------
#
# Project created by QtCreator 2017-11-30T15:35:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mPad
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    panel.cpp \
    notebar.cpp \
    whiteboard.cpp \
    switchboard.cpp \
    global.cpp \
    xwidget.cpp \
    screenshot.cpp

HEADERS  += mainwindow.h \
    panel.h \
    notebar.h \
    whiteboard.h \
    switchboard.h \
    global.h \
    xwidget.h \
    screenshot.h

FORMS    += mainwindow.ui \
    panel.ui \
    notebar.ui \
    switchboard.ui
