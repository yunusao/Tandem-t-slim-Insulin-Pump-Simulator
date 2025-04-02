QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bgscreen.cpp \
    bolusinitiatedscreen.cpp \
    bolusscreen.cpp \
    carbentryscreen.cpp \
    confirmdeliveryscreen.cpp \
    confirmextendedbolusscreen.cpp \
    createeditprofile.cpp \
    delivernowinputscreen.cpp \
    durationinputscreen.cpp \
    errorlogpage.cpp \
    confirmbolusscreen.cpp \
    correctionsuggestionscreen.cpp \
    extendedbolusscreen.cpp \
    finaldeliveryscreen.cpp \
    finalextendeddeliveryscreen.cpp \
    homescreen.cpp \
    main.cpp \
    mainwindow.cpp \
    optionsscreen.cpp \
    profilepage.cpp

HEADERS += \
    bgscreen.h \
    bolusinitiatedscreen.h \
    bolusscreen.h \
    carbentryscreen.h \
    confirmdeliveryscreen.h \
    confirmextendedbolusscreen.h \
    createeditprofile.h \
    delivernowinputscreen.h \
    durationinputscreen.h \
    errorlogpage.h \
    confirmbolusscreen.h \
    correctionsuggestionscreen.h \
    extendedbolusscreen.h \
    finaldeliveryscreen.h \
    finalextendeddeliveryscreen.h \
    homescreen.h \
    mainwindow.h \
    optionsscreen.h \
    profilepage.h

FORMS += \
    bgscreen.ui \
    bolusinitiatedscreen.ui \
    bolusscreen.ui \
    carbentryscreen.ui \
    confirmdeliveryscreen.ui \
    confirmextendedbolusscreen.ui \
    createeditprofile.ui \
    delivernowinputscreen.ui \
    durationinputscreen.ui \
    errorlogpage.ui \
    confirmbolusscreen.ui \
    correctionsuggestionscreen.ui \
    extendedbolusscreen.ui \
    finaldeliveryscreen.ui \
    finalextendeddeliveryscreen.ui \
    homescreen.ui \
    mainwindow.ui \
    optionsscreen.ui \
    profilepage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
