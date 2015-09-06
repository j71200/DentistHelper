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
    preferences.cpp \
    messagedialog.cpp

HEADERS  += mainwindow.h \
    default_setting.h \
    settingdialog.h \
    messagedialog.h \
    customtreeview.h \

FORMS    += mainwindow.ui \
    settingdialog.ui \
    messagedialog.ui
