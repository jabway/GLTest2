#include "Matrices.h"

mat4 Matrices::Model;
mat4 Matrices::Projection;
mat4 Matrices::View;
stack<mat4> Matrices::ModelStack = stack<mat4>();
stack<mat4> Matrices::ProjectionStack = stack<mat4>();
stack<mat4> Matrices::ViewStack = stack<mat4>();

Matrices::Matrices()
{
//    ModelStack = stack<mat4>();
//    ProjectionStack = stack<mat4>();
//    ViewStack = stack<mat4>();
}

void Matrices::PopMatrix(stackType type)
{
    switch(type)
    {
    case MODEL_STACK:
        if(!ModelStack.empty())
        {
            ModelStack.pop();

            if(!ModelStack.empty())
                Model = ModelStack.top();
        }
        break;
    case PROJECTION_STACK:
        if(!ProjectionStack.empty())
        {
            ProjectionStack.pop();

            if(!ProjectionStack.empty())
                Projection = ProjectionStack.top();
        }
        break;
    case VIEW_STACK:
        if(!ViewStack.empty())
        {
            ViewStack.pop();

            if(!ViewStack.empty())
                View = ViewStack.top();
        }
        break;
    default:
        break;
    }
}

void Matrices::PushMatrix(stackType type, mat4 data)
{
    switch(type)
    {
    case MODEL_STACK:
        if(!ModelStack.empty())
        {
            Model += data;
        }
        else
            Model = data;
        ModelStack.push(Model);
        break;
    case PROJECTION_STACK:
        if(!ProjectionStack.empty())
        {
            Projection += data;
        }
        else
            Projection = data;
        ProjectionStack.push(Projection);
        break;
    case VIEW_STACK:
        if(!ViewStack.empty())
        {
            View += data;
        }
        else
            View = data;
        ViewStack.push(View);
        break;
    default:
        break;
    }
}

