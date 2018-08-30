//
// Created by robin on 30.08.18.
//

#ifndef LOGGERY_TEXT_H
#define LOGGERY_TEXT_H

#include "imgui/imgui.h"
#include <string>
#include <vector>
#include "../classes/Color.hpp"

namespace ly
{
    class Text
    {
        public:
            Text() = default;
            Text(const std::string &value, bool hasColor = false);

            bool process();

            void setHasColor(bool hasColor);
            void setValue(const std::string &value);
            void setColor(const ImVec4 &color);

            bool hasColor() const;
            const std::string_view getValue() const;
            const ImVec4 &getColor() const;

        protected:
            bool m_hasColor = false;
            std::string m_value;
            ImVec4 m_color {255, 255, 255, 255}; //White

    };
}

#endif //LOGGERY_TEXT_H
