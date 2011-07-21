#ifndef UNIFORMBUFFEROBJECT_H
#define UNIFORMBUFFEROBJECT_H

#include "BufferObject.h"

class UniformBufferObject : public BufferObject
{
public:
    UniformBufferObject();
    void BufferData(void* data, GLuint size);
    void Bind(GLuint index, GLuint offset, GLuint size);
};

#endif // UNIFORMBUFFEROBJECT_H
