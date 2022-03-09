QT += core gui widgets charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    barchart.cpp \
    chart.cpp \
    controller.cpp \
    error.cpp \
    jsonparser.cpp \
    linechart.cpp \
    main.cpp \
    model.cpp \
    modelerror.cpp \
    parser.cpp \
    parsingerror.cpp \
    scene.cpp \
    view.cpp \
    xmlparser.cpp
    scene.cpp \
    view.cpp

HEADERS += \
    barchart.h \
    chart.h \
    controller.h \
    error.h \
    jsonparser.h \
    linechart.h \
    model.h \
    modelerror.h \
    parser.h \
    parsingerror.h \
    scene.h \
    view.h \
    xmlparser.h
    scene.h \
    view.h

RESOURCES = res.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
