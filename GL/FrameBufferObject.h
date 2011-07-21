#ifndef FRAMEBUFFEROBJECT_H
#define FRAMEBUFFEROBJECT_H

#include "Framework.h"
#include "ShaderProgram.h"
#include "VertexArrayObject.h"

class FrameBufferObject
{
private:
    GLuint fbo, fboDepth;
    GLuint * fboTextures;
    int width, height, samples;
    mat4 ortho, model, view;
    BufferObjectData bod;
    VertexArrayObject * Vao;
    ShaderMaterial mats;
    ShaderProgram * sp;
    vector<GLenum> attachments;
    int numBuffers;
public:
    FrameBufferObject();
    FrameBufferObject(int w, int h, int aaSamples, bool deferred);

    void Bind();
    void RenderToScreen();
    void Unbind();
};

#endif // FRAMEBUFFEROBJECT_H
