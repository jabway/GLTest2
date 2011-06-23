#ifndef VERTEXARRAYOBJECT_H
#define VERTEXARRAYOBJECT_H

#include "Framework.h"
#include "Vertex.h"
#include "IndexBufferObject.h"

class VertexArrayObject
{
private:
    GLuint  VboId,
            VaoId,
            IndexBufferId;
    IndexBufferObject *IBO;
public:
    VertexArrayObject();
    ~VertexArrayObject();
};

#endif // VERTEXARRAYOBJECT_H
