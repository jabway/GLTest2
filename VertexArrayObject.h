#ifndef VERTEXARRAYOBJECT_H
#define VERTEXARRAYOBJECT_H

#include "Framework.h"
#include "Vertex.h"
#include "IndexBufferObject.h"
#include "VertexBufferObject.h"
#include "OBJLoader.h"

class VertexArrayObject
{
private:
    GLuint  VaoId;

    VertexBufferObject * VBO;
    IndexBufferObject *IBO;
public:
    VertexArrayObject();
    ~VertexArrayObject();
    void Draw();
};

#endif // VERTEXARRAYOBJECT_H
