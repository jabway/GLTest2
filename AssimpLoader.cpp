#include "AssimpLoader.h"

mat4 aiMatrix4ToMat4(aiMatrix4x4 in);

AssimpLoader::AssimpLoader()
{
    scaleFactor = 1.0f;
    GLSceneMeshes = NULL;
}

void AssimpLoader::constructScene()
{
    if(!scene)
        return;
    GLSceneMeshes = new SceneMesh();

    aiNode * root = scene->mRootNode;

    for(int i = 0; i < root->mNumMeshes; i++)
    {
        Mesh temp = getMesh( root->mMeshes[i]);
        GLSceneMeshes->AddMesh(temp);
        GLSceneMeshes->SetModelMatrix(temp.GetModelMatrix());
    }

    // Temporary array for node children
    vector<aiNode*> childArray;

    for(int j = 0; j < root->mNumChildren; j++)
    {
        childArray.push_back( root->mChildren[j]);
        SceneMesh * temp = constructSceneHelper(root->mChildren[j]);
        GLSceneMeshes->AddChild(temp);
    }
}

SceneMesh * AssimpLoader::constructSceneHelper(aiNode * node)
{
    if(!node)
        return NULL;

    SceneMesh * current = new SceneMesh();

    for(int i = 0; i < node->mNumMeshes; i++)
    {
        Mesh temp = getMesh( node->mMeshes[i]);
        current->AddMesh(temp);
        current->SetModelMatrix(temp.GetModelMatrix());
    }

    // Temporary array for node children
    vector<aiNode*> childArray;

    for(int j = 0; j < node->mNumChildren; j++)
    {
        childArray.push_back( node->mChildren[j]);
        SceneMesh * temp = constructSceneHelper(node->mChildren[j]);
        current->AddChild(temp);
    }

    return current;
}

void AssimpLoader::get_bounding_box_for_node(const aiNode *nd,
                                             aiVector3D *min,
                                             aiVector3D *max)
{
    struct aiMatrix4x4 prev;
    unsigned int n = 0, t;

    for (; n < nd->mNumMeshes; ++n) {
            const struct aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];
            for (t = 0; t < mesh->mNumVertices; ++t) {

                    struct aiVector3D tmp = mesh->mVertices[t];

                    min->x = aisgl_min(min->x,tmp.x);
                    min->y = aisgl_min(min->y,tmp.y);
                    min->z = aisgl_min(min->z,tmp.z);

                    max->x = aisgl_max(max->x,tmp.x);
                    max->y = aisgl_max(max->y,tmp.y);
                    max->z = aisgl_max(max->z,tmp.z);
            }
    }

    for (n = 0; n < nd->mNumChildren; ++n) {
            get_bounding_box_for_node(nd->mChildren[n],min,max);
    }
}

void AssimpLoader::get_bounding_box (struct aiVector3D* min,
                                     struct aiVector3D* max)
{

        min->x = min->y = min->z =  1e10f;
        max->x = max->y = max->z = -1e10f;
        get_bounding_box_for_node(scene->mRootNode,min,max);
}

bool AssimpLoader::Import3DFromFile( const std::string& pFile)
{

    //check if file exists
    std::ifstream fin(pFile.c_str());
    if(!fin.fail()) {
        fin.close();
    }
    else{
        printf("Couldn't open file: %s\n", pFile.c_str());
        printf("%s\n", importer.GetErrorString());
        return false;
    }

    // Have to use aiProcess_OptimizeGraph to make sure nodes are created
    scene = importer.ReadFile( pFile, aiProcessPreset_TargetRealtime_Quality | aiProcess_OptimizeGraph);

    // If the import failed, report it
    if( !scene)
    {
        printf("%s\n", importer.GetErrorString());
        return false;
    }

    // Now we can access the file's contents.
    printf("Import of scene %s succeeded.",pFile.c_str());

    struct aiVector3D scene_min, scene_max, scene_center;
    get_bounding_box(&scene_min, &scene_max);
    float tmp;
    tmp = scene_max.x-scene_min.x;
    tmp = scene_max.y - scene_min.y > tmp?scene_max.y - scene_min.y:tmp;
    tmp = scene_max.z - scene_min.z > tmp?scene_max.z - scene_min.z:tmp;
    scaleFactor = 200.0f / tmp;

    // Load textures before scene
    LoadGLTextures();

    constructScene();
    // We're done. Everything will be cleaned up by the importer destructor
    return true;
}

