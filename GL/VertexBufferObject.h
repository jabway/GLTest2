#ifndef VERTEXBUFFEROBJECT_H
#define VERTEXBUFFEROBJECT_H

#include "BufferObject.h"
#include "Vertex.h"

class VertexBufferObject : public BufferObject
{
public:
    VertexBufferObject();
    VertexBufferObject(const vector<GLfloat> BufferData);
};

#endif // VERTEXBUFFEROBJECT_H
