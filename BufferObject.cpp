#include "BufferObject.h"

BufferObject::BufferObject() : Target(GL_ARRAY_BUFFER)
{
    Generate();
}

void BufferObject::Generate()
{
    GLenum ErrorCheckValue = glGetError();

    glGenBuffers(1, &BufferId);
    glBindBuffer(Target, BufferId);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        fprintf(
            stderr,
            "ERROR: Could not create a BO: %s \n",
            gluErrorString(ErrorCheckValue)
        );

        exit(-1);
    }
}

BufferObject::~BufferObject()
{
    GLenum ErrorCheckValue = glGetError();

    glBindBuffer(Target, 0);
    glDeleteBuffers(1, &BufferId);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        fprintf(
            stderr,
            "ERROR: Could not destroy the BO: %s \n",
            gluErrorString(ErrorCheckValue)
        );

        exit(-1);
    }
}
