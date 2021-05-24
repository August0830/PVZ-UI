QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

QMAKE_CXXFLAGS += "-std=c++11"
QT += multimedia
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basiczombie.cpp \
    bucketzombie.cpp \
    bullet.cpp \
    button.cpp \
    card.cpp \
    cherrybomb.cpp \
    conezombie.cpp \
    doubleshooter.cpp \
    footballzombie.cpp \
    frozenshooter.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    mower.cpp \
    nut.cpp \
    other.cpp \
    peashooter.cpp \
    plant.cpp \
    potatomine.cpp \
    screenzombie.cpp \
    shop.cpp \
    shovel.cpp \
    sun.cpp \
    sunflower.cpp \
    zombie.cpp

HEADERS += \
    basiczombie.h \
    bucketzombie.h \
    bullet.h \
    button.h \
    card.h \
    cherrybomb.h \
    conezombie.h \
    doubleshooter.h \
    footballzombie.h \
    frozenshooter.h \
    mainwindow.h \
    map.h \
    mower.h \
    nut.h \
    other.h \
    peashooter.h \
    plant.h \
    potatomine.h \
    screenzombie.h \
    shop.h \
    shovel.h \
    sun.h \
    sunflower.h \
    zombie.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    myresouce.qrc




