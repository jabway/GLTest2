#include "IndexBufferObject.h"

IndexBufferObject::IndexBufferObject()
{
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

    Target = GL_ELEMENT_ARRAY_BUFFER;

    Generate();
    glBufferData(Target, sizeof(Indices), Indices, GL_STATIC_DRAW);
}

