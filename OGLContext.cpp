#include "OGLContext.h"

OGLContext::OGLContext()
{
    frameCount = 0;
    lastFrame = 0.0f;

    // Initialise GLFW
    if( !glfwInit() )
    {
        cerr << "Failed to initialize GLFW\n" << endl;
        return;
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
        return;
    }

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        cerr << "Failed to initialize GLEW\n" << endl;
        return;
    }

    glfwSetWindowTitle( "Tutorial 01" );

    // Create VBO
    VAO = new VertexArrayObject();

    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Ensure we can capture the escape key being pressed below
    glfwEnable( GLFW_STICKY_KEYS );

    sp = new ShaderProgram("shader.vert", "shader.frag");


}

void OGLContext::Cleanup(void)
{
    delete VAO;
}

void OGLContext::RenderFunction()
{


    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    sp->Use();

    VAO->Draw();

    sp->Disable();


    // Swap buffers
    glfwSwapBuffers();



    float curTime = glfwGetTime();
    float deltaTime = curTime - lastFrame;

    if( deltaTime > 1.0f)
    {
        string title = "";
        ostringstream oss(title, ostringstream::out);

        oss << "Tutorial 01 | FPS: " << frameCount/deltaTime;
        glfwSetWindowTitle(oss.str().c_str());
        frameCount = 0;
        lastFrame = glfwGetTime();
    }
    else
    {
        frameCount++;
    }
}

void OGLContext::Render()
{
    lastFrame = glfwGetTime();
    do{

        RenderFunction();
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
    glfwGetWindowParam( GLFW_OPENED ) );

    Cleanup();
}
