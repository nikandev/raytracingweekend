QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    camera.cpp \
    dielectric.cpp \
    hitrecord.cpp \
    hittable.cpp \
    lambertian.cpp \
    main.cpp \
    mainwindow.cpp \
    material.cpp \
    materialmetal.cpp \
    ray.cpp \
    renderer.cpp \
    sphere.cpp \
    utility.cpp

HEADERS += \
    camera.h \
    common.h \
    dielectric.h \
    hitrecord.h \
    hittable.h \
    lambertian.h \
    mainwindow.h \
    material.h \
    materialmetal.h \
    ray.h \
    renderer.h \
    sphere.h \
    utility.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
