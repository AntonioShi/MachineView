TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

CONFIG -= no-pkg-config
CONFIG += link_pkgconfig
PKGCONFIG += opencv

INCLUDEPATH += /usr/local/include

LIBS +=

SOURCES += main.cpp
