//
// Created by robin on 08.09.18.
//

#ifndef LOGGERY_MENUBAR_H
#define LOGGERY_MENUBAR_H

#include "imgui/imgui.h"
#include <string>

namespace ly
{
    class MenuBar
    {
        public:
            MenuBar(const std::string &id, bool isMainMenu);

            void process();

        protected:
            std::string m_id;

            bool m_isMainMenu = false;
    };
}

#endif //LOGGERY_MENUBAR_H
