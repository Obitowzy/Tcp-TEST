#-------------------------------------------------
#
# Project created by QtCreator 2023-09-21T15:45:25
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = TCP
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        bianbi.cpp \
        fenliang1.cpp \
        fenliang2.cpp \
        fenliang3.cpp \
        gonglv.cpp \
        main.cpp \
        mainui.cpp \
        mainwindow.cpp \
        signal_ui.cpp \
        tcplist.cpp

HEADERS += \
        bianbi.h \
        checkboxdelegate.h \
        fenliang1.h \
        fenliang2.h \
        fenliang3.h \
        gonglv.h \
        mainui.h \
        mainwindow.h \
        signal_ui.h \
        tcplist.h

FORMS += \
        bianbi.ui \
        fenliang1.ui \
        fenliang2.ui \
        fenliang3.ui \
        gonglv.ui \
        mainui.ui \
        mainwindow.ui \
        signal_ui.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    myapp.rc

RESOURCES += \
    resource.qrc

RC_ICONS = myappico.ico
