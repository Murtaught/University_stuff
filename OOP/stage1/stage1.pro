TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    point.cpp \
    pointset.cpp \
    color.cpp \
    polygon.cpp \
    geometricprimitive.cpp \
    vectorpicture.cpp \
    binarymarkerdispatcher.cpp

HEADERS += \
    point.h \
    pointset.h \
    color.h \
    painteradapter.h \
    polygon.h \
    binaryserializable.h \
    geometricprimitive.h \
    vectorpicture.h \
    binarymarkerdispatcher.h

