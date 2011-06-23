#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject()
{
    Vertex Vertices[] =
    {
        //Top
        { { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } },
        { { 1.0f, 1.0f, -1.0f, 1.0f }, { 1.0f, 1.0f, -1.0f, 1.0f } },
        { { -1.0f, 1.0f, -1.0f, 1.0f }, { -1.0f, 1.0f, -1.0f, 1.0f } },
        { { -1.0f, 1.0f, 1.0f, 1.0f }, { -1.0f, 1.0f, 1.0f, 1.0f } },
        //Bottom
        { { 1.0f, -1.0f, 1.0f, 1.0f }, { 1.0f, -1.0f, 1.0f, 1.0f } },
        { { 1.0f, -1.0f, -1.0f, 1.0f }, { 1.0f, -1.0f, -1.0f, 1.0f } },
        { { -1.0f, -1.0f, -1.0f, 1.0f }, { -1.0f, -1.0f, -1.0f, 1.0f } },
        { { -1.0f, -1.0f, 1.0f, 1.0f }, { -1.0f, -1.0f, 1.0f, 1.0f } }
    };

    GLenum ErrorCheckValue = glGetError();
    const size_t BufferSize = sizeof(Vertices);
    const size_t VertexSize = sizeof(Vertices[0]);
    const size_t RgbOffset = sizeof(Vertices[0].XYZW);

//    glGenBuffers(1, &VboId);

    glGenVertexArrays(1, &VaoId);
    glBindVertexArray(VaoId);

//    glBindBuffer(GL_ARRAY_BUFFER, VboId);
//    glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);
    VBO = new VertexBufferObject();

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // Create IBO
    IBO = new IndexBufferObject();

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        fprintf(
            stderr,
            "ERROR: Could not create a VBO: %s \n",
            gluErrorString(ErrorCheckValue)
        );

        exit(-1);
    }
}

VertexArrayObject::~VertexArrayObject()
{
    GLenum ErrorCheckValue = glGetError();

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

//    glBindBuffer(GL_ARRAY_BUFFER, 0);

//    glDeleteBuffers(1, &VboId);
    if(VBO)
        delete VBO;

    if(IBO)
        delete IBO;

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VaoId);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        fprintf(
            stderr,
            "ERROR: Could not destroy the VBO: %s \n",
            gluErrorString(ErrorCheckValue)
        );

        exit(-1);
    }
}
