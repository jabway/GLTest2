#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject()
{
//    float o_st = 0.577350269f;
//    Vertex Vertices[] =
//    {
//        //Top
//        { { 1.0f, 1.0f, 1.0f, 1.0f }, { o_st, o_st, o_st}, { 1.0f, 1.0f, 1.0f, 1.0f } },
//        { { 1.0f, 1.0f, -1.0f, 1.0f }, { o_st, o_st, -o_st }, { 1.0f, 1.0f, -1.0f, 1.0f } },
//        { { -1.0f, 1.0f, -1.0f, 1.0f }, { -o_st, o_st, -o_st }, { -1.0f, 1.0f, -1.0f, 1.0f } },
//        { { -1.0f, 1.0f, 1.0f, 1.0f }, { -o_st, o_st, o_st }, { -1.0f, 1.0f, 1.0f, 1.0f } },
//        //Bottom
//        { { 1.0f, -1.0f, 1.0f, 1.0f }, { o_st, -o_st, o_st }, { 1.0f, -1.0f, 1.0f, 1.0f } },
//        { { 1.0f, -1.0f, -1.0f, 1.0f }, { o_st, -o_st, -o_st }, { 1.0f, -1.0f, -1.0f, 1.0f } },
//        { { -1.0f, -1.0f, -1.0f, 1.0f }, {- o_st, -o_st, -o_st }, { -1.0f, -1.0f, -1.0f, 1.0f } },
//        { { -1.0f, -1.0f, 1.0f, 1.0f }, { -o_st, -o_st, o_st }, { -1.0f, -1.0f, 1.0f, 1.0f } }
//    };

//    GLuint Indices[] = {
//        // Top
//        0, 1, 2,
//        0, 2, 3,
//        // Bottom
//        4, 5, 6,
//        4, 7, 6,
//        // Left
//        3, 2, 6,
//        3, 7, 6,
//        // Right
//        0, 5, 1,
//        0, 4, 5,
//        // Front
//        0, 3, 4,
//        3, 7, 4,
//        // Back
//        1, 6, 2,
//        1, 5, 6
//    };

//    Vertex * Vertices = NULL;
//    int vertSize = 0;

//    GLuint * Indices = NULL;
//    int indexSize = 0;

    OBJLoader OBJ("dragon.obj");

    vector<Vertex> Vertices = OBJ.GetVertices();
    vector<GLuint> Indices = OBJ.GetIndices();

    //OBJ.Store(Vertices, Indices);


    GLenum ErrorCheckValue = glGetError();

    glGenVertexArrays(1, &VaoId);
    glBindVertexArray(VaoId);

    VBO = new VertexBufferObject(Vertices);

    // Create IBO
    IBO = new IndexBufferObject(Indices);

    glBindVertexArray(0);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        fprintf(
            stderr,
            "ERROR: Could not create a VBO: %s \n",
            gluErrorString(ErrorCheckValue)
        );

        exit(-1);
    }
}

VertexArrayObject::~VertexArrayObject()
{
    GLenum ErrorCheckValue = glGetError();

    if(VBO)
        delete VBO;

    if(IBO)
        delete IBO;

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VaoId);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        fprintf(
            stderr,
            "ERROR: Could not destroy the VBO: %s \n",
            gluErrorString(ErrorCheckValue)
        );

        exit(-1);
    }
}

void VertexArrayObject::Draw()
{
    glBindVertexArray(VaoId);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    IBO->Draw();

    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}
