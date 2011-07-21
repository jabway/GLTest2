#ifndef SHADERMATERIAL_H
#define SHADERMATERIAL_H

#include "Framework.h"

class ShaderMaterial
{
public:
    ShaderMaterial();

    float diffuse[4];
    float ambient[4];
    float specular[4];
    float emissive[4];
    float shininess;
    int texCount;


};

#endif // SHADERMATERIAL_H
