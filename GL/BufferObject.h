#ifndef BUFFEROBJECT_H
#define BUFFEROBJECT_H

#include "Framework.h"

class BufferObject
{
protected:
    void Generate();


    GLenum Target;
public:
    BufferObject();
    ~BufferObject();
    void Bind();
    void Unbind();

    GLuint BufferId;
};

#endif // BUFFEROBJECT_H
