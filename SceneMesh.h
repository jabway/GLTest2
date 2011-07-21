#ifndef SCENEMESH_H
#define SCENEMESH_H

#include "Mesh.h"
#include "SceneNode.h"

class SceneMesh : public SceneNode
{
private:
    mat4 Model;
public:
    SceneMesh();

    void AddMesh(Mesh _mesh);
    void Draw();
    void SetModelMatrix(mat4 _model);

    vector<Mesh> GLMeshes;
};

#endif // SCENEMESH_H
