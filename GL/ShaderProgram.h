#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "Shader.h"
#include "FragmentShader.h"
#include "Lights.h"
#include "ShaderMaterial.h"
#include "UniformBufferObject.h"
#include "VertexShader.h"

class ShaderProgram
{
private:
    GLuint ID;
    GLuint uniformLoc;
    FragmentShader *fs;
    VertexShader *vs;
    ShaderMaterial material;
    UniformBufferObject UBO;
public:
    ShaderProgram();
    ~ShaderProgram();
    ShaderProgram(string vertexShaderFile, string fragmentShaderFile);
//    ShaderProgram(string xmlShader);
    void Bind();
    void Link();
    void SetMaterial(ShaderMaterial _material);
    void Unbind();

    Matrices mat;
};

#endif // SHADERPROGRAM_H
