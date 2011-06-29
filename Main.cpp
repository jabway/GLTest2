#include "Framework.h"
#include "OGLContext.h"


using namespace std;

// Function prototypes
void logRedirect();
void logUnredirect();
void Resize(int width, int height);
void KeyCallback(int key, int action);
void MousePosCallback(int x, int y);
void MouseButtonCallback(int button, int action);
void MouseScrollCallback(int scroll);

// Variables
streambuf *ferrbuf, *errbackup, *foutbuf, *outbackup;
ofstream ferrstr, foutstr;
OGLContext *ogc;


int main()
{
    logRedirect();

    ogc = new OGLContext();

    if(ogc)
    {
        //GLFW callbacks can't be set within classes
        glfwSetWindowSizeCallback( Resize);
        glfwSetKeyCallback(KeyCallback);
        glfwEnable( GLFW_KEY_REPEAT );
        //glfwEnable( GLFW_STICKY_MOUSE_BUTTONS);
        glfwSetMousePosCallback(MousePosCallback);
        glfwSetMouseButtonCallback(MouseButtonCallback);
        glfwSetMouseWheelCallback(MouseScrollCallback);


//        ogc->setPerspective(45.0f, 4.0f/3.0f, 0.1f, 100.0f);
//        ogc->setView(glm::vec3(-9,15,20), // Camera is at (4,3,3), in World Space
//                glm::vec3(0,2,0), // and looks at the origin
//                glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down
//                );

        ogc->Render();
    }

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

void Resize(int width, int height)
{
    ogc->Resize(width, height);
}

void KeyCallback(int key, int action)
{
    ogc->KeyCallback(key, action);
}

void MouseButtonCallback(int button, int action)
{
    ogc->MouseButtonCallback(button, action);
}

void MousePosCallback(int x, int y)
{
    ogc->MousePosCallback(x, y);
}

void MouseScrollCallback(int scroll)
{
    ogc->MouseScrollCallback(scroll);
}
