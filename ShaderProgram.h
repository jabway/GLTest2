#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "Shader.h"
#include "FragmentShader.h"
#include "VertexShader.h"

class ShaderProgram
{
private:
    GLuint ID;
    FragmentShader *fs;
    VertexShader *vs;
    glm::mat4 Projection;
    glm::mat4 View;
    glm::mat4 Model;
public:
    ShaderProgram();
    ~ShaderProgram();
    ShaderProgram(string vertexShaderFile, string fragmentShaderFile);
//    ShaderProgram(string xmlShader);
    void setPerspective(float fov, float aspect, float near, float far);
    void setView(glm::vec3 cameraLocation, glm::vec3 focus, glm::vec3 upVector);
    void Link();
    void Use();


};

#endif // SHADERPROGRAM_H
