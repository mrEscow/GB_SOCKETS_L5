QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


# if win
INCLUDEPATH += D:/geekbrains/BOOST/boost_1_79_0
LIBS += D:\Qt\QT6\Tools\mingw1120_64\x86_64-w64-mingw32\lib\libws2_32.a
LIBS += D:\Qt\QT6\Tools\mingw1120_64\x86_64-w64-mingw32\lib\libwsock32.a
LIBS += "-LD:\geekbrains\BOOST\boost_1_79_0\boost_mingw1120_64"
LIBS += "-LD:\Qt\QT6\Tools\mingw1120_64\x86_64-w64-mingw32\lib"


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Model.cpp \
    Request_Gun.cpp \
    TimeClient.cpp \
    TimeServer.cpp \
    Window.cpp \
    main.cpp

HEADERS += \
    Model.h \
    Protocol.h \
    Request_Gun.h \
    TimeClient.h \
    TimeServer.h \
    Window.h

FORMS += \
    Window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
