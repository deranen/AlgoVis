TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    GLVis.cpp \
    GLUtils.cpp

QMAKE_CXXFLAGS += -std=c++11

CONFIG(debug, debug|release): QMAKE_CXXFLAGS += -D_DEBUG

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-EasyGeom-Desktop-Debug/release/ -lEasyGeom
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-EasyGeom-Desktop-Debug/debug/ -lEasyGeom
else:unix: LIBS += -L$$PWD/../build-EasyGeom-Desktop-Debug/ -lEasyGeom

INCLUDEPATH += $$PWD/../EasyGeom
DEPENDPATH += $$PWD/../EasyGeom

mac: INCLUDEPATH += /Library/Frameworks/SDL2.framework/Headers
mac: INCLUDEPATH += /System/Library/Frameworks/OpenGL.framework/Headers

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-EasyGeom-Desktop-Debug/release/libEasyGeom.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-EasyGeom-Desktop-Debug/debug/libEasyGeom.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-EasyGeom-Desktop-Debug/release/EasyGeom.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-EasyGeom-Desktop-Debug/debug/EasyGeom.lib
else:unix: PRE_TARGETDEPS += $$PWD/../build-EasyGeom-Desktop-Debug/libEasyGeom.a

mac: LIBS += -F/Library/Frameworks -framework SDL2
else:unix|win32: LIBS += -lSDL2

mac: LIBS += -framework OpenGL
else:unix|win32: LIBS += -lOpenGL

HEADERS += \
    GLVis.h \
    GLUtils.h

OTHER_FILES += \
    triangles.frag \
    triangles.vert
