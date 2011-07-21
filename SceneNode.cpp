#include "SceneNode.h"

double SceneNode::DeltaTime;
double SceneNode::CurrentTime;

SceneNode::SceneNode()
{
    Parent = NULL;
}

void SceneNode::AddChild(SceneNode* node)
{
    node->Parent = this;
    Children.push_back(node);
}

void SceneNode::Draw()
{
    for(unsigned i = 0; i < Children.size(); i++)
    {
        SceneNode* temp = Children[i];

        if(temp)
            temp->Draw();
    }
}

void SceneNode::SetTime(double _time)
{
    DeltaTime = _time - CurrentTime;
    CurrentTime = _time;
}
