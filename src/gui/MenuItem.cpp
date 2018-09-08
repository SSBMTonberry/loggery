//
// Created by robin on 08.09.18.
//

#include "MenuItem.h"


ly::MenuItem::MenuItem(const std::string &id) : m_id {id}
{

}

bool ly::MenuItem::process()
{
    if(ImGui::MenuItem(m_id.c_str(), m_shortcut.c_str(), m_isSelected, m_isEnabled))
    {

    }
    return false;
}

bool ly::MenuItem::isSelected() const
{
    return m_isSelected;
}

void ly::MenuItem::setSelected(bool isSelected)
{
    m_isSelected = isSelected;
}

bool ly::MenuItem::isEnabled() const
{
    return m_isEnabled;
}

void ly::MenuItem::setEnabled(bool isEnabled)
{
    m_isEnabled = isEnabled;
}

const std::string &ly::MenuItem::getShortcut() const
{
    return m_shortcut;
}

void ly::MenuItem::setShortcut(const std::string &shortcut)
{
    m_shortcut = shortcut;
}

