//
// Created by robin on 19.08.18.
//

#include "Window.h"

bool filesHaveBeenDragDropped = false;
std::vector<fs::path> dragDroppedFiles;

static void drop_callback(GLFWwindow* window, int count, const char** paths)
{
    filesHaveBeenDragDropped = true;
    ly::SystemLog::get()->addInfo(fmt::format("Drag-dropped {0} files!", count));
    dragDroppedFiles.clear();
    for (int i = 0; i < count;  i++)
    {
        fs::path path {paths[i]};
        if(fs::exists(path) && fs::is_regular_file(path))
        {
            dragDroppedFiles.emplace_back(path);
            ly::SystemLog::get()->addInfo(fmt::format("Drag-dropped file: {0}", path.string()));
        }
        else if(!fs::is_regular_file(path))
        {
            ly::SystemLog::get()->addError(fmt::format("File '{0}' is not a valid file type", path.string()));
        }
        //handle_dropped_file(paths[i]);
    }

}

ly::Window::~Window()
{
    destroyWindow();
}

int ly::Window::initialize()
{
    return 0;
}

/*!
 * Destroys m_window, if it exists.
 * @return
 */
bool ly::Window::destroyWindow()
{
    if(m_window)
    {
        glfwDestroyWindow(m_window);
        return true;
    }
    return false;
}

bool ly::Window::create(const ly::Vector2i &size, const std::string &title)
{
    destroyWindow();
    m_size = size;
    m_title = title;
    m_window = glfwCreateWindow(m_size.x, m_size.y, m_title.c_str(), NULL, NULL);
    glfwSetDropCallback(m_window, drop_callback);
    return m_window != nullptr;
}

GLFWwindow *ly::Window::get()
{
    return m_window;
}

void ly::Window::registerDragDropFileCallback(const ly::Window::func_path &cb)
{
    m_callbackDragDropFiles.emplace_back(cb);
}

bool ly::Window::processCallbacks()
{
    if(filesHaveBeenDragDropped)
    {
        filesHaveBeenDragDropped = false;
        SystemLog::get()->addInfo(fmt::format("Drag-drop detected! Calling {0} callbacks...", m_callbackDragDropFiles.size()));
        for (auto &callback : m_callbackDragDropFiles)
            callback(dragDroppedFiles);
    }
}



