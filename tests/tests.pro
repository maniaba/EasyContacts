TEMPLATE = app
QT += core gui sql testlib


SOURCES += ../src/Entity/contact.cpp \
           ../src/Model/contactmodel.cpp \
           ../src/Database/databasemanager.cpp \
           ../src/Database/schemamanager.cpp \
           test_contactmodel.cpp

HEADERS += ../src/Entity/contact.h \
           ../src/Model/contactmodel.h \
           ../src/Database/databasemanager.h \
           ../src/Database/schemamanager.h

INCLUDEPATH += ../src
INCLUDEPATH += ../src/Model
INCLUDEPATH += ../src/Entity
