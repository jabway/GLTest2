#############################################################################
# Makefile for building: GLTest2
# Generated by qmake (2.01a) (Qt 4.8.0) on: Sat Mar 17 16:58:24 2012
# Project:  GLTest2.pro
# Template: app
# Command: /usr/bin/qmake -spec /usr/share/qt/mkspecs/linux-g++ CONFIG+=debug CONFIG+=declarative_debug QMAKE_CXXFLAGS+=-std=c++0x -o Makefile GLTest2.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -std=c++0x -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt/mkspecs/linux-g++ -I. -I/usr/include/QtCore -I/usr/include/QtGui -I/usr/include -I.
LINK          = g++
LFLAGS        = -Wl,-O1,--sort-common,--as-needed,-z,relro,--hash-style=gnu
LIBS          = $(SUBLIBS)  -L/usr/lib -lGLEW -lGLU -lGL -lIL -lglfw -lassimp -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = Main.cpp \
		AssimpLoader.cpp \
		Matrices.cpp \
		Lights.cpp \
		Mesh.cpp \
		SceneNode.cpp \
		GLScene.cpp \
		SceneMesh.cpp \
		SceneCamera.cpp \
		GL/VertexShader.cpp \
		GL/VertexBufferObject.cpp \
		GL/VertexArrayObject.cpp \
		GL/UniformBufferObject.cpp \
		GL/ShaderProgram.cpp \
		GL/ShaderMaterial.cpp \
		GL/Shader.cpp \
		GL/OGLContext.cpp \
		GL/IndexBufferObject.cpp \
		GL/FragmentShader.cpp \
		GL/BufferObjectData.cpp \
		GL/BufferObject.cpp \
		GL/Renderer.cpp \
		GL/VertexAttribute.cpp \
		GL/FrameBufferObject.cpp 
OBJECTS       = Main.o \
		AssimpLoader.o \
		Matrices.o \
		Lights.o \
		Mesh.o \
		SceneNode.o \
		GLScene.o \
		SceneMesh.o \
		SceneCamera.o \
		VertexShader.o \
		VertexBufferObject.o \
		VertexArrayObject.o \
		UniformBufferObject.o \
		ShaderProgram.o \
		ShaderMaterial.o \
		Shader.o \
		OGLContext.o \
		IndexBufferObject.o \
		FragmentShader.o \
		BufferObjectData.o \
		BufferObject.o \
		Renderer.o \
		VertexAttribute.o \
		FrameBufferObject.o
DIST          = /usr/share/qt/mkspecs/common/unix.conf \
		/usr/share/qt/mkspecs/common/linux.conf \
		/usr/share/qt/mkspecs/common/gcc-base.conf \
		/usr/share/qt/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt/mkspecs/common/g++-base.conf \
		/usr/share/qt/mkspecs/common/g++-unix.conf \
		/usr/share/qt/mkspecs/qconfig.pri \
		/usr/share/qt/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt/mkspecs/features/qt_functions.prf \
		/usr/share/qt/mkspecs/features/qt_config.prf \
		/usr/share/qt/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt/mkspecs/features/default_pre.prf \
		GL/GL.pri \
		Input/Input.pri \
		/usr/share/qt/mkspecs/features/debug.prf \
		/usr/share/qt/mkspecs/features/default_post.prf \
		/usr/share/qt/mkspecs/features/declarative_debug.prf \
		/usr/share/qt/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt/mkspecs/features/warn_on.prf \
		/usr/share/qt/mkspecs/features/qt.prf \
		/usr/share/qt/mkspecs/features/unix/thread.prf \
		/usr/share/qt/mkspecs/features/moc.prf \
		/usr/share/qt/mkspecs/features/resources.prf \
		/usr/share/qt/mkspecs/features/uic.prf \
		/usr/share/qt/mkspecs/features/yacc.prf \
		/usr/share/qt/mkspecs/features/lex.prf \
		/usr/share/qt/mkspecs/features/include_source_dir.prf \
		GLTest2.pro
