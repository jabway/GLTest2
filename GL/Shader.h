#ifndef SHADER_H
#define SHADER_H

#include "Framework.h"
#include "Matrices.h"

class Shader
{
protected:
    GLuint ID;
    GLenum type;
public:
    Shader();
    ~Shader();
    void Compile(std::string _filename);
    void Attach(GLuint programID);
    void Detach(GLuint programID);

};

#endif // SHADER_H
