TEMPLATE = app
TARGET = qsqldbTest

CONFIG += console
CONFIG -= app_bundle

#CONFIG -= qt
QT -= gui
QT += sql

DEFINES += DEBUG

SOURCES += main.cpp

include(deployment.pri)
qtcAddDeployment()
