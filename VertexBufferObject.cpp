#include "VertexBufferObject.h"

VertexBufferObject::VertexBufferObject()
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

    const size_t BufferSize = sizeof(Vertices);
    Target = GL_ARRAY_BUFFER;

    Generate();
    glBufferData(Target, BufferSize, Vertices, GL_STATIC_DRAW);
}
