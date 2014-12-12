TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

OTHER_FILES += \
    program.txt \
    tape.txt \
    output.txt

QMAKE_CXXFLAGS += -std=c++11
