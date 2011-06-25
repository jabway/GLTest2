#include "VertexBufferObject.h"

VertexBufferObject::VertexBufferObject()
{
    float o_st = 0.577350269f;
    Vertex Vertices[] =
    {
        //Top
        { { 1.0f, 1.0f, 1.0f, 1.0f }, { o_st, o_st, o_st}, { 1.0f, 1.0f, 1.0f, 1.0f } },
        { { 1.0f, 1.0f, -1.0f, 1.0f }, { o_st, o_st, -o_st }, { 1.0f, 1.0f, -1.0f, 1.0f } },
        { { -1.0f, 1.0f, -1.0f, 1.0f }, { -o_st, o_st, -o_st }, { -1.0f, 1.0f, -1.0f, 1.0f } },
        { { -1.0f, 1.0f, 1.0f, 1.0f }, { -o_st, o_st, o_st }, { -1.0f, 1.0f, 1.0f, 1.0f } },
        //Bottom
        { { 1.0f, -1.0f, 1.0f, 1.0f }, { o_st, -o_st, o_st }, { 1.0f, -1.0f, 1.0f, 1.0f } },
        { { 1.0f, -1.0f, -1.0f, 1.0f }, { o_st, -o_st, -o_st }, { 1.0f, -1.0f, -1.0f, 1.0f } },
        { { -1.0f, -1.0f, -1.0f, 1.0f }, {- o_st, -o_st, -o_st }, { -1.0f, -1.0f, -1.0f, 1.0f } },
        { { -1.0f, -1.0f, 1.0f, 1.0f }, { -o_st, -o_st, o_st }, { -1.0f, -1.0f, 1.0f, 1.0f } }
    };



    const size_t VertexSize = sizeof(Vertex);
    const size_t BufferSize = sizeof(Vertices);
    const size_t NormalOffset = sizeof(Vertices[0].XYZW);
    const size_t RgbOffset = NormalOffset + sizeof(Vertices[0].Normal);

    Target = GL_ARRAY_BUFFER;

    Generate();
    glBufferData(Target, BufferSize, Vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, VertexSize, (GLvoid*)NormalOffset);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset);

    // Disable Vertex attributes
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
}

VertexBufferObject::VertexBufferObject(const Vertex *Vertices, int BufferSize)
{


    const size_t VertexSize = sizeof(Vertex);

    const size_t NormalOffset = sizeof(Vertices[0].XYZW);
    const size_t RgbOffset = NormalOffset + sizeof(Vertices[0].Normal);

    Target = GL_ARRAY_BUFFER;

    Generate();
    glBufferData(Target, BufferSize, Vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, VertexSize, (GLvoid*)NormalOffset);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset);

    // Disable Vertex attributes
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
}

VertexBufferObject::VertexBufferObject(const vector<Vertex> Vertices)
{
    const size_t VertexSize = sizeof(Vertex);

    const size_t NormalOffset = sizeof(Vertices[0].XYZW);
    const size_t RgbOffset = NormalOffset + sizeof(Vertices[0].Normal);

    Target = GL_ARRAY_BUFFER;

    Generate();
    glBufferData(Target, Vertices.size()*sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, VertexSize, (GLvoid*)NormalOffset);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset);

    // Disable Vertex attributes
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
}
