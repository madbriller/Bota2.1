#-------------------------------------------------
#
# Project created by QtCreator 2015-05-29T15:05:06
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BotaTwo
TEMPLATE = app


SOURCES += main.cpp\
        bota2.cpp \
    databasemanager.cpp \
    matchmanager.cpp \
    teammanager.cpp \
    addteam.cpp

HEADERS  += bota2.h \
    databasemanager.h \
    matchmanager.h \
    teammanager.h \
    addteam.h

FORMS    += \
    bota2.ui \
    addteam.ui

OTHER_FILES += \
    bota2.asdadui
