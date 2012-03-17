#include "Renderer.h"



Renderer::Renderer()
{
    FrameCount = 0;
    LastFrame = 0.0f;
    width = 1280;
    height = 960;


    // Initialize Matrices
    CameraPos = vec3(0, 9, 12);
    CameraFocus = vec3(0,3,0);
    setPerspective(45.0f, 1.33f, 0.1f, 100.0f);
    setView(CameraPos, CameraFocus, vec3(0,1,0));
    Axes = mat3(-1, 0, 0,
                0, -1, 0,
                0, 0, -1);

    mat4 debug = Matrices::View;

    Lights::LightPos = vec3(0,-6,6);
    LightTheta = 0.0f;

    AssimpLoader aiL;
    //aiL.Import3DFromFile("pc/c001\ -\ Lighning/c001.x360out.dae");
    aiL.Import3DFromFile("/home/jordan/R8_Scene/audir8.blend");
    aiL.LoadGLTextures();
    aiL.genVAOsAndUniformBuffer();

    //Make sure nothing is in here
//    MeshArray.clear();
//    MeshArray = aiL.getMeshes();

    scene = aiL.getScene();


    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Ensure we can capture the escape key being pressed below
    glfwEnable( GLFW_STICKY_KEYS );


    //Generate FBO
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);

    //Generate Depth buffer
    glGenRenderbuffers(1, &fboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, fboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);

    //Generate Color buffer
    glGenTextures(1, &fboTexture);
    glBindTexture(GL_TEXTURE_2D, fboTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Attach color and depth buffer
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fboTexture, 0);
    glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, fboDepth);

    GLenum fboStatus = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);                                   // Check the status of our generated frame buffer

    if (fboStatus != GL_FRAMEBUFFER_COMPLETE)                                                      // If the frame buffer does not report back as complete...
    {
        cerr << "Couldn't create frame buffer" << endl;                               // ...Output an error to the console
        exit(0);                                                                                // Exit the application
    }

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void Renderer::Cleanup(void)
{

}

void Renderer::RenderFunction()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE_ARB);
    glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);


//    for(int i = 0; i < MeshArray.size(); i++)
//        MeshArray[i].Draw();

    if(scene)
        scene->Draw();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_MULTISAMPLE_ARB);
    glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);

    // Swap buffers
    glfwSwapBuffers();

    // Increment frame counter
    FrameCount++;

    /**** Move light ****/
    LastTime = CurTime;
    CurTime = glfwGetTime();
    DeltaTime = CurTime - LastFrame;
    LightTheta += (CurTime - LastTime);

    LightTheta = (LightTheta > 360.0)?(LightTheta - 360.0):LightTheta;

    vec3 temp = vec3(0, -3, 3);

    Lights::LightPos.x = temp.x * glm::cos(LightTheta)
                         - temp.y * glm::sin(LightTheta);

    Lights::LightPos.y = temp.y * glm::cos(LightTheta)
                         + temp.x * glm::sin(LightTheta);
    /**** Move light ****/


    // Calculate FPS
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

void Renderer::Render()
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

void Renderer::setPerspective(float fov, float aspect, float near,
                                   float far)
{
    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    Matrices::Projection = glm::perspective(fov, aspect, near, far);
}

void Renderer::setView(glm::vec3 cameraLocation, glm::vec3 focus,
                            glm::vec3 upVector)
{
    // Camera matrix
    mat4 CameraMatrix;

    CameraMatrix       = glm::lookAt(
        cameraLocation, // Camera is at (4,3,3), in World Space
        focus, // and looks at the origin
        upVector  // Head is up (set to 0,-1,0 to look upside-down)
    );

    Matrices::View = CameraMatrix;

}
void GLFWCALL Renderer::Resize(int width, int height)
{
    //glfwSetWindowSize(width, height);
    glViewport(0, 0, width, height);
    // Initialize Matrices
    setPerspective(45.0f, (double)width/(double)height, 0.1f, 100.0f);
}

void Renderer::KeyCallback(int key, int action)
{
    if(action == GLFW_PRESS)
    {
        switch(key)
        {
            case GLFW_KEY_UP:
                CameraPos.y += 0.5f;
                CameraFocus.y += 0.5f;
                Matrices::View = glm::translate(Matrices::View, normalize(-Axes[1]));
                break;
            case GLFW_KEY_DOWN:
                CameraPos.y -= 0.5f;
                CameraFocus.y -= 0.5f;
                Matrices::View = glm::translate(Matrices::View, normalize(Axes[1]));
                break;
            case GLFW_KEY_RIGHT:
                CameraPos.x += 0.5f;
                CameraFocus.x += 0.5f;
                Matrices::View = glm::translate(Matrices::View, normalize(-Axes[0]));
                break;
            case GLFW_KEY_LEFT:
                CameraPos.x -= 0.5f;
                CameraFocus.x -= 0.5f;
                Matrices::View = glm::translate(Matrices::View, normalize(Axes[0]));
            break;
            default:
                break; // Do nothing
        }
    }
}

void Renderer::MouseButtonCallback(int button, int action)
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

void Renderer::MousePosCallback(int x, int y)
{
    DeltaPos[0] = MousePos[0] - x;
    DeltaPos[1] = MousePos[1] - y;

    MousePos[0] = x;
    MousePos[1] = y;

    if(MouseDown)
    {

        // Rotate view matrix
        Matrices::View = glm::rotate(Matrices::View, (float)DeltaPos[0], vec3(0,0,-1));
        Matrices::View = glm::rotate(Matrices::View, (float)DeltaPos[1], vec3(-1,0,0));

        // Rotate axes
        Axes[2] = glm::rotateX(Axes[2],(float)DeltaPos[1]);
        Axes[2] = glm::rotateZ(Axes[2],(float)DeltaPos[0]);
        Axes[0] = glm::rotateX(Axes[0],(float)DeltaPos[1]);
        Axes[0] = glm::rotateZ(Axes[0],(float)DeltaPos[0]);
        Axes[1] = normalize(glm::cross(Axes[2], Axes[0]) );


        CameraPos = glm::rotateZ(CameraPos, (float)DeltaPos[0]);
        CameraPos = glm::rotateX(CameraPos, (float)DeltaPos[1]);

        CameraFocus = glm::rotateZ(CameraFocus, (float)DeltaPos[0]);
        CameraFocus = glm::rotateX(CameraFocus, (float)DeltaPos[1]);

    }
}

void Renderer::MouseScrollCallback(int scroll)
{
    float DeltaScroll = (MouseScroll - scroll)/10.0f;
    MouseScroll = scroll;

//    vec3 deltaVec = vec3(Axes[2].x * DeltaScroll, Axes[2].y * DeltaScroll,
//                          Axes[2].z * DeltaScroll);
    vec3 deltaVec = CameraPos - CameraFocus;
    deltaVec *= ( DeltaScroll);
//    CameraPos = CameraFocus + deltaVec;

//    setView(CameraPos, CameraFocus, vec3(0,1,0));

    Matrices::View = glm::translate(Matrices::View, deltaVec);

//    vec4 temp = glm::column(Matrices::View, 0);
//    CameraPos = temp.swizzle(glm::X,glm::Y, glm::Z);

//    temp = glm::column(Matrices::View, 1);
//    CameraFocus = temp.swizzle(glm::X,glm::Y, glm::Z);
}
