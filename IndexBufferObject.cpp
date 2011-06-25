#include "IndexBufferObject.h"

IndexBufferObject::IndexBufferObject()
{
    GLuint Indices[] = {
        // Top
        0, 1, 2,
        0, 2, 3,
        // Bottom
        4, 5, 6,
        4, 7, 6,
        // Left
        3, 2, 6,
        3, 7, 6,
        // Right
        0, 5, 1,
        0, 4, 5,
        // Front
        0, 3, 4,
        3, 7, 4,
        // Back
        1, 6, 2,
        1, 5, 6
    };


    Target = GL_ELEMENT_ARRAY_BUFFER;
    NumElements = sizeof(Indices)/sizeof(GLuint);

    Generate();
    glBufferData(Target, sizeof(Indices), Indices, GL_STATIC_DRAW);
}

IndexBufferObject::IndexBufferObject(const GLuint *Indices, int BufferSize)
{
    Target = GL_ELEMENT_ARRAY_BUFFER;
    NumElements = BufferSize/sizeof(GLuint);

    Generate();
    glBufferData(Target, BufferSize, Indices, GL_STATIC_DRAW);
}

IndexBufferObject::IndexBufferObject(const vector<GLuint> Indices)
{
    Target = GL_ELEMENT_ARRAY_BUFFER;
    NumElements = Indices.size();

    Generate();
    glBufferData(Target, NumElements * sizeof(GLuint), &Indices[0], GL_STATIC_DRAW);
}

void IndexBufferObject::Draw()
{
    glDrawElements(GL_TRIANGLES, NumElements, GL_UNSIGNED_INT, 0);
}

