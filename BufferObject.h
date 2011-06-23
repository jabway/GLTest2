#ifndef BUFFEROBJECT_H
#define BUFFEROBJECT_H

#include "Framework.h"

class BufferObject
{
protected:
    void Generate();

    GLuint BufferId;
    GLenum Target;
public:
    BufferObject();
    ~BufferObject();
};

#endif // BUFFEROBJECT_H
