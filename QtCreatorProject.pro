QT += core gui opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += openglwidgets

CONFIG += c++11

INCLUDEPATH += AppTinyMesh/Include
INCLUDEPATH += $$(GLEW_DIR)
INCLUDEPATH += $$(OUT_PWD)

VPATH += AppTinyMesh

SOURCES += \
    $$files("*.cpp", true) \

HEADERS += \
    $$files("*.h", true) \

FORMS += \
    $$files("*.ui", true) \

win32 {
    LIBS += -L$$(GLEW_DIR) -lglew32
    LIBS += -lopengl32 -lglu32
}
unix:!macx {
    LIBS += -lGLEW -lGL -lGLU
}
macx {
    LIBS += -lGLEW -lGL -lGLU
}

# Copy shader files
# $$shell_quote puts quote around the path, to make it work if it contains space or other special characters.
copydata.commands = $(COPY_DIR) $$shell_path($$PWD\AppTinyMesh\Shaders) $$shell_path($$OUT_PWD\Shaders)
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
