#include "OBJLoader.h"

OBJLoader::OBJLoader()
{
}

OBJLoader::OBJLoader(string Filename)
{
    Load(Filename);
    CalculateNormals();
    //CreateVertices();
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
            glm::vec4 PosVec;

            if( ( iss >> c >> PosVec[0] >> PosVec[1] >> PosVec[2]).fail() )
            {
                cerr << "Could not parse position" << endl;
                return;
            }

            PosVec[3] = 1.0f;
            Position.push_back(PosVec[0]);
            Position.push_back(PosVec[1]);
            Position.push_back(PosVec[2]);
            Position.push_back(PosVec[3]);
            Color.push_back(1.0f);
            Color.push_back(1.0f);
            Color.push_back(0.0f);
            Color.push_back(1.0f);
        }else if(line.find("vn ") != string::npos){

        }else if(line.find("vt ") != string::npos){

        }else if(line.find("f ") != string::npos){

            char c;
            glm::ivec3 IndexVec;

            if( ( iss >> c >> IndexVec[0] >> IndexVec[1] >> IndexVec[2]).fail() )
            {
                cerr << "Could not parse index" << endl;
                return;
            }

            Indices.push_back(IndexVec[0] - 1);
            Indices.push_back(IndexVec[1] - 1);
            Indices.push_back(IndexVec[2] - 1);
        }
    }
    int NumUnique = Position.size() / 4;

    Normal.assign(NumUnique * 3, 0.0f);

    OBJFile.close();
}

void OBJLoader::CalculateNormals()
{
    if(Indices.size() < 3 || Position.size() < 12)
    {
        cerr << "Can't calculate normals" << endl;
        return;
    }

    int NumFaces = Indices.size() / 3;
    int NumUnique = Position.size() / 4;
    //Normal = vector<GLfloat>(NumUnique * 3, 0.0f);
    Normal.assign(NumUnique * 3, 0.0f);

    for(int i = 0; i < NumFaces; i++)
    {
        int p0 = Indices[i] * 4;
        int p1 = Indices[i+1] * 4;
        int p2 = Indices[i+2] * 4;

        int n0 = Indices[i] * 3;
        int n1 = Indices[i+1] * 3;
        int n2 = Indices[i+2] * 3;
        vec3 FaceNorm;

        if(n0 == n1 || n0 == n2 || n1 == n2)
        {
            cerr << "Got a degenerate face " << i << endl;
            continue;
        }

        vec3 a(Position[p0], Position[p0 + 1], Position[p0 + 2]);
        vec3 b(Position[p1], Position[p1 + 1], Position[p1 + 2]);
        vec3 c(Position[p2], Position[p2 + 1], Position[p2 + 2]);
        vec3 ca = c - a;
        vec3 cb = c - b;

        FaceNorm = glm::normalize(glm::cross( ca, cb) );



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
        int p = i * 4;
        int n = i * 3;

        vec3 a(Normal[n], Normal[n+1], Normal[n+2]);

        vec3 aNorm = glm::normalize(a);

        if( isnan( aNorm[0]) ||
            isnan( aNorm[1]) ||
            isnan( aNorm[2]) )
        {
            //aNorm = vec3(0.577350269f, 0.577350269f, 0.577350269f);
            aNorm = vec3(0.0f, 0.0f, 1.0f);
            //aNorm = a;
            cerr << "Got a NaN for normal " << i << endl;
        }

        if( aNorm == vec3(0.0f, 0.0f, 0.0f))
        {
            aNorm = vec3(0.0f, 0.0f, 1.0f);
        }

        Normal[n] = aNorm[0];
        Normal[n+1] = aNorm[1];
        Normal[n+2] = aNorm[2];
    }

    CreateVertices(Vertices);

    cout << "Done calculating normals" << endl;
}

void OBJLoader::CreateVertices(vector<Vertex> &_Vertices)
{

    int NumUnique = Position.size() / 4;
    for(int i = 0; i < NumUnique; i++)
    {
        int p = i * 4;
        int n = i * 3;

        vec3 a(Normal[n], Normal[n+1], Normal[n+2]);

        Vertex v;
        v.XYZW = { Position[p], Position[p+1], Position[p+2], Position[p+3] };
        v.Normal = { a[0], a[1], a[2] };
        v.RGBA = { 1.0f, 1.0f, 1.0f, 1.0f };

        _Vertices.push_back(v);
    }
}

void OBJLoader::Store(Vertex *outVertices, int *VertSize, GLuint *outIndices, int *IndexSize)
{
    outVertices = &Vertices[0];
    *VertSize = Vertices.size();
    outIndices = &Indices[0];
    *IndexSize = Indices.size();
}

vector<Vertex> OBJLoader::GetVertices()
{
    return Vertices;
}

vector<GLuint> OBJLoader::GetIndices()
{
    return Indices;
}
