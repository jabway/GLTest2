#include "UniformBufferObject.h"

UniformBufferObject::UniformBufferObject()
{
    Target = GL_UNIFORM_BUFFER;

    Generate();
}

void UniformBufferObject::BufferData(void *data, GLuint size)
{
    // Store buffer data
    glNamedBufferDataEXT(BufferId, size, data, GL_STATIC_DRAW);
}

void UniformBufferObject::Bind(GLuint index, GLuint offset, GLuint size)
{
    glBindBufferRange(Target, index, BufferId, offset, size);
}
