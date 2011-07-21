#include "IndexBufferObject.h"

IndexBufferObject::IndexBufferObject()
{


        GLuint Indices[] = {
            // Top
            0, 1, 2,
            0, 2, 3,
            // Bottom
            4, 6, 5,
            4, 7, 6,
            // Left
            3, 2, 6,
            3, 6, 7,
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
    Bind();
    glNamedBufferDataEXT(BufferId, sizeof(Indices), Indices, GL_STATIC_DRAW);
    //glBufferData(Target, sizeof(Indices), Indices, GL_STATIC_DRAW);

    Unbind ();
}


IndexBufferObject::IndexBufferObject(const vector<GLuint> Indices)
{
    Target = GL_ELEMENT_ARRAY_BUFFER;
    NumElements = Indices.size();

    Generate();
    Bind();
    glNamedBufferDataEXT(BufferId, NumElements * sizeof(GLuint), &Indices[0], GL_STATIC_DRAW);
    //glBufferData(Target, NumElements * sizeof(GLuint), &Indices[0], GL_STATIC_DRAW);

    Unbind ();
}


GLuint IndexBufferObject::GetSize()
{
    return NumElements;
}

void IndexBufferObject::Draw()
{
    Bind();
    glDrawElements(GL_TRIANGLES, NumElements, GL_UNSIGNED_INT, 0);
    Unbind();
}
