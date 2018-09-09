//
// Created by robin on 08.09.18.
//

#ifndef LOGGERY_MENUBAR_H
#define LOGGERY_MENUBAR_H

#include "imgui/imgui.h"
#include <string>
#include "MenuItem.h"
namespace ly
{
    class MenuBar
    {
        public:
            MenuBar(bool isMainMenu);

            void process();

            MenuItem * addMenuItem(const std::string &id, const std::string &shortcut = "");

        protected:
            bool processMenuItems();

            bool m_isMainMenu = false;
            ImVec2 m_menuSize = {0,0};
            std::vector<MenuItem> m_menuItems;
    };
}

#endif //LOGGERY_MENUBAR_H
