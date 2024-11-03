QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addbook.cpp \
    addemprunt.cpp \
    addmember.cpp \
    bookmanager.cpp \
    dbacess.cpp \
    empruntmanager.cpp \
    main.cpp \
    mainwindow.cpp \
    membermanager.cpp \
    modifybook.cpp \
    modifymember.cpp \
    repportgenerator.cpp

HEADERS += \
    addbook.h \
    addemprunt.h \
    addmember.h \
    bookmanager.h \
    dbacess.h \
    empruntmanager.h \
    mainwindow.h \
    membermanager.h \
    modifybook.h \
    modifymember.h \
    repportgenerator.h

FORMS += \
    addbook.ui \
    addemprunt.ui \
    addmember.ui \
    bookmanager.ui \
    empruntmanager.ui \
    mainwindow.ui \
    membermanager.ui \
    modifybook.ui \
    modifymember.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
