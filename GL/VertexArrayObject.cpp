#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject()
{
    MaxAttribs = 0;

    GLenum ErrorCheckValue = glGetError();

    glGenVertexArrays(1, &VaoId);
    glBindVertexArray(VaoId);

    glBindVertexArray(0);

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

void VertexArrayObject::BindBuffers(BufferObjectData& Bod, const vector<GLuint> &Indices)
{
    vector<Attribute>& VecAttribs = Bod.GetAttributes();

    //Bind VAO to add buffers
    glBindVertexArray(VaoId);
    VertexBufferObject* tempVBO = NULL;

    for(unsigned i = 0; i < VecAttribs.size(); i++)
    {
        tempVBO = new VertexBufferObject(VecAttribs[i].Data);

        if(tempVBO != NULL)
        {
            glVertexArrayVertexAttribOffsetEXT(VaoId, tempVBO->BufferId, VecAttribs[i].AttribLocation,
                                               VecAttribs[i].CountPerIndex, GL_FLOAT, GL_FALSE, 0, 0 );

            MaxAttribs++;
        }

        tempVBO->Unbind();
    }

    IBO = new IndexBufferObject(Indices);

    // Unbind VAO
    glBindVertexArray(0);
}

void VertexArrayObject::Draw()
{
    // Bind Vao before drawing
    glBindVertexArray(VaoId);

    // Enable vertex attributes
    for(int i = 0; i < MaxAttribs; i++)
    {
        glEnableVertexArrayAttribEXT(VaoId, i);
    }


    // Draw contents of Vao
    IBO->Draw();

    // Disable vertex attributes
    for(int i = MaxAttribs - 1; i >= 0; i--)
    {
         glDisableVertexArrayAttribEXT(VaoId, i);
    }

    // Unbind Vao
    glBindVertexArray(0);
}

