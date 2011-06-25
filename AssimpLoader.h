#ifndef ASSIMPLOADER_H
#define ASSIMPLOADER_H

#include "Framework.h"

class AssimpLoader
{
private:
    Importer importer;
    aiScene     scene;
public:
    AssimpLoader();
    bool Import3DFromFile( const std::string& pFile);
};

#endif // ASSIMPLOADER_H
