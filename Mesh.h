#ifndef MESH_H
#define MESH_H

#include "Framework.h"
#include "GL/ShaderMaterial.h"
#include "GL/ShaderProgram.h"
#include "GL/VertexArrayObject.h"

class Mesh
{
private:
    VertexArrayObject* VAO;
    ShaderMaterial mat;
    ShaderProgram* sp;
    mat4 Model;

    int numFaces;
public:
    Mesh();

    void AttachShader();
    void AttachShader(string Vert, string Frag);
    void AttachVAO(VertexArrayObject* _VAO);
    void Draw();
    mat4 GetModelMatrix();
    void SetMaterial(ShaderMaterial _mat);
    void SetModelMatrix(mat4 _mat);

    vector<GLuint> texIndices;
    GLuint uniformBlockIndex;
    string mName;
};

#endif // MESH_H
