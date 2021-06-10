QT       += core gui
QT       += charts
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/basicChart.cpp \
    src/chart.cpp \
    src/doubleLineChart.cpp \
    src/main.cpp \
    src/regulacja.cpp \
    src/regulation.cpp \
    src/singleLineChart.cpp \
    src/tcpSocket.cpp

HEADERS += \
    include/basicChart.h \
    include/chart.h \
    include/doubleLineChart.h \
    include/pshm_stc.h \
    include/regulacja.h \
    include/regulation.h \
    include/singleLineChart.h \
    include/tcpSocket.h

LIBS += -lrt
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
