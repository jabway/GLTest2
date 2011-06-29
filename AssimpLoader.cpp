#include "AssimpLoader.h"

mat4 aiMatrix4ToMat4(aiMatrix4x4 in);

AssimpLoader::AssimpLoader()
{
    scaleFactor = 1.0f;
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

    scene = importer.ReadFile( pFile, aiProcessPreset_TargetRealtime_Quality);

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
    scaleFactor = 8.0f / tmp;

    LoadGLTextures();
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
        struct aiMesh* mesh = scene->mMeshes[n];
        VertexArrayObject* VAO;

        // Create vector for indices
        vector<GLuint> Indices;
        BufferObjectData Bod;

        for(int t = 0; t < mesh->mNumFaces; t++)
        {
            int faceIndex = t * 3;

            Indices.push_back(mesh->mFaces[t].mIndices[0]);
            Indices.push_back(mesh->mFaces[t].mIndices[1]);
            Indices.push_back(mesh->mFaces[t].mIndices[2]);
        }

        VAO = new VertexArrayObject();
        if(!VAO)
            return;

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

        if(mesh->HasNormals())
        {
            vector<GLfloat> Normals;
            for(int v = 0; v < mesh->mNumVertices; v++)
            {
                Normals.push_back(mesh->mNormals[v].x);
                Normals.push_back(mesh->mNormals[v].y);
                Normals.push_back(mesh->mNormals[v].z);
            }


            Bod.AddAttribute(Normals, 3, 1);
        }

        vector<GLfloat> Colors(mesh->mNumVertices * 3, 0.9);
        Bod.AddAttribute(Colors, 3, 2);

        VAO->BindBuffers(Bod, Indices);
        VAO->AttachShader("shader.vert", "shader.frag");

        // Get transformation matrix
        aiMatrix4x4 m = scene->mRootNode->mTransformation;

        // Convert to column major
        m.Transpose();
        mat4 mt = aiMatrix4ToMat4(m);

        VAO->AddModelMatrix(mt);
//        VAO->AddModelMatrix(mat4(1.0));

        VertexArrays.push_back(VAO);


    }
}

vector<VertexArrayObject*>& AssimpLoader::getVAOs()
{
    return VertexArrays;
}

int AssimpLoader::LoadGLTextures()
{
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
            ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

            /* Create and load textures to OpenGL */
            glBindTexture(GL_TEXTURE_2D, textureIds[i]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ilGetInteger(IL_IMAGE_WIDTH),
                ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGBA, GL_UNSIGNED_BYTE,
                ilGetData());
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

mat4 aiMatrix4ToMat4(aiMatrix4x4 in)
{
    mat4 result(1.0);

//    for(int i = 0; i < 4; i++)
//    {
////        vec4 resVec;
////        resVec.x = *in[i*4];
////        resVec.y = *in[i*4 + 1];
////        resVec.z = *in[i*4 + 2];
////        resVec.w = *in[i*4 + 3];
////        result[i] = resVec;
//        result[i].x = *in[i*4];
//        result[i].y = *in[i*4 + 1];
//        result[i].z = *in[i*4 + 2];
//        result[i].w = *in[i*4 + 3];
    //    }

//        result[0].x = in.a1;
//        result[0].y = in.a2;
//        result[0].z = in.a3;
//        result[0].w = in.a4;
//        result[1].x = in.b1;
//        result[1].y = in.b2;
//        result[1].z = in.b3;
//        result[1].w = in.b4;
//        result[2].x = in.c1;
//        result[2].y = in.c2;
//        result[2].z = in.c3;
//        result[2].w = in.c4;
//        result[3].x = in.d1;
//        result[3].y = in.d2;
//        result[3].z = in.d3;
//        result[3].w = in.d4;
    memcpy(&result[0], in[0], sizeof(aiMatrix4x4));

    return result;
}
