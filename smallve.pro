#-------------------------------------------------
#
# Project created by QtCreator 2014-01-30T16:49:13
#
#-------------------------------------------------

QT       -= core gui
CONFIG 	-= qt

TARGET = smallve
TEMPLATE = lib

CONFIG += link_pkconfig
PKGCONFIG += opencv

DEFINES += SMALLVE_LIBRARY

SOURCES += \
    src/smallve.cpp

HEADERS += \
    include/smallve.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
