#ifndef ASSIMPLOADER_H
#define ASSIMPLOADER_H

#include "Framework.h"
#include "GL/BufferObjectData.h"
#include "Mesh.h"
#include "SceneMesh.h"
#include "SceneNode.h"
#include "GL/VertexArrayObject.h"

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)

class AssimpLoader
{
private:
    Importer importer;
    const aiScene *scene;
    float scaleFactor;
    vector<Mesh> MeshArray;
    SceneMesh *GLSceneMeshes;
    map<string, GLuint> textureIdMap;

    void constructScene();
    SceneMesh * constructSceneHelper(aiNode * node);
    void get_bounding_box_for_node (const struct aiNode* nd,
            struct aiVector3D* min,
            struct aiVector3D* max);
    void get_bounding_box (struct aiVector3D* min,
                           struct aiVector3D* max);

    Mesh getMesh(int index);
public:
    AssimpLoader();
    bool Import3DFromFile( const std::string& pFile);
    void setScaleFactor(float scale);
    void genVAOsAndUniformBuffer();
    vector<Mesh> getMeshes();
    SceneMesh * getScene();
    int LoadGLTextures();
};

#endif // ASSIMPLOADER_H
