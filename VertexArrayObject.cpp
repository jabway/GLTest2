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

    GLubyte Indices[] = {
        // Top
        0, 1, 2,
        0, 3, 2,
        // Bottom
        4, 5, 6,
        4, 7, 6,
        // Left
        3, 2, 6,
        3, 7, 6,
        // Right
        0, 1, 5,
        0, 4, 5,
        // Front
        0, 3, 4,
        3, 7, 4,
        // Back
        1, 2, 6,
        1, 5, 6
    };

    GLenum ErrorCheckValue = glGetError();
    const size_t BufferSize = sizeof(Vertices);
    const size_t VertexSize = sizeof(Vertices[0]);
    const size_t RgbOffset = sizeof(Vertices[0].XYZW);

    glGenBuffers(1, &VboId);

    glGenVertexArrays(1, &VaoId);
    glBindVertexArray(VaoId);

    glBindBuffer(GL_ARRAY_BUFFER, VboId);
    glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // Create IBO
//    glGenBuffers(1, &IndexBufferId);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferId);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
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

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &VboId);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &IndexBufferId);

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
