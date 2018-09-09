//
// Created by robin on 08.09.18.
//

#ifndef LOGGERY_MENUITEM_H
#define LOGGERY_MENUITEM_H

#include "imgui/imgui.h"
#include <string>
#include <vector>
#include <functional>
namespace ly
{
    class MenuItem
    {
        typedef std::function<void(MenuItem* )> func_menuitem; //OnCancel(), for instance
        public:
            explicit MenuItem(const std::string &id, const std::string &shortcut = "");

            bool process();

            MenuItem * addMenuItem(const std::string &id, const std::string &shortcut = "");

            void registerOnChosenCallback(const func_menuitem &cb);

            void setId(const std::string &id);
            void setShortcut(const std::string &shortcut);
            void setSelected(bool isSelected);
            void setEnabled(bool isEnabled);

            const std::string &getId() const;
            const std::string &getShortcut() const;
            bool isSelected() const;
            bool isEnabled() const;

        protected:
            std::vector<MenuItem> m_childMenuItems;

            std::vector<func_menuitem> m_callbackOnChosen;
            std::string m_id;
            std::string m_shortcut;

            bool m_isSelected = false;
            bool m_isEnabled = true;
    };
}

#endif //LOGGERY_MENUITEM_H
