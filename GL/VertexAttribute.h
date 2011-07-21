#ifndef VERTEXATTRIBUTE_H
#define VERTEXATTRIBUTE_H

#include "Framework.h"

template <class T>
class VertexAttribute
{
public:
    VertexAttribute();

    vector<T> Data;
    int AttribIndex;
};

#endif // VERTEXATTRIBUTE_H
