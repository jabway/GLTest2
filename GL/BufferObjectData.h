#ifndef BUFFEROBJECTDATA_H
#define BUFFEROBJECTDATA_H

#include "Framework.h"

typedef struct
{
    vector<GLfloat> Data;
    int CountPerIndex;
    int AttribLocation;
} Attribute;

class BufferObjectData
{
private:
    vector<Attribute> Attribs;
public:
    BufferObjectData();
    void AddAttribute(vector<GLfloat>& Data, int CPI,
                      int AttribLocation);
    vector<Attribute>& GetAttributes();
};

#endif // BUFFEROBJECTDATA_H
