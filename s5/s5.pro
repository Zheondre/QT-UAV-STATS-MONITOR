QT += quick
QT += bluetooth

CONFIG += c++11
CONFIG += qml_debug
#CONFIG +=

#Pass
-qmljsdebugger=port:8080

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        basestats.cpp \
        src/FcAir/fcairstats.cpp \
        src/bluetooth/bluetooth.cpp \
        src/bluetooth/chatclient.cpp \
        src/bluetooth/chatserver.cpp \
        src/bluetooth/remoteselector.cpp \ 
        src/statsModel.cpp \
        src/favstatsmodel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    basestats.h \
    src/FcAir/fcairstats.h \
    src/bluetooth/bluetooth.h \
    src/bluetooth/chatclient.h \
    src/bluetooth/chatserver.h \
    src/bluetooth/remoteselector.h \
    src/statsModel.h \
    src/favstatsmodel.h \
    statsEntry.h

SUBDIRS += \
    src/bluetooth/btchat.pro

FORMS += \
    src/bluetooth/chat.ui \
    src/bluetooth/remoteselector.ui

DISTFILES += \
    src/bluetooth/CMakeLists.txt \
    src/bluetooth/doc/images/btchat-example.png \
    src/bluetooth/doc/src/btchat.qdoc \

ANDROID_ABIS = armeabi-v7a

