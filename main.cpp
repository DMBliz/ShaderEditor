#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imnodes.h>
#include "App.h"
#include <stdio.h>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif


static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void keyPressedCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    App::buttonPressed(key, action, mods);
}

void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    App::mouseScroll(yoffset);
}

void cursorMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
    App::mouseMoved(xpos, ypos);
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    App::mouseButtonAction(button, action);
}

int main(int, char**)
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(1500, 900, "Shader editor", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, keyPressedCallback);
    glfwSetScrollCallback(window, mouseScrollCallback);
    glfwSetCursorPosCallback(window, cursorMoveCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); 
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.IniFilename = NULL;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    ImGui::StyleColorsDark();

    ImNodes::CreateContext();

    ImNodes::StyleColorsDark();

    ImNodes::GetIO().EmulateThreeButtonMouse.Modifier = &ImGui::GetIO().KeyAlt;


    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    App::init(1500, 900);
    bool showDock = true;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        App::drawUI();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        App::drawScene();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwMakeContextCurrent(window);
        glfwSwapBuffers(window);

        if (App::needCopy())
        {
            glfwSetClipboardString(window, App::getShaderCode().c_str());
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImNodes::DestroyContext();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}