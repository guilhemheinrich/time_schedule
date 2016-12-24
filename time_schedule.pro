QT += core
QT -= gui

CONFIG += c++11

TARGET = time_schedule
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    class.cpp \
    room.cpp \
    teacher.cpp \
    slot.cpp \
    schedule.cpp \
    solution.cpp \
    problem.cpp

HEADERS += \
    class.h \
    room.h \
    teacher.h \
    slot.h \
    schedule.h \
    solution.h \
    problem.h
