TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    voxelitem.cpp \
    math/matrix3.cpp \
    math/matrix4.cpp \
    math/transform2D.cpp \
    math/transform3D.cpp \
    math/vector2.cpp \
    math/vector3.cpp \
    math/vector4.cpp \
    math/aabb.cpp \
    tracer/voxeltracer.cpp \
    tracer/instance.cpp \
    math/ray.cpp \
    tracer/pinholecamera.cpp \
    math/uvw.cpp \
    imagedata.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    voxelitem.h \
    math/mathutil.h \
    math/matrix3.h \
    math/matrix4.h \
    math/transform2d.h \
    math/transform3d.h \
    math/vector2.h \
    math/vector3.h \
    math/vector4.h \
    math/aabb.h \
    tracer/voxeltracer.h \
    tracer/data.h \
    tracer/canvas.h \
    tracer/instance.h \
    math/ray.h \
    tracer/pinholecamera.h \
    math/uvw.h \
    imagedata.h \
    tracer/mockdata.h

DISTFILES +=

CONFIG += c++11
