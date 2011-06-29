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

void VertexArrayObject::BindBuffers(BufferObjectData& Bod,
                                    const vector<GLuint> &Indices)
{
    vector<Attribute>& VecAttribs = Bod.GetAttributes();

    //Bind VAO to add buffers
    glBindVertexArray(VaoId);
    VertexBufferObject* tempVBO = NULL;

    for(int i = 0; i < VecAttribs.size(); i++)
    {
        tempVBO = new VertexBufferObject(VecAttribs[i].Data,
                                         VecAttribs[i].CountPerIndex,
                                         VecAttribs[i].AttribLocation);

        if(tempVBO != NULL)
            MaxAttribs++;
    }

    IBO = new IndexBufferObject(Indices);

    glBindVertexArray(0);
}

void VertexArrayObject::Draw()
{
    glBindVertexArray(VaoId);

    for(int i = 0; i < MaxAttribs; i++)
    {
        glEnableVertexAttribArray(i);
    }
    sp->Use();

    IBO->Draw();

    sp->Disable();

    for(int i = MaxAttribs - 1; i >= 0; i--)
    {
        glDisableVertexAttribArray(i);
    }

    glBindVertexArray(0);
}


void VertexArrayObject::AttachShader(string vert, string frag)
{
    sp = new ShaderProgram(vert, frag);
    if(!sp)
    {
        cerr << "Could not create shader program" << endl;
        exit(-1);
    }
}

void VertexArrayObject::AddModelMatrix(mat4 _model)
{
    if(sp)
        sp->SetModelMatrix(_model);
}
