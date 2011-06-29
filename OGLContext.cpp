#include "OGLContext.h"



OGLContext::OGLContext()
{
    FrameCount = 0;
    LastFrame = 0.0f;

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


    // Initialize Matrices
    CameraPos = vec3(0, 9, 12);
    CameraFocus = vec3(0,3,0);
    setPerspective(45.0f, 1.33f, 0.1f, 100.0f);
    setView(CameraPos, CameraFocus, vec3(0,1,0));

    mat4 debug = Matrices::View;

    Lights::LightPos = vec3(0,6,6);
    LightTheta = 0.0f;

    AssimpLoader aiL;
    aiL.Import3DFromFile("pc/c001\ -\ Lighning/c001.x360out.dae");
    aiL.setScaleFactor(5.0f);
    aiL.genVAOsAndUniformBuffer();
    VAO = aiL.getVAOs();

//    if(!VAO)
//    {
//        cerr << "Could not load mesh" << endl;
//        exit(-1);
//    }


    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Ensure we can capture the escape key being pressed below
    glfwEnable( GLFW_STICKY_KEYS );

//    sp = new ShaderProgram("shader.vert", "shader.frag");
//    if(!sp)
//    {
//        cerr << "Could not create shader program" << endl;
//        exit(-1);
//    }


}

void OGLContext::Cleanup(void)
{
    for(int i = 0; i < VAO.size(); i++)
    {
        if(VAO[i])
            delete VAO[i];
    }

    if(sp)
        delete sp;
}

void OGLContext::RenderFunction()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

//    glCullFace(GL_BACK);
//    glEnable(GL_CULL_FACE);


    for(int i = 0; i < VAO.size(); i++)
        VAO[i]->Draw();


    // Swap buffers
    glfwSwapBuffers();



    FrameCount++;

    LastTime = CurTime;
    CurTime = glfwGetTime();
    DeltaTime = CurTime - LastFrame;
    LightTheta += (CurTime - LastTime);

    LightTheta = (LightTheta > 360.0)?(LightTheta - 360.0):LightTheta;

    vec3 temp = vec3(0, 0, 6);

    Lights::LightPos.x = temp.x * glm::cos(LightTheta)
                         - temp.z * glm::sin(LightTheta);

    Lights::LightPos.z = temp.z * glm::cos(LightTheta)
                         + temp.x * glm::sin(LightTheta);

    if( DeltaTime > 1.0f)
    {
        string title = "";
        ostringstream oss(title, ostringstream::out);

        oss << "Tutorial 01 | FPS: " << FrameCount/DeltaTime;
        glfwSetWindowTitle(oss.str().c_str());
        FrameCount = 0;
        LastFrame = glfwGetTime();
    }
}

void OGLContext::Render()
{
    LastFrame = glfwGetTime();
    glfwGetMousePos(&MousePos[0], &MousePos[1]);
    MouseDown = false;
    do{

        RenderFunction();
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
    glfwGetWindowParam( GLFW_OPENED ) );

    Cleanup();
}

void OGLContext::setPerspective(float fov, float aspect, float near,
                                   float far)
{
    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    Matrices::Projection = glm::gtc::matrix_transform::perspective(fov, aspect, near, far);
}

void OGLContext::setView(glm::vec3 cameraLocation, glm::vec3 focus,
                            glm::vec3 upVector)
{
    // Camera matrix
    mat4 CameraMatrix;

    CameraMatrix       = glm::gtc::matrix_transform::lookAt(
        cameraLocation, // Camera is at (4,3,3), in World Space
        focus, // and looks at the origin
        upVector  // Head is up (set to 0,-1,0 to look upside-down)
    );

    Matrices::View = CameraMatrix;

}
void GLFWCALL OGLContext::Resize(int width, int height)
{
    glfwSetWindowSize(width, height);
    // Initialize Matrices
    setPerspective(45.0f, (double)width/(double)height, 0.1f, 100.0f);
}

void OGLContext::KeyCallback(int key, int action)
{
    if(action == GLFW_PRESS)
    {
        switch(key)
        {
            case GLFW_KEY_UP:
                CameraPos.y += 0.5f;
                CameraFocus.y += 0.5f;
                setView(CameraPos, CameraFocus, vec3(0,1,0));
                break;
            case GLFW_KEY_DOWN:
                CameraPos.y -= 0.5f;
                CameraFocus.y -= 0.5f;
                setView(CameraPos, CameraFocus, vec3(0,1,0));
                break;
            case GLFW_KEY_RIGHT:
                CameraPos.x += 0.5f;
                CameraFocus.x += 0.5f;
                setView(CameraPos, CameraFocus, vec3(0,1,0));
                break;
            case GLFW_KEY_LEFT:
                CameraPos.x -= 0.5f;
                CameraFocus.x -= 0.5f;
                setView(CameraPos, CameraFocus, vec3(0,1,0));
            break;
            default:
                break; // Do nothing
        }
    }
}

void OGLContext::MouseButtonCallback(int button, int action)
{
    if(action == GLFW_PRESS)
    {
        switch(button)
        {
        case GLFW_MOUSE_BUTTON_LEFT:
            MouseDown = true;
        default:
            break;
        }
    }
    else{
        switch(button)
        {
        case GLFW_MOUSE_BUTTON_LEFT:
            MouseDown = false;
        default:
            break;
        }
    }
}

void OGLContext::MousePosCallback(int x, int y)
{
    DeltaPos[0] = MousePos[0] - x;
    DeltaPos[1] = MousePos[1] - y;

    MousePos[0] = x;
    MousePos[1] = y;

    if(MouseDown)
    {
        Matrices::View = glm::rotate(Matrices::View, (float)DeltaPos[0], vec3(0,-1,0));
        Matrices::View = glm::rotate(Matrices::View, (float)DeltaPos[1], vec3(0,0,-1));

        mat4 mattemp = Matrices::View;
        vec4 temp = glm::column(Matrices::View, 0);
//        CameraPos = temp.swizzle(glm::X,glm::Y, glm::Z);

//        temp = glm::column(Matrices::View, 1);
//        CameraFocus = temp.swizzle(glm::X,glm::Y, glm::Z);
    }
}

void OGLContext::MouseScrollCallback(int scroll)
{
//    int DeltaScroll = MouseScroll - scroll;
//    MouseScroll = scroll;

//    vec3 deltaVec = CameraPos - CameraFocus;

//    deltaVec *= DeltaScroll;

//    Matrices::View = glm::translate(Matrices::View, deltaVec);

//    vec4 temp = glm::column(Matrices::View, 0);
//    CameraPos = temp.swizzle(glm::X,glm::Y, glm::Z);

//    temp = glm::column(Matrices::View, 1);
//    CameraFocus = temp.swizzle(glm::X,glm::Y, glm::Z);
}
