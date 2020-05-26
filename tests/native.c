//========================================================================
// Win32 native handle attachment test
// Copyright (c) Camilla Löwy <elmindreda@glfw.org>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================

#define UNICODE

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#if WIN32
    #define GLFW_EXPOSE_NATIVE_WIN32
#elif GLFW_X11
asdf
#endif
    #define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>

#include <stdio.h>
#include <stdlib.h>

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}


int main(int argc, char** argv)
{
    GLFWwindow* window;
    GLFWwindow* externalWindow;
    
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }
    
    externalWindow = glfwCreateWindow( 300, 300, "Gears", NULL, NULL );

    if (!externalWindow)
        exit(EXIT_FAILURE);
#if WIN32
    HWND handle = glfwGetWin32Window(externalWindow);
    if (handle)
        window = glfwAttachWin32Window(handle, NULL);
#else
    Window handle = glfwGetX11Window(externalWindow);
    if (handle)
        window = glfwAttachX11Window(handle, NULL);
#endif

    if (!window)
    {
        glfwTerminate();
        glfwDestroyWindow(externalWindow);
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwWaitEvents();
    }

    glfwTerminate();
    glfwDestroyWindow(externalWindow);
    exit(EXIT_SUCCESS);
    return 0;
}

