#include "FrameBufferObject.h"

FrameBufferObject::FrameBufferObject()
{

}

FrameBufferObject::FrameBufferObject(int w, int h, int aaSamples, bool deferred)
{
    // Set FBO parameters
    width = w;
    height = h;
    samples = aaSamples;
    numBuffers = (deferred)?3:1;

    //Generate FBO
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);

    //Generate Depth buffer
    glGenTextures(1, &fboDepth);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, fboDepth);
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_DEPTH_COMPONENT24, width, height, false);
    glTextureParameteriEXT(fboDepth, GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteriEXT(fboDepth, GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Attach depth
    glNamedFramebufferTextureEXT(fbo, GL_DEPTH_ATTACHMENT, fboDepth, 0);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

    //Generate Color buffer
    fboTextures = new GLuint[numBuffers];
    glGenTextures(numBuffers, fboTextures);

    for(int i = 0; i < numBuffers; i++)
    {

        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, fboTextures[i]);
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGBA16, width, height, false);
        glTextureParameteriEXT(fboTextures[i], GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteriEXT(fboTextures[i], GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Attach color
        attachments.push_back(GL_COLOR_ATTACHMENT0 + i);
        glNamedFramebufferTextureEXT(fbo, attachments[i], fboTextures[i], 0);

        // Make sure color buffer isn't bound
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
    }



    GLenum fboStatus = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);                                   // Check the status of our generated frame buffer

    if (fboStatus != GL_FRAMEBUFFER_COMPLETE)                                                      // If the frame buffer does not report back as complete...
    {
        cerr << "Couldn't create frame buffer" << endl;                               // ...Output an error to the console
        exit(0);                                                                                // Exit the application
    }

    float aspect = 1.0f;//(float)width/(float)height;
    ortho = gtc::matrix_transform::ortho(-aspect,aspect, 1.0f, -1.0f);
    model = mat4(1.0);
    view = gtc::matrix_transform::lookAt( vec3(0,0,1), vec3(0,0,0), vec3(0,1,0));

    // Screen sized rectangle for drawing
    vector<GLfloat> Pos = { -aspect, -1.0f, -1.0f,  aspect, -1.0f, -1.0f,  -aspect, 1.0f, -1.0f,  aspect, 1.0f, -1.0f };
    vector<GLfloat> tCoords = { 0.0f, 0.0f,  1.0f, 0.0f,  0.0f, 1.0f,  1.0f, 1.0f };
    vector<GLuint> Indices = { 0, 1, 3,  0, 3, 2};

    bod.AddAttribute(Pos, 3, 0);
    bod.AddAttribute(tCoords, 2, 1);

    Vao = new VertexArrayObject();
    Vao->BindBuffers(bod, Indices);

    mats.texCount = numBuffers + 1;

    sp = new ShaderProgram("FBODraw.vert", "FBODraw.frag");

    if(sp)
    {
        sp->SetMaterial(mats);
    }

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void FrameBufferObject::Bind()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
    glDrawBuffers(numBuffers, &attachments[0]);

    // Set viewport
    glViewport(0, 0, width, height);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE_ARB);
    glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
}

void FrameBufferObject::RenderToScreen()
{


    Matrices::PushMatrix(PROJECTION_STACK, ortho);
    Matrices::PushMatrix(VIEW_STACK, view);
    Matrices::PushMatrix(MODEL_STACK, model);


    for(int i = 0; i < numBuffers; i++)
    {
        glActiveTexture(GL_TEXTURE0 +i);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, fboTextures[i]);
    }

    glActiveTexture(GL_TEXTURE0 + numBuffers);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, fboDepth);

    if(sp)
        sp->Bind();

    // Draw rectangle
    if(Vao)
        Vao->Draw();

    if(sp)
        sp->Unbind();

    glActiveTexture(GL_TEXTURE0 + numBuffers);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

    for(int i = 0; i < numBuffers; i++)
    {
        glActiveTexture(GL_TEXTURE0 +i);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
    }

    Matrices::PopMatrix(PROJECTION_STACK);
    Matrices::PopMatrix(VIEW_STACK);
    Matrices::PopMatrix(MODEL_STACK);
}

void FrameBufferObject::Unbind()
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_MULTISAMPLE_ARB);
    glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);

    //glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
    //glDrawBuffer(GL_BACK);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}


