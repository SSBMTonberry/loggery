//
// Created by robin on 19.08.18.
//

#ifndef LOGGERY_WINDOW_H
#define LOGGERY_WINDOW_H

#include <stdio.h>
#include <string>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Vector.hpp"

namespace ly
{
    class Window
    {
        public:
            Window() = default;
            ~Window();
            int initialize();
            bool create(const ly::Vector2i &size, const std::string &title);

            GLFWwindow *get();
        protected:
            bool destroyWindow();

            GLFWwindow* m_window = nullptr;
            ly::Vector2i m_size;
            std::string m_title;
    };
}

#endif //LOGGERY_WINDOW_H
