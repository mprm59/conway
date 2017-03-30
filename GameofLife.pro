QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RC_FILE = myapp.rc

TARGET = GameofLife
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    game.cpp

HEADERS  += mainwindow.h \
    game.h

FORMS    += mainwindow.ui

DISTFILES += \
    myappico.ico \
    myapp.rc \
    wt.png

RESOURCES += \
    images.qrc
