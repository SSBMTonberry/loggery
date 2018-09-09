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
#include "../gui/MenuBar.h"

#include <map>

namespace ly
{
    enum class MenuAction : unsigned
    {
        None = 0,

        //File
        QuickOpenLog,
        Quit,

        //View
        SystemLog
    };

    class ProgramManager
    {
        public:
            ProgramManager() = default;
            ~ProgramManager();

            int initialize(const ly::Vector2i &size, const std::string &title);
            void initializeMenubar();
            int initializeGLAD();
            void initializeImGui();

            void onMenuItemClicked(MenuItem *menuItem);

            void processMenuAction(const MenuAction &action);

            void run();

            void onFileDragDrop(const std::vector<fs::path> &files);

            void setCurrentWindow(ly::Window *window);
            void setSwapInterval(int swapInterval);

            Window *getCurrentWindow() const;

        private:
            int initializeGLFW();

            std::map<std::string, MenuAction> m_menuActionMap;

            bool m_quit = false;
            ly::MenuBar m_menuBar {true};
            ly::Window m_window; //The default window
            ly::Window *m_currentWindow;
            ly::LogManager m_logManager;
    };
}

#endif //LOGGERY_PROGRAMMANAGER_H