QMAKE_TARGET  = GLTest2
DESTDIR       = 
TARGET        = GLTest2

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)
	{ test -n "$(DESTDIR)" && DESTDIR="$(DESTDIR)" || DESTDIR=.; } && test $$(gdb --version | sed -e 's,[^0-9]\+\([0-9]\)\.\([0-9]\).*,\1\2,;q') -gt 72 && gdb --nx --batch --quiet -ex 'set confirm off' -ex "save gdb-index $$DESTDIR" -ex quit '$(TARGET)' && test -f $(TARGET).gdb-index && objcopy --add-section '.gdb_index=$(TARGET).gdb-index' --set-section-flags '.gdb_index=readonly' '$(TARGET)' '$(TARGET)' && rm -f $(TARGET).gdb-index || true

Makefile: GLTest2.pro  /usr/share/qt/mkspecs/linux-g++/qmake.conf /usr/share/qt/mkspecs/common/unix.conf \
		/usr/share/qt/mkspecs/common/linux.conf \
		/usr/share/qt/mkspecs/common/gcc-base.conf \
		/usr/share/qt/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt/mkspecs/common/g++-base.conf \
		/usr/share/qt/mkspecs/common/g++-unix.conf \
		/usr/share/qt/mkspecs/qconfig.pri \
		/usr/share/qt/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt/mkspecs/features/qt_functions.prf \
		/usr/share/qt/mkspecs/features/qt_config.prf \
		/usr/share/qt/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt/mkspecs/features/default_pre.prf \
		GL/GL.pri \
		Input/Input.pri \
		/usr/share/qt/mkspecs/features/debug.prf \
		/usr/share/qt/mkspecs/features/default_post.prf \
		/usr/share/qt/mkspecs/features/declarative_debug.prf \
		/usr/share/qt/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt/mkspecs/features/warn_on.prf \
		/usr/share/qt/mkspecs/features/qt.prf \
		/usr/share/qt/mkspecs/features/unix/thread.prf \
		/usr/share/qt/mkspecs/features/moc.prf \
		/usr/share/qt/mkspecs/features/resources.prf \
		/usr/share/qt/mkspecs/features/uic.prf \
		/usr/share/qt/mkspecs/features/yacc.prf \
		/usr/share/qt/mkspecs/features/lex.prf \
		/usr/share/qt/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt/mkspecs/linux-g++ CONFIG+=debug CONFIG+=declarative_debug QMAKE_CXXFLAGS+=-std=c++0x -o Makefile GLTest2.pro
