#ifndef INDEXBUFFEROBJECT_H
#define INDEXBUFFEROBJECT_H

#include "BufferObject.h"

class IndexBufferObject : public BufferObject
{
private:
    GLuint NumElements;
public:
    IndexBufferObject();
    IndexBufferObject(const vector<GLuint> Indices);
    void Draw();
    GLuint GetSize();
};

#endif // INDEXBUFFEROBJECT_H
