#include "Mesh.h"

Mesh::Mesh()
{
    sp = NULL;
}

void Mesh::AttachShader()
{
    // Set shader
    sp = new ShaderProgram("shader.vert", "shader.frag");
    if(!sp)
    {
        cerr << "Could not create shader program" << endl;
    }

}

void Mesh::AttachShader(string Vert, string Frag)
{
    // Set shader
    sp = new ShaderProgram(Vert, Frag);
    if(!sp)
    {
        cerr << "Could not create shader program with sources \"" << Vert
             << "\" and \"" << Frag << "\"" << endl;
        AttachShader();
    }
}

void Mesh::AttachVAO(VertexArrayObject *_VAO)
{
    VAO = _VAO;
}

void Mesh::Draw()
{

    int s = texIndices.size();

    if(s > 0)
    {
        for(int i = 0; i < texIndices.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, texIndices[i]);
        }
    }

    if(sp != NULL)
        sp->Bind();

    if(VAO)
        VAO->Draw();

    if(sp != NULL)
        sp->Unbind();

    if(s > 0)
    {
        for(int i = 0; i < texIndices.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
}

mat4 Mesh::GetModelMatrix()
{
    return Model;
}

void Mesh::SetMaterial(ShaderMaterial _mat)
{
    mat = _mat;
    if(sp)
        sp->SetMaterial(mat);
}

void Mesh::SetModelMatrix(mat4 _mMatrix)
{
    Model = _mMatrix;

}
