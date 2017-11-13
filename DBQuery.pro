#-------------------------------------------------
#
# Project created by QtCreator 2017-10-14T18:59:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DBQuery
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
 DESTDIR       = ../plugins
 INCLUDEPATH    += ../QPluginBil ../DBComTools ../NetLib
SOURCES += main.cpp\
    frmdbmain.cpp \
    frmconfig.cpp \
    ContentWidget.cpp \
    mainwindow.cpp \
    titlewidget.cpp \
    mainmenu.cpp \
    pushbutton.cpp \
    toolbutton.cpp \
    systemtray.cpp \
    skinwidget.cpp \
    util.cpp \
    changeskinwidget.cpp \
    logindialog.cpp \
    accountitem.cpp \
    msgbox.cpp \
    loadingwidget.cpp \
    mainlog.cpp \
    dbmoniter.cpp \
    frmdb.cpp \
    pluginmanager.cpp \
    connectionpool.cpp \
    queryresult.cpp \
    xmlconfig.cpp \
    pluginread.cpp \
    plugininfo.cpp \
    netrecbil.cpp

HEADERS  += \
    frmdbmain.h \
    frmconfig.h \
    ContentWidget.h \
    mainwindow.h \
    titlewidget.h \
    mainmenu.h \
    common.h \
    pushbutton.h \
    toolbutton.h \
    systemtray.h \
    skinwidget.h \
    util.h \
    changeskinwidget.h \
    logindialog.h \
    accountitem.h \
    msgbox.h \
    loadingwidget.h \
    mainlog.h \
    dbmoniter.h \
    frmdb.h \
    pluginmanager.h \
    queryresult.h \
    xmlconfig.h \
    pluginread.h \
    plugininfo.h \
    netrecbil.h

FORMS    += \
    frmdbmain.ui \
    frmconfig.ui \
    mainwindow.ui \
    mainlog.ui \
    dbmoniter.ui \
    frmdb.ui

RESOURCES += \
    mysrc.qrc

TRANSLATIONS+= \
    360safe_en.ts \
     360safe_zh.ts \

QT += charts

QT += sql

QT += network
LIBS += ../plugins/DBComTools.dll  ../plugins/NetLib.dll

