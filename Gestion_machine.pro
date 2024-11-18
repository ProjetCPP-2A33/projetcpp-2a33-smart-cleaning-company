QT       += core gui sql

QT += core gui printsupport
QT += charts sql
QT += core gui sql printsupport charts network serialport
QT += charts

QT += core gui charts
QT += printsupport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    connection.cpp \
    machine.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    connection.h \
    machine.h \
    mainwindow.h

FORMS += \
    mainwindow.ui
