#-------------------------------------------------
#
# Project created by QtCreator 2013-08-29T10:46:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUIApp
TEMPLATE = app

CONFIG += console

SOURCES += main.cpp\
        mainwindow.cpp \
    thresholddialog.cpp \
    imageprocess.cpp \
    webcamdialog.cpp \
    faceclassifierdialog.cpp

HEADERS  += mainwindow.h \
    thresholddialog.h \
    imageprocess.h \
    webcamdialog.h \
    faceclassifierdialog.h

FORMS    += mainwindow.ui \
    thresholddialog.ui \
    webcamdialog.ui \
    faceclassifierdialog.ui

INCLUDEPATH += C://LibrariesQt//OpenCV//include

LIBS += C://LibrariesQt//OpenCV//bin//*.dll
