TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    point.cpp \
    color.cpp \
    polygon.cpp \
    geometricprimitive.cpp \
    vectorpicture.cpp \
    binarymarkerdispatcher.cpp \
    ellipse.cpp

HEADERS += \
    point.h \
    color.h \
    polygon.h \
    binaryserializable.h \
    geometricprimitive.h \
    vectorpicture.h \
    binarymarkerdispatcher.h \
    ellipse.h \
    painter.h \
    bytearray.h

