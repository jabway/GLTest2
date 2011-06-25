#ifndef VERTEXBUFFEROBJECT_H
#define VERTEXBUFFEROBJECT_H

#include "BufferObject.h"
#include "Vertex.h"

class VertexBufferObject : public BufferObject
{
public:
    VertexBufferObject();
    VertexBufferObject(const Vertex * Vertices, int BufferSize);
    VertexBufferObject(const vector<Vertex> Vertices);
};

#endif // VERTEXBUFFEROBJECT_H
