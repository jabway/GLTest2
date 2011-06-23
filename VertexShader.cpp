#include "VertexShader.h"

VertexShader::VertexShader()
{
    type = GL_VERTEX_SHADER;
}

VertexShader::VertexShader(string Filename)
{
    type = GL_VERTEX_SHADER;

    Compile(Filename);
}
