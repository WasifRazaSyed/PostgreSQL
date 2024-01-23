QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialog_box.cpp \
    landing.cpp \
    login.cpp \
    main.cpp \
    mover.cpp

HEADERS += \
    dialog_box.h \
    landing.h \
    login.h \
    mover.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


LIBS+="-LC:/Program Files/PostgreSQL/12/lib"
win32: LIBS += -llibpq
LIBS+="-LC:/Program Files/libpqxx/lib"
win32: LIBS += -lpqxx

win32: LIBS += -lwsock32
win32: LIBS += -lws2_32
INCLUDEPATH += "C:/Program Files/libpqxx/include"

RESOURCES += \
    resource.qrc
