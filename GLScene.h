#ifndef GLSCENE_H
#define GLSCENE_H

#include "Framework.h"
#include "SceneCamera.h"
#include "SceneNode.h"
#include "Matrices.h"

class GLScene
{
private:

public:
    GLScene();
    GLScene(SceneNode *scene);
    void AddChild(SceneNode *node);
    void Draw();

    SceneNode* Root;
    vector<SceneCamera*> Cameras;
};

#endif // GLSCENE_H
