#-------------------------------------------------
#
# Project created by QtCreator 2015-08-22T14:32:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = firstQt
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    settingdialog.cpp \
    messagedialog.cpp \
    xraywindow.cpp \
    imagewindow.cpp \
    faqwindow.cpp \
    debugwindow.cpp

HEADERS  += mainwindow.h \
    default_setting.h \
    settingdialog.h \
    messagedialog.h \
    xraywindow.h \
    imagewindow.h \
    preferences.h \
    customtreeview.h \
    faqwindow.h \
    debugwindow.h \
    customscrollarea.h \
    customimagelabel.h

FORMS    += mainwindow.ui \
    settingdialog.ui \
    messagedialog.ui \
    xraywindow.ui \
    imagewindow.ui \
    faqwindow.ui \
    debugwindow.ui
