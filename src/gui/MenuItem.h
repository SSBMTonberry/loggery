//
// Created by robin on 08.09.18.
//

#ifndef LOGGERY_MENUITEM_H
#define LOGGERY_MENUITEM_H

#include "imgui/imgui.h"
#include <string>
#include <vector>
namespace ly
{
    class MenuItem
    {
        public:
            explicit MenuItem(const std::string &id);

            bool process();

            void setShortcut(const std::string &shortcut);
            void setSelected(bool isSelected);
            void setEnabled(bool isEnabled);

            const std::string &getShortcut() const;
            bool isSelected() const;
            bool isEnabled() const;

        protected:
            std::vector<MenuItem> m_childMenuItems;

            std::string m_id;
            std::string m_shortcut;

            bool m_isSelected = false;
            bool m_isEnabled = true;
    };
}

#endif //LOGGERY_MENUITEM_H
