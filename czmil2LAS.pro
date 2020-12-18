RC_FILE = czmil2LAS.rc
RESOURCES = icons.qrc
contains(QT_CONFIG, opengl): QT += opengl
QT += 
INCLUDEPATH += C:/PFM/compile/include
LIBS += -LC:/PFM/compile/lib -lCZMIL -lproj -lnvutility -llas -lgdal -lxml2 -lpoppler -liconv
DEFINES += WIN32 NVWIN3X UINT32_C INT32_C
CONFIG += exceptions
CONFIG += console
QMAKE_CXXFLAGS += -fno-strict-aliasing
QMAKE_LFLAGS += 
######################################################################
# Automatically generated by qmake (2.01a) Mon Dec 14 10:49:25 2020
######################################################################

TEMPLATE = app
TARGET = czmil2LAS
DEPENDPATH += . nbproject\private
INCLUDEPATH += .

# Input
HEADERS += czmil2LAS.hpp \
           czmil2LASDef.hpp \
           fileInputPage.hpp \
           fileInputPageHelp.hpp \
           optionPage.hpp \
           optionPageHelp.hpp \
           runPage.hpp \
           runPageHelp.hpp \
           startPage.hpp \
           startPageHelp.hpp \
           version.hpp
SOURCES += czmil2LAS.cpp \
           fileInputPage.cpp \
           main.cpp \
           optionPage.cpp \
           runPage.cpp \
           startPage.cpp \
           nbproject/private/c_standard_headers_indexer.c \
           nbproject/private/cpp_standard_headers_indexer.cpp
RESOURCES += icons.qrc
TRANSLATIONS += czmil2LAS_xx.ts