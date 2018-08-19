//
// Created by robin on 19.08.18.
//

#ifndef LOGGERY_WINDOW_H
#define LOGGERY_WINDOW_H

#include <stdio.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Vector.hpp"

namespace ly
{
    class Window
    {
        public:
            Window();
            ~Window();
            int initialize();
            bool create();

        protected:
            bool destroyWindow();
            GLFWwindow* m_window = nullptr;
    };
}

#endif //LOGGERY_WINDOW_H
