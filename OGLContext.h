#ifndef OGLCONTEXT_H
#define OGLCONTEXT_H

#include "AssimpLoader.h"
#include "Framework.h"
#include "Lights.h"
#include "BufferObjectData.h"
#include "Matrices.h"
#include "OBJLoader.h"
#include "ShaderProgram.h"
#include "Vertex.h"
#include "VertexArrayObject.h"

class OGLContext
{
private:
    unsigned FrameCount;
    float LastFrame;
    float CurTime;
    float LastTime;
    float DeltaTime;
    vec3 CameraPos;
    vec3 CameraFocus;
    int MousePos[2];
    int DeltaPos[2];
    int MouseScroll;
    bool MouseDown;
    bool LightDir;
    float LightTheta;

    vector<VertexArrayObject*> VAO;
    ShaderProgram *sp;

    void Cleanup(void);
    void RenderFunction();
public:
    OGLContext();
    void Render();
    void setPerspective(float fov, float aspect, float near,
                        float far);
    void setView(glm::vec3 cameraLocation, glm::vec3 focus,
                 glm::vec3 upVector);
    void GLFWCALL Resize(int width, int height);
    void KeyCallback(int key, int action);
    void MouseButtonCallback(int button, int action);
    void MousePosCallback(int x, int y);
    void MouseScrollCallback(int scroll);

    Matrices mat;
};

#endif // OGLCONTEXT_H
