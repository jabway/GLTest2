#include "SceneCamera.h"

SceneCamera::SceneCamera()
{
//    FBO = FrameBufferObject(1280, 960);
}

void SceneCamera::Draw()
{
    Matrices::PushMatrix(PROJECTION_STACK, Projection);
    Matrices::PushMatrix(VIEW_STACK, View);

    //FBO.Bind();

    SceneNode::Draw();

    //FBO.Unbind();

    Matrices::PopMatrix(PROJECTION_STACK);
    Matrices::PopMatrix(VIEW_STACK);
}

void SceneCamera::Rotate(vec3 rotVector)
{
    // Rotate view matrix
    mat4 rotMatrix = mat4(1.0);

//    View = gtc::matrix_transform::rotate(View, rotVector.x, -Axes[1]);
//    View = gtc::matrix_transform::rotate(View, rotVector.y, -cross(Axes[2], Axes[1]));
//    View = gtc::matrix_transform::rotate(View, rotVector.z, -Axes[2]);
    rotMatrix = gtc::matrix_transform::rotate(rotMatrix, rotVector.x, vec3( 0, -1, 0));
    rotMatrix = gtc::matrix_transform::rotate(rotMatrix, rotVector.y, vec3( -1, 0, 0));
    rotMatrix = gtc::matrix_transform::rotate(rotMatrix, rotVector.z, vec3(0, 0, -1));

    View *= rotMatrix;

    // Rotate vectors
    Axes[1] = rotateX(Axes[1], -rotVector.y);
    Axes[1] = rotateY(Axes[1], -rotVector.z);
    Axes[1] = rotateZ(Axes[1], -rotVector.x);

//    Location = rotateX( Location, rotVector.x);
//    Location = rotateY( Location, rotVector.y);
//    Location = rotateZ( Location, rotVector.z);

//    Focus = rotateX( Focus, rotVector.x);
//    Focus = rotateY( Focus, rotVector.y);
//    Focus = rotateZ( Focus, rotVector.z);

//    Forward = normalize(Focus - Location);

    Axes[2] = rotateX(Axes[2], -rotVector.y);
    Axes[2] = rotateY(Axes[2], -rotVector.z);
    Axes[2] = rotateZ(Axes[2], -rotVector.x);
}

void SceneCamera::setPerspective(float fov, float aspect, float near, float far)
{
    Projection = gtc::matrix_transform::perspective(fov, aspect, near, far);
}

void SceneCamera::setView(vec3 cameraLocation, vec3 focus, vec3 upVector)
{
    View = gtc::matrix_transform::lookAt(cameraLocation, focus, upVector);
    Focus = focus;
    Location = cameraLocation;

    Forward = normalize(Focus - Location);
    Up = normalize(upVector);

    Axes[0] = normalize(Focus + cross(Forward, Up));
    Axes[1] = normalize(Focus + Up);
    Axes[2] = normalize(Focus + Forward);
}

void SceneCamera::Zoom(float zFactor)
{
    if(zFactor > 0.0f || zFactor < 0.0f)
    View = gtc::matrix_transform::translate(View, (1 - 1/zFactor) * Axes[2]);
}
