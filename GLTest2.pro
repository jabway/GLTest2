
HEADERS += \
    Framework.h \
    Vertex.h \
    AssimpLoader.h \
    Matrices.h \
    Lights.h \
    Mesh.h \
    SceneNode.h \
    GLScene.h \
    SceneMesh.h \
    SceneCamera.h

SOURCES += \
    Main.cpp \
    AssimpLoader.cpp \
    Matrices.cpp \
    Lights.cpp \
    Mesh.cpp \
    SceneNode.cpp \
    GLScene.cpp \
    SceneMesh.cpp \
    SceneCamera.cpp

    include(GL/GL.pri)
    include(Input/Input.pri)
