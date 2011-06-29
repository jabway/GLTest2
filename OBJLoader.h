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
    int startIndex;
public:
    OBJLoader();
    OBJLoader(string Filename);

    void Load(string Filename);
    void CalculateNormals();

    vector<GLfloat>& GetPosition();
    vector<GLfloat>& GetNormal();
    vector<GLfloat>& GetColor();

    vector<GLuint>& GetIndices();
};

#endif // OBJLOADER_H
