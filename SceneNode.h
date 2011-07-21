#ifndef SCENENODE_H
#define SCENENODE_H

#include "Framework.h"
#include "Matrices.h"

class SceneNode
{
private:
    static double DeltaTime;
    static double CurrentTime;
public:
    SceneNode();

    void AddChild(SceneNode* node);
    virtual void Draw();
    static void SetTime(double _time);

    vector<SceneNode*> Children;
    SceneNode* Parent;
};

#endif // SCENENODE_H
