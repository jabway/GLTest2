#ifndef VERTEXARRAYOBJECT_H
#define VERTEXARRAYOBJECT_H

#include "Framework.h"
#include "Vertex.h"
#include "IndexBufferObject.h"
#include "ShaderProgram.h"
#include "VertexBufferObject.h"
#include "OBJLoader.h"
#include "BufferObjectData.h"

class VertexArrayObject
{
private:
    GLuint  VaoId;

    IndexBufferObject * IBO;
    ShaderProgram * sp;
    mat4 Model;

    int MaxAttribs;
public:
    VertexArrayObject();
    ~VertexArrayObject();
    void BindBuffers(BufferObjectData& Bod,
                     const vector<GLuint>& Indices);
    void Draw();
    void AttachShader(string vert, string frag);
    void AddModelMatrix(mat4 _model);
};

#endif // VERTEXARRAYOBJECT_H
