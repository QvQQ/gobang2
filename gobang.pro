#-------------------------------------------------
#
# Project created by QtCreator 2018-02-02T01:10:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += object_parallel_to_source

TARGET = gobang
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    use.cpp \
    instance/chessboard.cpp \
    instance/chessman.cpp \
    struct/actor.cpp \
    struct/stage.cpp \
    struct/position.cpp \
    strategy/gobang2.c \
    strategy/playchess.cpp

HEADERS += \
    mainwindow.h \
    instance/chessboard.h \
    instance/chessman.h \
    struct/actor.h \
    struct/stage.h \
    struct/position.h \
    strategy/playchess.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    resource/res.qrc
