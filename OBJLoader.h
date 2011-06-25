#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "Framework.h"
#include "Vertex.h"

class OBJLoader
{
private:
    vector<GLfloat> Position,
                    Normal,
                    Color;

    vector<GLuint> Indices;
    vector<Vertex> Vertices;
public:
    OBJLoader();
    OBJLoader(string Filename);

    void Load(string Filename);
    void CalculateNormals();
    void CreateVertices(vector<Vertex> &_Vertices);
    void Store(Vertex * outVertices,
               int * VertSize,
               GLuint * outIndices,
               int * IndexSize);
    vector<Vertex> GetVertices();
    vector<GLuint> GetIndices();
};

#endif // OBJLOADER_H