/usr/share/qt/mkspecs/common/unix.conf:
/usr/share/qt/mkspecs/common/linux.conf:
/usr/share/qt/mkspecs/common/gcc-base.conf:
/usr/share/qt/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt/mkspecs/common/g++-base.conf:
/usr/share/qt/mkspecs/common/g++-unix.conf:
/usr/share/qt/mkspecs/qconfig.pri:
/usr/share/qt/mkspecs/modules/qt_phonon.pri:
/usr/share/qt/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt/mkspecs/features/qt_functions.prf:
/usr/share/qt/mkspecs/features/qt_config.prf:
/usr/share/qt/mkspecs/features/exclusive_builds.prf:
/usr/share/qt/mkspecs/features/default_pre.prf:
GL/GL.pri:
Input/Input.pri:
/usr/share/qt/mkspecs/features/debug.prf:
/usr/share/qt/mkspecs/features/default_post.prf:
/usr/share/qt/mkspecs/features/declarative_debug.prf:
/usr/share/qt/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt/mkspecs/features/warn_on.prf:
/usr/share/qt/mkspecs/features/qt.prf:
/usr/share/qt/mkspecs/features/unix/thread.prf:
/usr/share/qt/mkspecs/features/moc.prf:
/usr/share/qt/mkspecs/features/resources.prf:
/usr/share/qt/mkspecs/features/uic.prf:
/usr/share/qt/mkspecs/features/yacc.prf:
/usr/share/qt/mkspecs/features/lex.prf:
/usr/share/qt/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtGui.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt/mkspecs/linux-g++ CONFIG+=debug CONFIG+=declarative_debug QMAKE_CXXFLAGS+=-std=c++0x -o Makefile GLTest2.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/GLTest21.0.0 || $(MKDIR) .tmp/GLTest21.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/GLTest21.0.0/ && $(COPY_FILE) --parents Framework.h Vertex.h AssimpLoader.h Matrices.h Lights.h Mesh.h SceneNode.h GLScene.h SceneMesh.h SceneCamera.h GL/VertexShader.h GL/VertexBufferObject.h GL/VertexArrayObject.h GL/UniformBufferObject.h GL/ShaderProgram.h GL/ShaderMaterial.h GL/Shader.h GL/OGLContext.h GL/IndexBufferObject.h GL/FragmentShader.h GL/BufferObjectData.h GL/BufferObject.h GL/Renderer.h GL/VertexFormat.h GL/VertexAttribute.h GL/FrameBufferObject.h .tmp/GLTest21.0.0/ && $(COPY_FILE) --parents Main.cpp AssimpLoader.cpp Matrices.cpp Lights.cpp Mesh.cpp SceneNode.cpp GLScene.cpp SceneMesh.cpp SceneCamera.cpp GL/VertexShader.cpp GL/VertexBufferObject.cpp GL/VertexArrayObject.cpp GL/UniformBufferObject.cpp GL/ShaderProgram.cpp GL/ShaderMaterial.cpp GL/Shader.cpp GL/OGLContext.cpp GL/IndexBufferObject.cpp GL/FragmentShader.cpp GL/BufferObjectData.cpp GL/BufferObject.cpp GL/Renderer.cpp GL/VertexAttribute.cpp GL/FrameBufferObject.cpp .tmp/GLTest21.0.0/ && (cd `dirname .tmp/GLTest21.0.0` && $(TAR) GLTest21.0.0.tar GLTest21.0.0 && $(COMPRESS) GLTest21.0.0.tar) && $(MOVE) `dirname .tmp/GLTest21.0.0`/GLTest21.0.0.tar.gz . && $(DEL_FILE) -r .tmp/GLTest21.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all:
compiler_moc_header_clean:
compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: 

####### Compile

Main.o: Main.cpp Framework.h \
		GL/OGLContext.h \
		AssimpLoader.h \
		GL/BufferObjectData.h \
		Mesh.h \
		GL/ShaderMaterial.h \
		GL/ShaderProgram.h \
		GL/Shader.h \
		Matrices.h \
		GL/FragmentShader.h \
		Lights.h \
		GL/UniformBufferObject.h \
		GL/BufferObject.h \
		GL/VertexShader.h \
		GL/VertexArrayObject.h \
		Vertex.h \
		GL/IndexBufferObject.h \
		GL/VertexBufferObject.h \
		SceneMesh.h \
		SceneNode.h \
		GLScene.h \
		SceneCamera.h \
		GL/FrameBufferObject.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Main.o Main.cpp

AssimpLoader.o: AssimpLoader.cpp AssimpLoader.h \
		Framework.h \
		GL/BufferObjectData.h \
		Mesh.h \
		GL/ShaderMaterial.h \
		GL/ShaderProgram.h \
		GL/Shader.h \
		Matrices.h \
		GL/FragmentShader.h \
		Lights.h \
		GL/UniformBufferObject.h \
		GL/BufferObject.h \
		GL/VertexShader.h \
		GL/VertexArrayObject.h \
		Vertex.h \
		GL/IndexBufferObject.h \
		GL/VertexBufferObject.h \
		SceneMesh.h \
		SceneNode.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o AssimpLoader.o AssimpLoader.cpp

