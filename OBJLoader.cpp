#include "OBJLoader.h"

OBJLoader::OBJLoader()
{
    startIndex = 0;
}

OBJLoader::OBJLoader(string Filename)
{
    startIndex = 0;
    Load(Filename);
    CalculateNormals();
}

void OBJLoader::Load(string Filename)
{
    ifstream OBJFile;

    OBJFile.open(Filename.c_str(), ios::in);

    // Failed to open OBJ
    if( !OBJFile.is_open() )
    {
        cerr << "Could not open OBJ file: \"" << Filename << "\"" << endl;
        return;
    }

    string line = "";

    while( getline(OBJFile, line))
    {
        bool working = line.find("v ") != string::npos;
        istringstream iss(line, istringstream::in);

        if( line.find("v ") != string::npos ){

            char c;
            glm::vec3 PosVec;

            if( ( iss >> c >> PosVec[0] >> PosVec[1] >> PosVec[2]).fail() )
            {
                cerr << "Could not parse position" << endl;
                return;
            }

            //PosVec[3] = 1.0f;
            Position.push_back(PosVec[0]);
            Position.push_back(PosVec[1]);
            Position.push_back(PosVec[2]);
            //Position.push_back(PosVec[3]);
            Color.push_back(0.9f);
            Color.push_back(0.9f);
            Color.push_back(0.9f);
            //Color.push_back(1.0f);
        }else if(line.find("vn ") != string::npos){
            char c;
            glm::vec3 NormVec;

            if( ( iss >> c >> NormVec[0] >> NormVec[1] >> NormVec[2]).fail() )
            {
                cerr << "Could not parse normal" << endl;
                return;
            }

            Normal.push_back(NormVec[0]);
            Normal.push_back(NormVec[1]);
            Normal.push_back(NormVec[2]);
        }else if(line.find("vt ") != string::npos){

        }else if(line.find("s ") != string::npos){
            char c;

            if( ( iss >> c >> startIndex).fail() )
            {
                cerr << "Could not parse start index" << endl;
                return;
            }
        }else if(line.find("f ") != string::npos){

            char c;
            glm::ivec3 IndexVec;

            if( ( iss >> c >> IndexVec[0] >> IndexVec[1] >> IndexVec[2]).fail() )
            {
                cerr << "Could not parse index" << endl;
                return;
            }

            if(IndexVec[0] == IndexVec[1] || IndexVec[0] == IndexVec[2] ||
                    IndexVec[1] == IndexVec[2])
            {
                cerr << "Got a degenerate triangle "  << endl;
                break;
            }

            Indices.push_back(IndexVec[0] - startIndex);
            Indices.push_back(IndexVec[1] - startIndex);
            Indices.push_back(IndexVec[2] - startIndex);
        }
    }
    int NumUnique = Position.size() / 3;

    Normal.assign(NumUnique * 3, 0.0f);

    OBJFile.close();
}


void OBJLoader::CalculateNormals()
{
    if(Indices.size() < 3 || Position.size() < 9)
    {
        cerr << "Can't calculate normals" << endl;
        return;
    }

    int Numindices = Indices.size();
    int NumUnique = Position.size() / 3;
    //Normal = vector<GLfloat>(NumUnique * 3, 0.0f);
    Normal.assign(NumUnique * 3, 0.0f);

    for(int i = 0; i < Numindices; i+=3)
    {
        int p0 = Indices[i] * 3;
        int p1 = Indices[i+1] * 3;
        int p2 = Indices[i+2] * 3;

        int n0 = Indices[i] * 3;
        int n1 = Indices[i+1] * 3;
        int n2 = Indices[i+2] * 3;
        vec3 FaceNorm;

        if(p0 == p1 || p0 == p2 || p1 == p2)
        {
            cerr << "Got a degenerate triangle " << i << endl;
            continue;
        }

        vec3 a(Position[p0], Position[p0 + 1], Position[p0 + 2]);
        vec3 b(Position[p1], Position[p1 + 1], Position[p1 + 2]);
        vec3 c(Position[p2], Position[p2 + 1], Position[p2 + 2]);
        vec3 ca = c - a;
        vec3 cb = c - b;

        FaceNorm = glm::cross( ca, cb);



        if( isnan( FaceNorm[0]) ||
            isnan( FaceNorm[1]) ||
            isnan( FaceNorm[2]) )
        {

            FaceNorm = vec3(0.577350269f, 0.577350269f, 0.577350269f);
            //FaceNorm = vec3(cb[2] + ca[1], cb[0] + ca[2], cb[1] + ca[0]);
            cerr << "Got a NaN for normal " << i << endl;
        }

        Normal[n0] += FaceNorm[0];
        Normal[n1] += FaceNorm[0];
        Normal[n2] += FaceNorm[0];
        Normal[n0 + 1] += FaceNorm[1];
        Normal[n1 + 1] += FaceNorm[1];
        Normal[n2 + 1] += FaceNorm[1];
        Normal[n0 + 2] += FaceNorm[2];
        Normal[n1 + 2] += FaceNorm[2];
        Normal[n2 + 2] += FaceNorm[2];
    }

    for(int i = 0; i < NumUnique; i++)
    {
        int p = i * 3;
        int n = i * 3;

        vec3 a(Normal[n], Normal[n+1], Normal[n+2]);

        vec3 aNorm = glm::normalize(a);

        if( isnan( aNorm[0]) ||
            isnan( aNorm[1]) ||
            isnan( aNorm[2]) )
        {
            //aNorm = vec3(0.577350269f, 0.577350269f, 0.577350269f);
            aNorm = vec3(Normal[n-3], Normal[n-2], Normal[n-1]);
            //aNorm = vec3(0.0f, 0.0f, 0.0f);
            //vec4 pos(Position[p])
            //aNorm = a;
            cerr << "Got a NaN for normal " << i << endl;
        }

        Normal[n] = aNorm[0];
        Normal[n+1] = aNorm[1];
        Normal[n+2] = aNorm[2];
    }

    cout << "Done calculating normals" << endl;
}


vector<GLfloat>& OBJLoader::GetPosition()
{
    return Position;
}

vector<GLfloat>& OBJLoader::GetNormal()
{
    return Normal;
}

vector<GLfloat>& OBJLoader::GetColor()
{
    return Color;
}

vector<GLuint>& OBJLoader::GetIndices()
{
    return Indices;
}
