QT       += core gui
QT+=sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminwindow.cpp \
    city.cpp \
    dialogaddcity.cpp \
    dialoginputcity.cpp \
    dialoginputuser.cpp \
    dialogreviseuser.cpp \
    dialogsignup.cpp \
    linearregression.cpp \
    main.cpp \
    signwindow.cpp \
    user.cpp \
    userwindow.cpp

HEADERS += \
    adminwindow.h \
    city.h \
    dialogaddcity.h \
    dialoginputcity.h \
    dialoginputuser.h \
    dialogreviseuser.h \
    dialogsignup.h \
    linearregression.h \
    signwindow.h \
    user.h \
    userwindow.h

FORMS += \
    adminwindow.ui \
    dialogaddcity.ui \
    dialoginputcity.ui \
    dialoginputuser.ui \
    dialogreviseuser.ui \
    dialogsignup.ui \
    signwindow.ui \
    userwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
