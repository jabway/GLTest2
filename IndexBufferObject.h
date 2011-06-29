#ifndef INDEXBUFFEROBJECT_H
#define INDEXBUFFEROBJECT_H

#include "BufferObject.h"

class IndexBufferObject : public BufferObject
{
private:
    GLuint BoId;
    GLuint NumElements;
public:
    IndexBufferObject();
    IndexBufferObject(const vector<GLuint> Indices);
    void Draw();
};

#endif // INDEXBUFFEROBJECT_H
