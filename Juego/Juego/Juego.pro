QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    entidad.cpp \
    estrategia.cpp \
    fireenemy.cpp \
    fisicas.cpp \
    main.cpp \
    mainwindow.cpp \
    nivel1.cpp \
    nivel2.cpp \
    objetojuego.cpp \
    obstaculo.cpp \
    premio.cpp \
    snowman.cpp \
    vector2d.cpp \
    zonasegura.cpp

HEADERS += \
    entidad.h \
    estrategia.h \
    fireenemy.h \
    fisicas.h \
    mainwindow.h \
    nivel1.h \
    nivel2.h \
    objetoJuego.h \
    obstaculo.h \
    premio.h \
    snowman.h \
    vector2D.h \
    zonasegura.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Recursos.qrc
