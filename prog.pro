QT += core gui widgets charts
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    barchart.cpp \
    chart.cpp \
    controller.cpp \
    jsonparser.cpp \
    linechart.cpp \
    main.cpp \
    model.cpp \
    parser.cpp \
    piechart.cpp \
    polarchart.cpp \
    scatterchart.cpp \
    scene.cpp \
    view.cpp \
    xmlparser.cpp

HEADERS += \
    barchart.h \
    chart.h \
    controller.h \
    jsonparser.h \
    linechart.h \
    model.h \
    parser.h \
    piechart.h \
    polarchart.h \
    scatterchart.h \
    scene.h \
    view.h \
    xmlparser.h

RESOURCES = res.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
