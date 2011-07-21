#include "GLScene.h"

GLScene::GLScene()
{
    Root = NULL;
}

GLScene::GLScene(SceneNode *scene)
{
    SceneCamera* temp = dynamic_cast<SceneCamera*>(scene);
    if( temp != 0)
        Cameras.push_back( (SceneCamera*)scene);
    Root = scene;
}

void GLScene::AddChild(SceneNode *node)
{
    SceneCamera* temp = dynamic_cast<SceneCamera*>(node);
    if( node != 0)
        Cameras.push_back( (SceneCamera*)node);

    if(Root)
        Root->AddChild(node);
    else
        Root = node;
}

void GLScene::Draw()
{
    mat4 identity = mat4(1.0);
    Matrices::PushMatrix(MODEL_STACK, identity);

    if(Root)
        Root->Draw();
    else
        cerr << "Failed to draw scene. Root node is NULL" << endl;

    Matrices::PopMatrix(MODEL_STACK);
}
