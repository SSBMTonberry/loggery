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
#include "../forms/SystemLog.h"
#include <functional>

#if MSVC
#include <filesystem>
    namespace fs = std::filesystem;
#elif MINGW
#if __MINGW64_VERSION_MAJOR > 5
        #include <filesystem>
        namespace fs = std::filesystem;
    #else
        #include <experimental/filesystem>
        namespace fs = std::experimental::filesystem;
    #endif
#elif APPLE
#include <experimental/filesystem>
    namespace fs = std::experimental::filesystem;
#else
#if __GNUC__ < 8 //GCC major version less than 8
#include <experimental/filesystem>
        namespace fs = std::experimental::filesystem;
#else
#include <filesystem>
namespace fs = std::filesystem;
#endif
#endif

namespace ly
{
    class Window
    {
        typedef std::function<void(std::vector<fs::path>)> func_path;
        public:
            Window() = default;
            ~Window();
            int initialize();
            bool create(const ly::Vector2i &size, const std::string &title);

            bool processCallbacks();

            void registerDragDropFileCallback(const func_path &cb);

            GLFWwindow *get();
        protected:
            bool destroyWindow();

            std::vector<func_path> m_callbackDragDropFiles;
            GLFWwindow* m_window = nullptr;
            ly::Vector2i m_size;
            std::string m_title;
    };
}

#endif //LOGGERY_WINDOW_H
