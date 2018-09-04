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

int ly::ProgramManager::initialize(const ly::Vector2i &size, const std::string &title)
{
    int result = initializeGLFW();
    bool windowResult = m_window.create(size, title);

    setCurrentWindow(&m_window);
    setSwapInterval(0);

    initializeGLAD();
    initializeImGui();

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


    return 0;
}

void ly::ProgramManager::setCurrentWindow(ly::Window *window)
{
    m_currentWindow = window;
    glfwMakeContextCurrent(m_currentWindow->get());
}

/*!
 * Sets the swap interval for the current window.
 * 0 = no fps limit,
 * 1 = using v-sync (60 fps, but I experience some delay...
 * 2 = about 30 fps.
 * 3 = about 20 fps.
 * @param swapInterval
 */
void ly::ProgramManager::setSwapInterval(int swapInterval)
{
    glfwSwapInterval(swapInterval); // Enable vsync with 1
}

ly::Window *ly::ProgramManager::getCurrentWindow() const
{
    return m_currentWindow;
}

/*!
 * Do this after the regular initialization is done and current window has been set.
 */
void ly::ProgramManager::initializeImGui()
{
    // Setup Dear ImGui binding
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

    ImGui_ImplGlfw_InitForOpenGL(m_currentWindow->get(), true);
    ImGui_ImplOpenGL3_Init();

    // Setup style
    ImGui::StyleColorsDark();

}

void ly::ProgramManager::run()
{
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ly::Image image {(void *)files_mapper::test::_MARIO_PNG, (int)files_mapper::test::_MARIO_PNG_SIZE};
    ly::Timer timer;
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);

    SystemLog::get()->addSuccess("OK!");
    SystemLog::get()->addError("OH NO!");

    LogForm testLog {"Testlog###test_id2"};
    testLog.loadFile("../test_logs/test.log");
    while (!glfwWindowShouldClose(m_currentWindow->get()) && !m_quit)
    {

        if(timer.update(mode->refreshRate))
        {
            // Poll and handle events (inputs, window resize, etc.)
            // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
            // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
            // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
            // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
            glfwPollEvents();

            if (ImGui::IsKeyPressed(GLFW_KEY_ESCAPE))
                m_quit = true;


            // Start the ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // 1. Show a simple window.
            // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets automatically appears in a window called "Debug".
            /*{
                static float f = 0.0f;
                static int counter = 0;
                ImGui::Text(
                        "Hello, world!");                           // Display some text (you can use a format string too)
                ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::ColorEdit3("clear color", (float *) &clear_color); // Edit 3 floats representing a color

                ImGui::Checkbox("Demo Window",
                                &show_demo_window);      // Edit bools storing our windows open/close state
                ImGui::Checkbox("Another Window", &show_another_window);

                if (ImGui::Button(
                        "Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
                    counter++;
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);


                ImGui::Image((void *) image.getTextureID(), {64, 64}, {0, 0}, {1.f, 1.f}); //, uv0, uv1);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                            ImGui::GetIO().Framerate);
            }*/

            // 2. Show another simple window. In most cases you will use an explicit Begin/End pair to name your windows.
            /*if (show_another_window)
            {
                ImGui::Begin("Another Window", &show_another_window);
                ImGui::Text("Hello from another window!");
                if (ImGui::Button("Close Me"))
                    show_another_window = false;
                ImGui::End();
            }*/

            // 3. Show the ImGui demo window. Most of the sample code is in ImGui::ShowDemoWindow(). Read its code to learn more about Dear ImGui!
            if (show_demo_window)
            {
                ImGui::SetNextWindowPos(ImVec2(650, 20),
                                        ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
                ImGui::ShowDemoWindow(&show_demo_window);
            }

            testLog.process();
            SystemLog::get()->process();
            // Rendering
            ImGui::Render();
            int display_w, display_h;
            //glfwMakeContextCurrent(window);
            glfwGetFramebufferSize(m_currentWindow->get(), &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            //glfwMakeContextCurrent(window);
            glfwSwapBuffers(m_currentWindow->get());
        }
    }
}

int ly::ProgramManager::initializeGLAD()
{
    if(!gladLoadGL()) {
        printf("Something went wrong!\n");
        return 1;
    }

    printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);
    return 0;
}
