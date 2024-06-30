QT += core gui widgets

# Set the project name
TARGET = ContactManager
TEMPLATE = app

# Specify the C++ standard
CONFIG += c++11

# Source files
SOURCES += \
    src/contact.cpp \
    src/main.cpp \
    src/easycontacts.cpp

# Header files
HEADERS += \
    src/contact.h \
    src/easycontacts.h

# UI files
FORMS += \
    src/easycontacts.ui

# Additional configurations (e.g., include paths, libraries)
# INCLUDEPATH += libs/third_party_library/include
# LIBS += -Llibs/third_party_library/lib -lthird_party_library
