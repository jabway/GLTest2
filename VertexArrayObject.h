#ifndef VERTEXARRAYOBJECT_H
#define VERTEXARRAYOBJECT_H

#include "Framework.h"
#include "Vertex.h"
#include "IndexBufferObject.h"
#include "VertexBufferObject.h"

class VertexArrayObject
{
private:
    GLuint  VboId,
            VaoId;

    VertexBufferObject * VBO;
    IndexBufferObject *IBO;
public:
    VertexArrayObject();
    ~VertexArrayObject();
};

#endif // VERTEXARRAYOBJECT_H
