#ifndef MATRICES_H
#define MATRICES_H
#include "Framework.h"

enum stackType
{
    MODEL_STACK,
    PROJECTION_STACK,
    VIEW_STACK
};

class Matrices
{

private:
    static stack<mat4> ModelStack;
    static stack<mat4> ProjectionStack;
    static stack<mat4> ViewStack;
public:
    Matrices();
    static void PopMatrix(stackType type);
    static void PushMatrix(stackType type, mat4 data);

    static mat4 Model;
    static mat4 Projection;
    static mat4 View;


};


#endif // MATRICES_H
