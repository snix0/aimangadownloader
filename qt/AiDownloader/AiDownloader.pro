#-------------------------------------------------
#
# Project created by QtCreator 2015-03-23T13:07:35
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AiDownloader
TEMPLATE = app


SOURCES += main.cpp\
        aidownloader.cpp \
    ../../src/curlpprequest.cpp \
    ../../src/parser.cpp

HEADERS  += aidownloader.h \
    ../../src/AiDownloader/curlpprequest.hpp \
    ../../src/curlpprequest.hpp \
    ../../src/parser.hpp

FORMS    += aidownloader.ui

CONFIG += link_pkgconfig c++11
PKGCONFIG += libxml++-2.6 curlpp glibmm-2.4
QT_CONFIG -= no-pkg-config
