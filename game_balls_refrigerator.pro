#-------------------------------------------------
#
# Project created by QtCreator 2016-01-19T14:52:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = game_balls_refrigerator
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
    grip_widget.cpp \
    main_window.cpp \
    lock_widget.cpp \
    game_controller.cpp

HEADERS  += \
    grip_widget.h \
    main_window.h \
    lock_widget.h \
    game_controller.h
