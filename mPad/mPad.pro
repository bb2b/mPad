#-------------------------------------------------
#
# Project created by QtCreator 2017-11-30T15:35:38
#
#-------------------------------------------------

QT       += core gui axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mPad
TEMPLATE = app

INCLUDEPATH += $$PWD/poppler

win32: LIBS += -L$$PWD/poppler -llibpoppler
win32: LIBS += -L$$PWD/poppler -llibpoppler-qt5

SOURCES += main.cpp\
        mainwindow.cpp \
    notebar.cpp \
    whiteboard.cpp \
    global.cpp \
    screenshot.cpp \
    desktop_switch_bar.cpp \
    whiteboard_switch_button.cpp \
    mylabel.cpp \
    settingpanel.cpp \
    localpanel.cpp \
    usbpanel.cpp \
    file_manage_window.cpp \
    file_manage_popup.cpp \
    file.cpp \
    udiskdetect.cpp \
    explorerwindow.cpp \
    pdfutils.cpp \
    picturewindow.cpp \
    moviewindow.cpp

HEADERS  += mainwindow.h \
    whiteboard.h \
    global.h \
    screenshot.h \
    desktop_switch_bar.h \
    whiteboard_switch_button.h \
    mylabel.h \
    notebar.h \
    settingpanel.h \
    localpanel.h \
    usbpanel.h \
    file_manage_window.h \
    file_manage_popup.h \
    file.h \
    udiskdetect.h \
    explorerwindow.h \
    pdfutils.h \
    picturewindow.h \
    moviewindow.h

FORMS    +=

RESOURCES += \
    res.qrc