Matrices.o: Matrices.cpp Matrices.h \
		Framework.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Matrices.o Matrices.cpp

Lights.o: Lights.cpp Lights.h \
		Framework.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Lights.o Lights.cpp

Mesh.o: Mesh.cpp Mesh.h \
		Framework.h \
		GL/ShaderMaterial.h \
		GL/ShaderProgram.h \
		GL/Shader.h \
		Matrices.h \
		GL/FragmentShader.h \
		Lights.h \
		GL/UniformBufferObject.h \
		GL/BufferObject.h \
		GL/VertexShader.h \
		GL/VertexArrayObject.h \
		Vertex.h \
		GL/IndexBufferObject.h \
		GL/VertexBufferObject.h \
		GL/BufferObjectData.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Mesh.o Mesh.cpp

SceneNode.o: SceneNode.cpp SceneNode.h \
		Framework.h \
		Matrices.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o SceneNode.o SceneNode.cpp

GLScene.o: GLScene.cpp GLScene.h \
		Framework.h \
		SceneCamera.h \
		GL/FrameBufferObject.h \
		GL/ShaderProgram.h \
		GL/Shader.h \
		Matrices.h \
		GL/FragmentShader.h \
		Lights.h \
		GL/ShaderMaterial.h \
		GL/UniformBufferObject.h \
		GL/BufferObject.h \
		GL/VertexShader.h \
		GL/VertexArrayObject.h \
		Vertex.h \
		GL/IndexBufferObject.h \
		GL/VertexBufferObject.h \
		GL/BufferObjectData.h \
		SceneNode.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o GLScene.o GLScene.cpp

SceneMesh.o: SceneMesh.cpp SceneMesh.h \
		Mesh.h \
		Framework.h \
		GL/ShaderMaterial.h \
		GL/ShaderProgram.h \
		GL/Shader.h \
		Matrices.h \
		GL/FragmentShader.h \
		Lights.h \
		GL/UniformBufferObject.h \
		GL/BufferObject.h \
		GL/VertexShader.h \
		GL/VertexArrayObject.h \
		Vertex.h \
		GL/IndexBufferObject.h \
		GL/VertexBufferObject.h \
		GL/BufferObjectData.h \
		SceneNode.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o SceneMesh.o SceneMesh.cpp

SceneCamera.o: SceneCamera.cpp SceneCamera.h \
		GL/FrameBufferObject.h \
		Framework.h \
		GL/ShaderProgram.h \
		GL/Shader.h \
		Matrices.h \
		GL/FragmentShader.h \
		Lights.h \
		GL/ShaderMaterial.h \
		GL/UniformBufferObject.h \
		GL/BufferObject.h \
		GL/VertexShader.h \
		GL/VertexArrayObject.h \
		Vertex.h \
		GL/IndexBufferObject.h \
		GL/VertexBufferObject.h \
		GL/BufferObjectData.h \
		SceneNode.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o SceneCamera.o SceneCamera.cpp

VertexShader.o: GL/VertexShader.cpp GL/VertexShader.h \
		GL/Shader.h \
		Framework.h \
		Matrices.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o VertexShader.o GL/VertexShader.cpp

VertexBufferObject.o: GL/VertexBufferObject.cpp GL/VertexBufferObject.h \
		GL/BufferObject.h \
		Framework.h \
		Vertex.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o VertexBufferObject.o GL/VertexBufferObject.cpp

VertexArrayObject.o: GL/VertexArrayObject.cpp GL/VertexArrayObject.h \
		Framework.h \
		Vertex.h \
		GL/IndexBufferObject.h \
		GL/BufferObject.h \
		GL/VertexBufferObject.h \
		GL/BufferObjectData.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o VertexArrayObject.o GL/VertexArrayObject.cpp

UniformBufferObject.o: GL/UniformBufferObject.cpp GL/UniformBufferObject.h \
		GL/BufferObject.h \
		Framework.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o UniformBufferObject.o GL/UniformBufferObject.cpp

