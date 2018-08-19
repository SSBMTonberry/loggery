//
// Created by robin on 19.08.18.
//

#include "ProgramManager.h"

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

ly::ProgramManager::~ProgramManager()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
}

int ly::ProgramManager::initialize()
{
    if(int result = initializeGLFW() != 0)
        return result;
}

int ly::ProgramManager::initializeGLFW()
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif



    if(!gladLoadGL()) {
        printf("Something went wrong!\n");
        return 1;
    }
    printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);
    return 0;
}
