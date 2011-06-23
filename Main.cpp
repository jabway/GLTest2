#include "Framework.h"
#include "ShaderProgram.h"
#include "Vertex.h"
#include "VertexArrayObject.h"

using namespace std;

// Function prototypes
void logRedirect();
void logUnredirect();
void RenderFunction(void);

void Cleanup(void);

// Variables
streambuf *ferrbuf, *errbackup, *foutbuf, *outbackup;
ofstream ferrstr, foutstr;
unsigned frameCount = 0;

VertexArrayObject *VAO;

GLuint
    VaoId,
    BufferId,
    IndexBufferId;

int main()
{
    logRedirect();

    // Initialise GLFW
    if( !glfwInit() )
    {
        cerr << "Failed to initialize GLFW\n" << endl;
        return -1;
    }
    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4); // 4x antialiasing
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

    // Open a window and create its OpenGL context
    if( !glfwOpenWindow( 1024, 768, 0,0,0,0, 32,0, GLFW_WINDOW ) )
    {
        cerr << "Failed to open GLFW window\n"  << endl;
        glfwTerminate();
        return -1;
    }

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        cerr << "Failed to initialize GLEW\n" << endl;
        return -1;
    }

    glfwSetWindowTitle( "Tutorial 01" );

    // Create VBO
    VAO = new VertexArrayObject();

    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Ensure we can capture the escape key being pressed below
    glfwEnable( GLFW_STICKY_KEYS );

    ShaderProgram sp("shader.vert", "shader.frag");

    do{
        sp.Use();

        // Enable depth test
        glEnable(GL_DEPTH_TEST);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, NULL);

        // Swap buffers
        glfwSwapBuffers();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
    glfwGetWindowParam( GLFW_OPENED ) );

    Cleanup();

    logUnredirect();
}

void logRedirect()
{
    ferrstr.open("errlog.txt");
    foutstr.open("log.txt");

    // backup rdbufs
    errbackup = cerr.rdbuf();
    outbackup = cout.rdbuf();

    ferrbuf = ferrstr.rdbuf();
    foutbuf = foutstr.rdbuf();
    cerr.rdbuf(ferrbuf);
    cout.rdbuf(foutbuf);
}

void logUnredirect()
{
    cerr.rdbuf(errbackup);
    cout.rdbuf(outbackup);

    ferrstr.close();
    foutstr.close();
}

void Cleanup(void)
{
    delete VAO;
}

void RenderFunction()
{
 return;
}