void AssimpLoader::setScaleFactor(float scale)
{
    //scaleFactor = scale;
}

void AssimpLoader::genVAOsAndUniformBuffer()
{
    if(!scene)
        return;

    for(int n = 0; n < scene->mNumMeshes; n++)
    {

        MeshArray.push_back( getMesh(n));
    }


}

Mesh AssimpLoader::getMesh(int index)
{
    Mesh GLMesh;

    if(!scene)
        return GLMesh;

    // Variables
    struct aiMesh* mesh = scene->mMeshes[index];
    ShaderMaterial aMat;
    VertexArrayObject* VAO;
    string Vert, Frag;

    // Create vector for indices
    vector<GLuint> Indices;
    BufferObjectData Bod;

    // Get mesh name
    GLMesh.mName = mesh->mName.data;


    Vert = "shaders/" + GLMesh.mName + ".vert";
    Frag = "shaders/" + GLMesh.mName + ".frag";
    GLMesh.AttachShader();

    for(int t = 0; t < mesh->mNumFaces; t++)
    {

        Indices.push_back(mesh->mFaces[t].mIndices[0]);
        Indices.push_back(mesh->mFaces[t].mIndices[1]);
        Indices.push_back(mesh->mFaces[t].mIndices[2]);
    }

    // Create Vao
    VAO = new VertexArrayObject();
    if(!VAO)
        return GLMesh;

    // Add Positions
    if(mesh->HasPositions())
    {
        vector<GLfloat> Positions;
        for(int v = 0; v < mesh->mNumVertices; v++)
        {

            Positions.push_back(mesh->mVertices[v].x * scaleFactor);
            Positions.push_back(mesh->mVertices[v].y * scaleFactor);
            Positions.push_back(mesh->mVertices[v].z * scaleFactor);
        }

        Bod.AddAttribute(Positions, 3, 0);
    }

    // Add Normals
    if(mesh->HasNormals())
    {
        vector<GLfloat> Normals;
        for(unsigned v = 0; v < mesh->mNumVertices; v++)
        {
            Normals.push_back(mesh->mNormals[v].x);
            Normals.push_back(mesh->mNormals[v].y);
            Normals.push_back(mesh->mNormals[v].z);
        }


        Bod.AddAttribute(Normals, 3, 1);
    }

    // Add texture coordinates
    if (mesh->HasTextureCoords(0))
    {
        vector<GLfloat> UVs;
        for(unsigned v = 0; v < mesh->mNumVertices; v++)
        {
            UVs.push_back(mesh->mTextureCoords[0][v].x);
            UVs.push_back(mesh->mTextureCoords[0][v].y);
        }

        Bod.AddAttribute(UVs, 2, 2);
    }
    else
    {
        vector<GLfloat> Colors(mesh->mNumVertices * 3, 0.9);
        Bod.AddAttribute(Colors, 3, 2);
    }

    // Add Tangents and Binormals
    if (mesh->HasTangentsAndBitangents())
    {
        vector<GLfloat> Tangents;
        vector<GLfloat> Bitangents;
        for(unsigned v = 0; v < mesh->mNumVertices; v++)
        {
            Tangents.push_back(mesh->mTangents[v].x);
            Tangents.push_back(mesh->mTangents[v].y);
            Tangents.push_back(mesh->mTangents[v].z);

            Bitangents.push_back(mesh->mBitangents[v].x);
            Bitangents.push_back(mesh->mBitangents[v].y);
            Bitangents.push_back(mesh->mBitangents[v].z);
        }
        Bod.AddAttribute(Tangents, 3, 3);
        Bod.AddAttribute(Bitangents, 3, 4);
    }

    VAO->BindBuffers(Bod, Indices);

    // Get transformation matrix
    aiMatrix4x4 m = scene->mRootNode->mTransformation;

    // Convert to column major
    m.Transpose();
    mat4 mt = aiMatrix4ToMat4(m);
    mt = gtc::matrix_transform::rotate(mt, 90.0f, vec3(-1,0,0));

    //VAO->AddModelMatrix(mt);
    GLMesh.SetModelMatrix(mt);


    // create material uniform buffer
    struct aiMaterial *mtl = scene->mMaterials[mesh->mMaterialIndex];

    // Get texture count for mesh, but don't assume they load
    aMat.texCount = 0;
    int maxTex = mtl->GetTextureCount(aiTextureType_DIFFUSE);

    aiString texPath;	//contains filename of texture

    for(int t = 0; t < maxTex; t++)
    {
        if(AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, t, &texPath)){
            //bind texture
            unsigned int texId = textureIdMap[texPath.data];
            GLMesh.texIndices.push_back(texId);
            aMat.texCount++;
        }
        //        else
        //                aMat.texCount = 0;
    }

    // Get Uniform values

    // Initialize defaults
    aMat.diffuse = {0.8, 0.8, 0.8, 1.0};
    aMat.ambient = {0.2, 0.2, 0.2, 1.0};
    aMat.specular = {0.1, 0.1, 0.1, 1.0};
    aMat.emissive = {0.0, 0.0, 0.0, 1.0};

    aiColor4D diffuse;
    if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
    {
        memcpy(aMat.diffuse, &diffuse, sizeof(aiColor4D) );
    }

    aiColor4D ambient;
    if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
    {
        memcpy(aMat.ambient, &ambient, sizeof(aiColor4D) );
    }

    aiColor4D specular;
    if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
    {
        //memcpy(aMat.specular, &specular, sizeof(aiColor4D) );
    }

    aiColor4D emissive;
    if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emissive))
    {
        memcpy(aMat.emissive, &emissive, sizeof(aiColor4D) );
    }

    float shininess = 1.0;
    unsigned int max;
    aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
    aMat.shininess = shininess;



    GLMesh.SetMaterial(aMat);
    GLMesh.AttachVAO(VAO);

    return GLMesh;
}

