TEMPLATE = app
QT += core gui sql testlib


SOURCES += ../src/Entity/contact.cpp \
           ../src/Model/contactmodel.cpp \
           ../src/Database/databasemanager.cpp \
           ../src/Database/schemamanager.cpp \
           ../src/Lib/logger.cpp \
           test_unit.cpp

HEADERS += ../src/Entity/contact.h \
           ../src/Model/contactmodel.h \
           ../src/Database/databasemanager.h \
           ../src/Database/schemamanager.h \
           ../src/Lib/logger.h

INCLUDEPATH += ../src
INCLUDEPATH += ../src/Model
INCLUDEPATH += ../src/Entity
