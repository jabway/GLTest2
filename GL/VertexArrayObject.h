#ifndef VERTEXARRAYOBJECT_H
#define VERTEXARRAYOBJECT_H

#include "Framework.h"
#include "Vertex.h"
#include "IndexBufferObject.h"
#include "VertexBufferObject.h"
#include "BufferObjectData.h"

class VertexArrayObject
{
private:
    GLuint  VaoId;

    IndexBufferObject * IBO;

    int MaxAttribs;
public:
    VertexArrayObject();
    ~VertexArrayObject();
    void BindBuffers(BufferObjectData& Bod,
                     const vector<GLuint>& Indices);
    void Draw();
};

#endif // VERTEXARRAYOBJECT_H
