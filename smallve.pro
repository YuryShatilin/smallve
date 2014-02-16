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
QMAKE_CXXFLAGS += -std=c++11
LIBS += -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab -ltbb /lib64/libXext.so /lib64/libX11.so /lib64/libICE.so /lib64/libSM.so /lib64/libGL.so /lib64/libGLU.so -lrt -lpthread -lm -ldl
DEFINES += SMALLVE_LIBRARY

SOURCES += \
    src/smallve.cpp \
    src/tools/logger.cpp \
    src/ieffect.cpp \
    src/effectmosaic.cpp \
    src/effectreplicate.cpp \
    src/effectgrayscale.cpp \
    src/effectcrop.cpp \
    src/effectborder.cpp \
    src/compositeeffect.cpp \
    src/iframe.cpp \
    src/ivideomanipulator.cpp \
    src/tools/simplemessagewriter.cpp \
    src/tools/imessagewriter.cpp \
    src/effectmanager.cpp \
    src/blureffect.cpp \
    src/opencvimpl/opencvframe.cpp \
    src/opencvimpl/opencvvideomanipulator.cpp

HEADERS += \
    include/smallve.h \
    include/tools/logger.h \
    include/ieffect.h \
    include/effectmosaic.h \
    include/effectreplicate.h \
    include/effects.h \
    include/effectgrayscale.h \
    include/effectcrop.h \
    include/effectborder.h \
    include/compositeeffect.h \
    include/iframe.h \
    include/ivideomanipulator.h \
    include/tools/simplemessagewriter.h \
    include/tools/imessagewriter.h \
    include/effectmanager.h \
    include/blureffect.h \
    include/opencvimpl/opencvframe.h \
    include/opencvimpl/opencvvideomanipulator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

CONFIG(debug, debug|release) {
    DEFINES += SMALLVE_DEBUG
    QMAKE_CXXFLAGS += -O0
}

CONFIG(release, debug|release) {
    QMAKE_CXXFLAGS += -O2
}
