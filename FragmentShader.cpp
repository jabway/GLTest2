#include "FragmentShader.h"

FragmentShader::FragmentShader()
{
    type = GL_FRAGMENT_SHADER;
}
FragmentShader::FragmentShader(string Filename)
{
    type = GL_FRAGMENT_SHADER;

    Compile(Filename);
}
