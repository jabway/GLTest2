#include "BufferObjectData.h"

BufferObjectData::BufferObjectData()
{
}

void BufferObjectData::AddAttribute(vector<GLfloat> &Data, int CPI,
                                    int AttribLocation)
{
    Attribute att = { Data, CPI, AttribLocation};
    Attribs.push_back(att);
}

vector<Attribute>& BufferObjectData::GetAttributes()
{
    return Attribs;
}
