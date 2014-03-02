// sample.cc - public domain
// authored from 2012-2013 by Adrien Herubel


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <cmath>
#include <iostream>

#include "imgui.hpp"
#include "imguiGL.hpp"

#include <GLFW/glfw3.h>

unsigned int KeyUNICODE=0;

void GetUNICODE(GLFWwindow *window, unsigned int unicode ){
    KeyUNICODE = unicode;
}

void GetControlKEY(GLFWwindow *window, int glfw_key, int sys_scancode, int glfw_action, int glfw_mods){
    if(glfw_action == GLFW_PRESS)
    {
        switch (glfw_key)
        {
        case GLFW_KEY_BACKSPACE:
            KeyUNICODE=0x08;
            break;
        case GLFW_KEY_ENTER:
            KeyUNICODE=0x0D;
            break;
        default:
            break;
        }
    }
    if(glfw_action == GLFW_RELEASE)
        KeyUNICODE = 0;
}

int main( int argc, char **argv )
{
    int width = 1024, height=640;

    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit( EXIT_FAILURE );
    }

    // Open a window and create its OpenGL context
$apple( $GL3(
    glfwOpenWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
) )
    GLFWmonitor *monitor = 0; /* 0 for windowed, glfwGetPrimaryMonitor() for primary monitor, etc */
    GLFWwindow *shared = 0;
    GLFWwindow* window = glfwCreateWindow(width, height, "imgui sample", monitor, shared);
    if( !window )
    {
        fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    glfwMakeContextCurrent(window);

$apple( $GL3(
    glewExperimental = GL_TRUE;
) )
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
          /* Problem: glewInit failed, something is seriously wrong. */
          fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
          exit( EXIT_FAILURE );
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode( window, GLFW_STICKY_KEYS, GL_TRUE );

    // Enable vertical sync (on cards that support it)
    glfwSwapInterval( 1 );

    // Init UI
    if (!imguiRenderGLInit())
    {
        fprintf(stderr, "Could not init GUI renderer.\n");
        exit(EXIT_FAILURE);
    }
    if (!imguiRenderGLFontInit(1, 14.f, "Ubuntu-B.ttf"))
    {
        fprintf(stderr, "Could not init GUI renderer.\n");
        exit(EXIT_FAILURE);
    }

    glClearColor(0.8f, 0.8f, 0.8f, 1.f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);

    // imgui states
    bool checked1 = false;
    bool checked2 = false;
    bool checked3 = true;
    bool checked4 = false;
    float value1 = 50.f;
    float value2 = 30.f;
    float value3A = 33.f, value3B = 66.f;
    float value4A = 33.f, value4B = 66.f;
    int scrollarea1 = 0;
    int scrollarea2 = 0;

    // glfw scrolling
    int glfwscroll = 0;

    //glfw callback
    glfwSetCharCallback(window, GetUNICODE);
    glfwSetKeyCallback(window, GetControlKEY);
    char input[15];
    sprintf(input, "\1type here");

    // main loop
    while( !glfwWindowShouldClose(window) )
    {
        glfwGetFramebufferSize(window, &width, &height);
        if( width * height <= 1 ) {
            glfwSwapBuffers(window);
            glfwPollEvents();
            continue;
        }
        glViewport(0, 0, width, height);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Mouse states
        unsigned char mousebutton = 0;
        int currentglfwscroll = 0; //glfwGetMouseWheel();
        int mscroll = 0;
        if (currentglfwscroll < glfwscroll)
            mscroll = 2;
         if (currentglfwscroll > glfwscroll)
            mscroll = -2;
        glfwscroll = currentglfwscroll;
        double mousex; double mousey;
        glfwGetCursorPos(window, &mousex, &mousey);
        mousey = height - mousey;
        int leftButton = glfwGetMouseButton( window, GLFW_MOUSE_BUTTON_LEFT );
        int rightButton = glfwGetMouseButton( window, GLFW_MOUSE_BUTTON_RIGHT );
        int middleButton = glfwGetMouseButton( window, GLFW_MOUSE_BUTTON_MIDDLE );
        int toggle = 0;
        if( leftButton == GLFW_PRESS )
            mousebutton |= IMGUI_MBUT_LEFT;

        // Draw UI
$GL2(
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        float projection[16] = { 2.f/width, 0.f, 0.f,  0.f,
                                 0.f, 2.f/height,  0.f,  0.f,
                                 0.f,  0.f, -2.f, 0.f,
                                 -1.f, -1.f,  -1.f,  1.f };
        glLoadMatrixf(projection);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glUseProgram(0);
)

        imguiBeginFrame(int(mousex), int(mousey), mousebutton, mscroll, KeyUNICODE);

        imguiBeginScrollArea("\1Scroll area", 10, 10, width / 5, height - 20, &scrollarea1);
        imguiSeparatorLine();
        imguiSeparator();

        imguiButton("\1Button");
        imguiButton("\1Disabled button", false);
        imguiItem("\1Item");
        imguiItem("\1Disabled item", false);
        toggle = imguiCheck("\1Checkbox", checked1);
        if (toggle)
            checked1 = !checked1;
        toggle = imguiCheck("\1Disabled checkbox", checked2, false);
        if (toggle)
            checked2 = !checked2;
        toggle = imguiCollapse("\1Collapse", "\1subtext", checked3);
        if (checked3)
        {
            imguiIndent();
            imguiLabel("\1Collapsible element");
            imguiUnindent();
        }
        if (toggle)
            checked3 = !checked3;
        toggle = imguiCollapse("\1Disabled collapse", "\1subtext", checked4, false);
        if (toggle)
            checked4 = !checked4;
        imguiLabel("\1Label");
        imguiValue("\1Value");

        imguiSlider("\1Slider", &value1, 0.f, 100.f, 1.f);
        imguiSlider("\1Disabled slider", &value2, 0.f, 100.f, 1.f, false);

        imguiRange("\1Range", &value3A, &value3B, 0.f, 100.f, 1.f);
        imguiRange("\1Disabled range", &value4A, &value4B, 0.f, 100.f, 1.f, false);

        imguiIndent();
        imguiLabel("\1Indented");
        imguiUnindent();
        imguiLabel("\1Unindented");

        //imguiTextInput("\1Text input", input, 15);

        imguiPair( "\1hello", "\1pair" );

        {
            static float percent = 0.f;
            percent += 0.1f;
            if( percent > 100.f ) percent = 0.f;
            imguiProgressBar( "\1progress bar", percent );
        }

        {
            const char *list[] = {"\1hello", "\1world"};
            static int choosing = 0, clicked = 0;
            imguiList("\1hello", 2, list, choosing, clicked );
        }

        {
            const char *list[] = {"\1hello", "\1world"};
            static int clicked = 0;
            imguiRadio("\1hello", 2, list, clicked );
        }

        {
            static unsigned bitmask = 0xAA;
            imguiBitmask("\1bitmask", &bitmask, 8 );
        }

        imguiEndScrollArea();

        imguiBeginScrollArea("\1Scroll area", 20 + width / 5, 500, width / 5, height - 510, &scrollarea2);
        imguiSeparatorLine();
        imguiSeparator();
        for (int i = 0; i < 100; ++i)
            imguiLabel("\1A wall of text");

        imguiEndScrollArea();
        imguiEndFrame();

#if 0
        imguiDrawText(30 + width / 5 * 2, height - 20, IMGUI_ALIGN_LEFT, "\1Free text",  imguiRGBA(32,192, 32,192));
        imguiDrawText(30 + width / 5 * 2 + 100, height - 40, IMGUI_ALIGN_RIGHT, "\1Free text",  imguiRGBA(32, 32, 192, 192));
        imguiDrawText(30 + width / 5 * 2 + 50, height - 60, IMGUI_ALIGN_CENTER, "\1Free text",  imguiRGBA(192, 32, 32,192));

        imguiDrawLine(30 + width / 5 * 2, height - 80, 30 + width / 5 * 2 + 100, height - 60, 1.f, imguiRGBA(32,192, 32,192));
        imguiDrawLine(30 + width / 5 * 2, height - 100, 30 + width / 5 * 2 + 100, height - 80, 2.f, imguiRGBA(32, 32, 192, 192));
        imguiDrawLine(30 + width / 5 * 2, height - 120, 30 + width / 5 * 2 + 100, height - 100, 3.f, imguiRGBA(192, 32, 32,192));

        imguiDrawRoundedRect(30 + width / 5 * 2, height - 240, 100, 100, 5.f, imguiRGBA(32,192, 32,192));
        imguiDrawRoundedRect(30 + width / 5 * 2, height - 350, 100, 100, 10.f, imguiRGBA(32, 32, 192, 192));
        imguiDrawRoundedRect(30 + width / 5 * 2, height - 470, 100, 100, 20.f, imguiRGBA(192, 32, 32,192));

        imguiDrawRect(30 + width / 5 * 2, height - 590, 100, 100, imguiRGBA(32, 192, 32, 192));
        imguiDrawRect(30 + width / 5 * 2, height - 710, 100, 100, imguiRGBA(32, 32, 192, 192));
        imguiDrawRect(30 + width / 5 * 2, height - 830, 100, 100, imguiRGBA(192, 32, 32,192));
#endif

        imguiRenderGLDraw(width, height);

        // Check for errors
        GLenum err = glGetError();
        if(err != GL_NO_ERROR)
        {
            fprintf(stderr, "OpenGL Error : %d %x\n", err, err );
        }

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

        // Check if the ESC key was pressed or the window was closed
        if( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
            break;
    }

    // Clean UI
    imguiRenderGLDestroy();

    // Close OpenGL window and terminate GLFW
    glfwDestroyWindow( window );
    glfwTerminate();

    exit( EXIT_SUCCESS );
}

