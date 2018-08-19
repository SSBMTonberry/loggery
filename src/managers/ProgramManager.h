//
// Created by robin on 19.08.18.
//

#ifndef LOGGERY_PROGRAMMANAGER_H
#define LOGGERY_PROGRAMMANAGER_H

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <stdio.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "../classes/Vector.hpp"

namespace ly
{
    class ProgramManager
    {
        public:
            ProgramManager() = default;
            ~ProgramManager();

            int initialize();
        private:
            int initializeGLFW();
    };
}

#endif //LOGGERY_PROGRAMMANAGER_H
