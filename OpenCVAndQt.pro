#-------------------------------------------------
#
# Project created by QtCreator 2012-11-08T14:21:14
#
#-------------------------------------------------

QT += core gui
QT -= bundle

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenCVAndQt
TEMPLATE = lib

CONFIG += c++11
CONFIG += console

#DEFINES += IMAGEVIEWERDLL_LIBRARY

win32{
INCLUDEPATH += ../../3rdLibs/openCV/OpenCV-2.4.5/build/include

LIBS += -L../../3rdLibs/openCV/OpenCV-2.4.5/build/x86/mingw/lib/ -lopencv_core245 -lopencv_highgui245 -lopencv_imgproc245 -lopencv_photo245
}
mac{
INCLUDEPATH += /usr/local/include

LIBS += -L/usr/local/lib/ -lopencv_core.2.4.5 -lopencv_imgproc.2.4.5
}

QMAKE_CXXFLAGS += -Woverloaded-virtual

SOURCES += \
    openCVToQt.cpp      

HEADERS  += \
    openCVToQt.hpp

OTHER_FILES +=
