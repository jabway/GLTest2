#ifndef SCENECAMERA_H
#define SCENECAMERA_H

#include "GL/FrameBufferObject.h"
#include "SceneNode.h"

class SceneCamera : public SceneNode
{
private:
    vec3 Forward, Up, Location, Focus;
    vec3 Axes[3];
public:
    SceneCamera();
    void Draw();
    void Rotate(vec3 rotVector);
    void setPerspective(float fov, float aspect, float near, float far);
    void setView(vec3 cameraLocation, vec3 focus, vec3 upVector);
    void Zoom(float zFactor);

    string Name;
    mat4 Projection, View;
//    FrameBufferObject FBO;
};

#endif // SCENECAMERA_H
