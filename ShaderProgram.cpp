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

ShaderProgram::ShaderProgram(string vertexShaderFile,
                             string fragmentShaderFile)
{
    ID = glCreateProgram();

    vs = new VertexShader(vertexShaderFile);
    fs = new FragmentShader(fragmentShaderFile);

    setPerspective(45.0f, 4.0f/3.0f, 0.1f, 100.0f);
    setView(glm::vec3(-9,15,20), // Camera is at (4,3,3), in World Space
            glm::vec3(0,0,0), // and looks at the origin
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down
            );

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

void ShaderProgram::setPerspective(float fov, float aspect, float near,
                                   float far)
{
    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    Projection = glm::gtc::matrix_transform::perspective(fov, aspect, near, far);
}

void ShaderProgram::setView(glm::vec3 cameraLocation, glm::vec3 focus,
                            glm::vec3 upVector)
{
    // Camera matrix
    View       = glm::gtc::matrix_transform::lookAt(
        cameraLocation, // Camera is at (4,3,3), in World Space
        focus, // and looks at the origin
        upVector  // Head is up (set to 0,-1,0 to look upside-down)
    );

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
        cerr << t << endl;


    }
    else
    {
        cerr << "Attempted to link invalid shader program" << endl;
        return;
    }


}

void ShaderProgram::Use()
{
    glUseProgram(ID);

    // Model matrix : an identity matrix (model will be at the origin)
    Model      = glm::mat4(1.0f);  // Changes for each model !
    // Our ModelViewProjection : multiplication of our 3 matrices
    //glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around

    // Get a handle for our "MVP" uniform.
    // Only at initialisation time.
    GLuint ModelID = 0;
    ModelID = glGetUniformLocation(ID, "model");

    // Only at initialisation time.
    GLuint ViewID = 0;
    ViewID = glGetUniformLocation(ID, "view");
    // Only at initialisation time.
    GLuint ProjID = 0;
    ProjID = glGetUniformLocation(ID, "projection");

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    glUniformMatrix4fv(ModelID, 1, GL_FALSE, &Model[0][0]);
    glUniformMatrix4fv(ViewID, 1, GL_FALSE, &View[0][0]);
    glUniformMatrix4fv(ProjID, 1, GL_FALSE, &Projection[0][0]);
}

void ShaderProgram::Disable()
{
    glUseProgram(0);
}
