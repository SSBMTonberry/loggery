//
// Created by robin on 08.09.18.
//

#include "MenuItem.h"


ly::MenuItem::MenuItem(const std::string &id, const std::string &shortcut) : m_id {id}, m_shortcut {shortcut}
{

}

bool ly::MenuItem::process()
{
    bool isPressed = false;
    if(m_childMenuItems.empty())
    {
        if (ImGui::MenuItem(m_id.c_str(), m_shortcut.c_str(), m_isSelected, m_isEnabled))
        {
            for(auto &callback : m_callbackOnChosen)
                callback(this);
            isPressed = true;
        }
    }
    else
    {
        if(ImGui::BeginMenu(m_id.c_str(), m_isEnabled))
        {
            for(auto &item : m_childMenuItems)
            {
                if(item.process())
                {
                    for(auto &callback : m_callbackOnChosen)
                        callback(&item);
                    isPressed = true;
                }
            }
            ImGui::EndMenu();
        }
    }


    return isPressed;
}

ly::MenuItem *ly::MenuItem::addMenuItem(const std::string &id, const std::string &shortcut)
{
    MenuItem &item = m_childMenuItems.emplace_back(id, shortcut);
    return &item;
}

void ly::MenuItem::registerOnChosenCallback(const ly::MenuItem::func_menuitem &cb)
{
    m_callbackOnChosen.emplace_back(cb);
}

const std::string &ly::MenuItem::getId() const
{
    return m_id;
}

void ly::MenuItem::setId(const std::string &id)
{
    m_id = id;
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


