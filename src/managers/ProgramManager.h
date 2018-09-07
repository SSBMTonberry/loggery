//
// Created by robin on 19.08.18.
//

#ifndef LOGGERY_PROGRAMMANAGER_H
#define LOGGERY_PROGRAMMANAGER_H

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <stdio.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "../classes/Vector.hpp"
#include "../classes/Window.h"
#include "../classes/Image.h"
#include "../classes/Timer.h"
#include "../../content/files_mapper.h"
#include "../managers/LogManager.h"
#include "../forms/SystemLog.h"


namespace ly
{
    class ProgramManager
    {
        public:
            ProgramManager() = default;
            ~ProgramManager();

            int initialize(const ly::Vector2i &size, const std::string &title);
            int initializeGLAD();
            void initializeImGui();

            void run();

            void setCurrentWindow(ly::Window *window);
            void setSwapInterval(int swapInterval);

            Window *getCurrentWindow() const;

        private:
            int initializeGLFW();
            bool m_quit = false;
            ly::Window m_window; //The default window
            ly::Window *m_currentWindow;
            ly::LogManager m_logManager;
    };
}

#endif //LOGGERY_PROGRAMMANAGER_H
