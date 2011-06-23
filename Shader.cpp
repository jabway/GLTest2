#include "Shader.h"

Shader::Shader()
{
}

Shader::~Shader()
{
    glDeleteShader(ID);
}

void Shader::Compile(std::string Filename)
{
    ID = glCreateShader(type);

    std::string ShaderCode;
    std::ifstream ShaderStream;

    // Load shader source code
    ShaderStream.open(Filename.c_str(), std::ios::in );

    if(ShaderStream.is_open() )
    {
        std::string line = "";
        while(getline(ShaderStream, line))
        {
            ShaderCode += line + "\n";
        }
        ShaderStream.close();
    }
    else
        cerr << "Could not open shader \"" << Filename << "\"" << endl;

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Shader
    cout << "Compiling shader : " << Filename << endl;
    char const * SourcePointer = ShaderCode.c_str();
    glShaderSource(ID, 1, &SourcePointer , NULL);
    glCompileShader(ID);

    // Check Shader
    glGetShaderiv(ID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> ShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(ID, InfoLogLength, NULL, &ShaderErrorMessage[0]);
    string t(ShaderErrorMessage.begin(), ShaderErrorMessage.end() );
    cout << t << endl;

}

void Shader::Attach(GLuint programID)
{
    glAttachShader(programID, ID);
}

void Shader::Detach(GLuint programID)
{
    glDetachShader(programID, ID);
}
