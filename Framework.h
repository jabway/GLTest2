#ifndef FRAMEWORK_H
#define FRAMEWORK_H

// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GL/glfw.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/swizzle.hpp>
using namespace glm;

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <cstring>
#include <math.h>
#include <stack>
#include <typeinfo>
using namespace std;

// Include IL
#include "IL/il.h"

// Include tinyXML
//#include <tinyxml.h>

#include <assimp/assimp.hpp>      // C++ importer interface
#include <assimp/aiScene.h>       // Output data structure
#include <assimp/aiPostProcess.h> // Post processing flags
using namespace Assimp;


#endif // FRAMEWORK_H
