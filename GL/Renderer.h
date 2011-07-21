#ifndef RENDERER_H
#define RENDERER_H

#include "AssimpLoader.h"
#include "Framework.h"
#include "Lights.h"
#include "BufferObjectData.h"
#include "Matrices.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Vertex.h"
#include "VertexArrayObject.h"

class Renderer
{
private:
    unsigned FrameCount;
    float LastFrame;
    float CurTime;
    float LastTime;
    float DeltaTime;
    mat3 Axes;      //World Axes
    vec3 CameraPos;
    vec3 CameraFocus;
    vec3 UpVector;
    int MousePos[2];
    int DeltaPos[2];
    int MouseScroll;
    bool MouseDown;
    bool LightDir;
    float LightTheta;

    vector<Mesh> MeshArray;
    SceneMesh * scene;

    int width;         // Width of the window
    int height;        // Height of the window

    GLuint fbo;        // The frame buffer object
    GLuint fboDepth;   // The depth buffer for the frame buffer object
    GLuint fboTexture; // The handle for the texture we draw to in the framebuffer

    GLenum* windowBuff;
    GLenum* fboBuff;

    void Cleanup(void);
    void RenderFunction();
public:
    Renderer();
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

#endif // RENDERER_H
