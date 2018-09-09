//
// Created by robin on 08.09.18.
//

#include "MenuBar.h"

ly::MenuBar::MenuBar(bool isMainMenu) : m_isMainMenu {isMainMenu}
{

}

void ly::MenuBar::process()
{
    if(m_isMainMenu)
    {
        if (ImGui::BeginMainMenuBar())
        {
            m_menuSize = ImGui::GetWindowSize();
            processMenuItems();
            ImGui::EndMainMenuBar();
        }
    }
    else
    {
        if (ImGui::BeginMenuBar())
        {
            m_menuSize = ImGui::GetWindowSize();
            processMenuItems();
            ImGui::EndMenuBar();
        }
    }
}

bool ly::MenuBar::processMenuItems()
{
    for(auto &item : m_menuItems)
        item.process();

    return false;
}

ly::MenuItem *ly::MenuBar::addMenuItem(const std::string &id, const std::string &shortcut)
{
    MenuItem &item = m_menuItems.emplace_back(id, shortcut);
    return &item;
}