ShaderProgram.o: GL/ShaderProgram.cpp GL/ShaderProgram.h \
		GL/Shader.h \
		Framework.h \
		Matrices.h \
		GL/FragmentShader.h \
		Lights.h \
		GL/ShaderMaterial.h \
		GL/UniformBufferObject.h \
		GL/BufferObject.h \
		GL/VertexShader.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ShaderProgram.o GL/ShaderProgram.cpp

ShaderMaterial.o: GL/ShaderMaterial.cpp GL/ShaderMaterial.h \
		Framework.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ShaderMaterial.o GL/ShaderMaterial.cpp

Shader.o: GL/Shader.cpp GL/Shader.h \
		Framework.h \
		Matrices.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Shader.o GL/Shader.cpp

OGLContext.o: GL/OGLContext.cpp GL/OGLContext.h \
		AssimpLoader.h \
		Framework.h \
		GL/BufferObjectData.h \
		Mesh.h \
		GL/ShaderMaterial.h \
		GL/ShaderProgram.h \
		GL/Shader.h \
		Matrices.h \
		GL/FragmentShader.h \
		Lights.h \
		GL/UniformBufferObject.h \
		GL/BufferObject.h \
		GL/VertexShader.h \
		GL/VertexArrayObject.h \
		Vertex.h \
		GL/IndexBufferObject.h \
		GL/VertexBufferObject.h \
		SceneMesh.h \
		SceneNode.h \
		GLScene.h \
		SceneCamera.h \
		GL/FrameBufferObject.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o OGLContext.o GL/OGLContext.cpp

IndexBufferObject.o: GL/IndexBufferObject.cpp GL/IndexBufferObject.h \
		GL/BufferObject.h \
		Framework.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o IndexBufferObject.o GL/IndexBufferObject.cpp

FragmentShader.o: GL/FragmentShader.cpp GL/FragmentShader.h \
		GL/Shader.h \
		Framework.h \
		Matrices.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o FragmentShader.o GL/FragmentShader.cpp

BufferObjectData.o: GL/BufferObjectData.cpp GL/BufferObjectData.h \
		Framework.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o BufferObjectData.o GL/BufferObjectData.cpp

BufferObject.o: GL/BufferObject.cpp GL/BufferObject.h \
		Framework.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o BufferObject.o GL/BufferObject.cpp

Renderer.o: GL/Renderer.cpp GL/Renderer.h \
		AssimpLoader.h \
		Framework.h \
		GL/BufferObjectData.h \
		Mesh.h \
		GL/ShaderMaterial.h \
		GL/ShaderProgram.h \
		GL/Shader.h \
		Matrices.h \
		GL/FragmentShader.h \
		Lights.h \
		GL/UniformBufferObject.h \
		GL/BufferObject.h \
		GL/VertexShader.h \
		GL/VertexArrayObject.h \
		Vertex.h \
		GL/IndexBufferObject.h \
		GL/VertexBufferObject.h \
		SceneMesh.h \
		SceneNode.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Renderer.o GL/Renderer.cpp

VertexAttribute.o: GL/VertexAttribute.cpp GL/VertexAttribute.h \
		Framework.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o VertexAttribute.o GL/VertexAttribute.cpp

FrameBufferObject.o: GL/FrameBufferObject.cpp GL/FrameBufferObject.h \
		Framework.h \
		GL/ShaderProgram.h \
		GL/Shader.h \
		Matrices.h \
		GL/FragmentShader.h \
		Lights.h \
		GL/ShaderMaterial.h \
		GL/UniformBufferObject.h \
		GL/BufferObject.h \
		GL/VertexShader.h \
		GL/VertexArrayObject.h \
		Vertex.h \
		GL/IndexBufferObject.h \
		GL/VertexBufferObject.h \
		GL/BufferObjectData.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o FrameBufferObject.o GL/FrameBufferObject.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

