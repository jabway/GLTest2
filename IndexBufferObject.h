#ifndef INDEXBUFFEROBJECT_H
#define INDEXBUFFEROBJECT_H

#include "BufferObject.h"

class IndexBufferObject : public BufferObject
{
private:
    GLuint VboId;
public:
    IndexBufferObject();
};

#endif // INDEXBUFFEROBJECT_H
