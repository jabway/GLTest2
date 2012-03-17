#include "ShaderMaterial.h"

ShaderMaterial::ShaderMaterial()
{
}

void ShaderMaterial::setDiffuse(float r, float g, float b, float a){
    diffuse[0] = r;
    diffuse[1] = g;
    diffuse[2] = b;
    diffuse[3] = a;
}

void ShaderMaterial::setAmbient(float r, float g, float b, float a){
    ambient[0] = r;
    ambient[1] = g;
    ambient[2] = b;
    ambient[3] = a;
}

void ShaderMaterial::setSpecular(float r, float g, float b, float a){
    specular[0] = r;
    specular[1] = g;
    specular[2] = b;
    specular[3] = a;
}

void ShaderMaterial::setEmissive(float r, float g, float b, float a){
    emissive[0] = r;
    emissive[1] = g;
    emissive[2] = b;
    emissive[3] = a;
}
