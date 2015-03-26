#-------------------------------------------------
#
# Project created by QtCreator 2015-03-23T13:07:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AiDownloader
TEMPLATE = app


SOURCES += main.cpp\
        aidownloader.cpp \
    ../../src/AiDownloader/curlpprequest.cpp

HEADERS  += aidownloader.h \
    ../../src/AiDownloader/curlpprequest.hpp

FORMS    += aidownloader.ui

CONFIG += link_pkgconfig c++11
PKGCONFIG += libxml++-2.6 curlpp glibmm-2.4
QT_CONFIG -= no-pkg-config
