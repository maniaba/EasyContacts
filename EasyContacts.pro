QT += core gui widgets sql testlib

# Set the project name
TARGET = ContactManager
TEMPLATE = app

# Specify the C++ standard
CONFIG += c++11

# Source files
SOURCES += \
    src/Forms/contactstoreform.cpp \
    src/Forms/oprogramu.cpp \
    src/Model/contactmodel.cpp \
    src/main.cpp \
    src/Forms/easycontacts.cpp \
    src/Entity/contact.cpp \
    src/Database/databasemanager.cpp \
    src/Database/schemamanager.cpp

# Header files
HEADERS += \
    src/Forms/contactstoreform.h \
    src/Forms/easycontacts.h \
    src/Entity/contact.h \
    src/Database/databasemanager.h \
    src/Database/schemamanager.h \
    src/Forms/oprogramu.h \
    src/Model/contactmodel.h
# UI files
FORMS += \
    src/Forms/contactstoreform.ui \
    src/Forms/easycontacts.ui \
    src/Forms/oprogramu.ui

# Additional configurations (e.g., include paths, libraries)
# INCLUDEPATH += libs/third_party_library/include
# LIBS += -Llibs/third_party_library/lib -lthird_party_library

