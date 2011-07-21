#include "SceneMesh.h"

SceneMesh::SceneMesh()
{
    Model = mat4(1.0);
}

void SceneMesh::AddMesh(Mesh _mesh)
{
    GLMeshes.push_back(_mesh);
}

void SceneMesh::Draw()
{
    Matrices::PushMatrix(MODEL_STACK, Model);

    SceneNode::Draw();

    for(unsigned i = 0; i < GLMeshes.size(); i++)
    {
        GLMeshes[i].Draw();
    }

    Matrices::PopMatrix(MODEL_STACK);
}

void SceneMesh::SetModelMatrix(mat4 _model)
{
    Model = _model;
}
