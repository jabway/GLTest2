#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
    ID = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
    vs->Detach(ID);
    fs->Detach(ID);

    if(fs)
        delete fs;

    if(vs)
        delete vs;

    glDeleteProgram(ID);
}

ShaderProgram::ShaderProgram(string vertexShaderFile, string fragmentShaderFile)
{
    ID = glCreateProgram();

    vs = new VertexShader(vertexShaderFile);
    fs = new FragmentShader(fragmentShaderFile);

    if(!vs || !fs){
        throw "Shaders " + vertexShaderFile + " and " + fragmentShaderFile + " not found.";
        return;
    }

    Link();
}

//ShaderProgram::ShaderProgram(string xmlShader)
//{
//    TiXmlDocument xmlShaderDoc(xmlShader);
//    if (!xmlShaderDoc.LoadFile() )
//    {
//        cerr << "Failed to load XML shader \"" << xmlShader << "\""  << endl;
//        return;
//    }

//    TiXmlHandle hShaderDoc( &xmlShaderDoc );
//    TiXmlElement *pElem;
//    TiXmlHandle hRoot(0);
//}


void ShaderProgram::Bind()
{
    glUseProgram(ID);

    // Get a handle for our matrix uniforms.
    // Only at initialisation time.
    GLuint ModelID = 0;
    ModelID = glGetUniformLocation(ID, "model");

    // Only at initialisation time.
    GLuint ViewID = 0;
    ViewID = glGetUniformLocation(ID, "view");
    // Only at initialisation time.
    GLuint ProjID = 0;
    ProjID = glGetUniformLocation(ID, "projection");
    // Only at initialisation time.
    GLuint LightID = 0;
    LightID = glGetUniformLocation(ID, "light");


    // Bind active textures to GLSL samplers
    for(int i = 0; i < material.texCount; i++)
    {
        stringstream ss;
        ss << "tex" << i;
        string texUniform = ss.str();
        GLuint texID = glGetUniformLocation(ID, texUniform.c_str());
        glProgramUniform1iEXT(ID, texID, i);
    }

    // Send our transformation to the currently bound shader
    glProgramUniformMatrix4fvEXT(ID, ModelID, 1, GL_FALSE, &Matrices::Model[0][0]);
    glProgramUniformMatrix4fvEXT(ID, ViewID, 1, GL_FALSE, &Matrices::View[0][0]);
    glProgramUniformMatrix4fvEXT(ID, ProjID, 1, GL_FALSE, &Matrices::Projection[0][0] );


    //glUniform3f(LightID, Lights::LightPos.x, Lights::LightPos.y, Lights::LightPos.z);
    glProgramUniform3fEXT(ID, LightID, Lights::LightPos.x, Lights::LightPos.y, Lights::LightPos.z);
    UBO.Bind(uniformLoc,0, sizeof(material));
}


void ShaderProgram::Link()
{
    if( vs  && fs )
    {
        //Attach shaders to program
        vs->Attach(ID);
        fs->Attach(ID);

        glLinkProgram(ID);

        GLint Result = GL_FALSE;
        int InfoLogLength;

        // Check the program
        glGetProgramiv(ID, GL_LINK_STATUS, &Result);
        glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        std::vector<char> ProgramErrorMessage( InfoLogLength);
        glGetProgramInfoLog(ID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        string t(ProgramErrorMessage.begin(), ProgramErrorMessage.end() );

        if(t.length() > 1)
            cerr << t << endl;

        // Uniform block index
        uniformLoc = 2;
        GLuint blockIndex = glGetUniformBlockIndex(ID, "Material");
        glUniformBlockBinding(ID, blockIndex, uniformLoc);


    }
    else
    {
        cerr << "Attempted to link invalid shader program" << endl;
        return;
    }


}



void ShaderProgram::SetMaterial(ShaderMaterial _material)
{
    material = _material;
    UBO.BufferData((void*)&material, sizeof(material));

}


void ShaderProgram::Unbind()
{
    glUseProgram(0);
}

void ShaderProgram::Uniformi(int ref, std::initializer_list<int> args)
{
    vector<int> list(args);

    switch(list.size()){
    case 1:
        glUniform1i(ref, list[0]);
        break;
    case 2:
        glUniform2i(ref, list[0], list[1]);
        break;
    case 3:
        glUniform3i(ref, list[0], list[1], list[2]);
        break;
    case 4:
        glUniform4i(ref, list[0], list[1], list[2], list[3]);
        break;
    default:
        throw "glUniformXi called with invalid number of arguments.";
        break;
   }
}

 void ShaderProgram::Uniformf(int ref, std::initializer_list<float> args)
 {
     vector<float> list(args);

     switch(list.size()){
     case 1:
         glUniform1f(ref, list[0]);
         break;
     case 2:
         glUniform2f(ref, list[0], list[1]);
         break;
     case 3:
         glUniform3f(ref, list[0], list[1], list[2]);
         break;
     case 4:
         glUniform4f(ref, list[0], list[1], list[2], list[3]);
         break;
     default:
         throw "glUniformXf called with invalid number of arguments.";
         break;
    }
 }
