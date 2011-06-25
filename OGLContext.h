#ifndef OGLCONTEXT_H
#define OGLCONTEXT_H

#include "Framework.h"
#include "OBJLoader.h"
#include "ShaderProgram.h"
#include "Vertex.h"
#include "VertexArrayObject.h"

class OGLContext
{
private:
    unsigned frameCount;
    float lastFrame;

    VertexArrayObject *VAO;
    ShaderProgram *sp;

    void Cleanup(void);
    void RenderFunction();
public:
    OGLContext();
    void Render();

    static glm::mat4 Projection;
    static glm::mat4 View;
};

#endif // OGLCONTEXT_H
