//
// Created by robin on 19.08.18.
//

#include "Window.h"

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
    return m_window != nullptr;
}

GLFWwindow *ly::Window::get()
{
    return m_window;
}



