# This project demonstrates how to use QtWebAppLib by including the
# sources into this project.

TARGET = webserver
TEMPLATE = app
QT = core network sql
CONFIG += console
QT_DEBUG_PLUGINS=1
DEFINES += SUPERVERBOSE
HEADERS += \
           src/controllers/requestcontroller.h \
           src/db/cdatabase.h \
           src/startup.h \
           src/requesthandler.h

SOURCES += src/main.cpp \
           src/controllers/requestcontroller.cpp \
           src/db/cdatabase.cpp \
           src/startup.cpp \
           src/requesthandler.cpp

OTHER_FILES += etc/* logs/* ../readme.txt

#---------------------------------------------------------------------------------------
# The following lines include the sources of the QtWebAppLib library
#---------------------------------------------------------------------------------------
INCLUDEPATH += src/db
include(QtWebApp/qtservice/qtservice.pri)
include(QtWebApp/httpserver/httpserver.pri)
include(QtWebApp/logging/logging.pri)
# Not used: include(../QtWebApp/templateengine/templateengine.pri)
