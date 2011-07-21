#ifndef VERTEXFORMAT_H
#define VERTEXFORMAT_H

#include "VertexAttribute.h"

#define HAS_BONES 0x00000001
#define HAS_NORMALS (HAS_BONES) << 1
#define HAS_POSITIONS (HAS_NORMALS) << 1
#define HAS_TANGENTS_AND_BITANGENTS (HAS_POSITIONS) << 1
#define HAS_TEXTURE_COORDS (HAS_TANGENTS_AND_BITANGENTS) << 1
#define HAS_VERTEX_COLORS (HAS_TEXTURE_COORDS) << 1

class VertexFormat
{
public:
    vector< VertexAttribute<float> > Data;
    vector<float> padding;
};

//class VT
//{
//public:
//    VertexAttribute<float> Position;
//    VertexAttribute<float> Position;
//    float padding[3];
//};

//class VNT
//{
//public:
//    float x, y, z;
//    float nx, ny, nz;
//    float s0, t0;
//};



#endif // VERTEXFORMAT_H
