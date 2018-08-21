//
// Created by robin on 19.08.18.
//

#include "Window.h"

ly::Window::~Window()
{


}

int ly::Window::initialize()
{
    return 0;
}

bool ly::Window::create()
{
    destroyWindow();
    return false;
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



