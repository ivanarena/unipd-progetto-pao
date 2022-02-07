QT += core gui widgets charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chart.cpp \
    chart_container.cpp \
    controller.cpp \
    jsonparser.cpp \
    main.cpp \
    model.cpp \
    parser.cpp \
    pie_chart.cpp \
    view.cpp

HEADERS += \
    chart.h \
    chart_container.h \
    controller.h \
    jsonparser.h \
    model.h \
    parser.h \
    pie_chart.h \
    view.h

RESOURCES = res.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