SceneMesh * AssimpLoader::getScene()
{
    return GLSceneMeshes;
}

int AssimpLoader::LoadGLTextures()
{
    if(!scene)
        return -1;

    ILboolean success;

    /* initialization of DevIL */
    ilInit();

    /* scan scene's materials for textures */
    for (unsigned int m=0; m < scene->mNumMaterials; ++m)
    {
        int texIndex = 0;
        aiString path;  // filename

        aiReturn texFound = scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
        while (texFound == AI_SUCCESS) {
            //fill map with textures, OpenGL image ids set to 0
            textureIdMap[path.data] = 0;
            // more textures?
            texIndex++;
            texFound = scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
        }
    }

    int numTextures = textureIdMap.size();

    /* create and fill array with DevIL texture ids */
    ILuint* imageIds = new ILuint[numTextures];
    ilGenImages(numTextures, imageIds);

    /* create and fill array with GL texture ids */
    GLuint* textureIds = new GLuint[numTextures];
    glGenTextures(numTextures, textureIds); /* Texture name generation */

    /* get iterator */
    std::map<std::string, GLuint>::iterator itr;
    itr = textureIdMap.begin();
    int i=0;
    for (; itr != textureIdMap.end(); ++i, ++itr)
    {
        //save IL image ID
        std::string filename = (*itr).first;  // get filename
        (*itr).second = textureIds[i];    // save texture id for filename in map

        ilBindImage(imageIds[i]); /* Binding of DevIL image name */
        ilEnable(IL_ORIGIN_SET);
        ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
        success = ilLoadImage((ILstring)filename.c_str());

        if (success) {
            /* Convert image to RGBA */
            //ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
            GLuint format = ilGetInteger (IL_IMAGE_FORMAT);
            GLuint type = ilGetInteger(IL_IMAGE_TYPE);

            /* Create and load textures to OpenGL */
            GLuint texID = textureIds[i];
            glBindTexture(GL_TEXTURE_2D, texID);
            glTextureParameteriEXT(texID, GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTextureParameteriEXT(texID, GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTextureImage2DEXT(texID, GL_TEXTURE_2D, 0, format, ilGetInteger(IL_IMAGE_WIDTH),
                                ilGetInteger(IL_IMAGE_HEIGHT), 0, format, type, ilGetData());
            glGenerateTextureMipmapEXT(texID, GL_TEXTURE_2D);
        }
        else
            printf("Couldn't load Image: %s\n", filename.c_str());
    }
    /* Because we have already copied image data into texture data
    we can release memory used by image. */
    ilDeleteImages(numTextures, imageIds);

    //Cleanup
    delete [] imageIds;
    delete [] textureIds;

    //return success;
    return true;
}

vector<Mesh> AssimpLoader::getMeshes()
{
    return MeshArray;
}

mat4 aiMatrix4ToMat4(aiMatrix4x4 in)
{
    mat4 result(1.0);

    memcpy(&result[0], in[0], sizeof(aiMatrix4x4));

    return result;
}


