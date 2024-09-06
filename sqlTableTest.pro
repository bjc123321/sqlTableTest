#-------------------------------------------------
#
# Project created by QtCreator 2024-09-02T14:31:07
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sqlTableTest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    databasemanager.cpp

HEADERS  += mainwindow.h \
    databasemanager.h

FORMS    += mainwindow.ui
