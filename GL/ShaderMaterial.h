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

    void setDiffuse(float r, float g, float b, float a);
    void setAmbient(float r, float g, float b, float a);
    void setSpecular(float r, float g, float b, float a);
    void setEmissive(float r, float g, float b, float a);
};

#endif // SHADERMATERIAL_H
