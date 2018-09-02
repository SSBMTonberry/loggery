//
// Created by robin on 30.08.18.
//

#include "Text.h"

ly::Text::Text(const std::string &value, bool hasColor) : m_value{value}, m_hasColor {hasColor}
{

}

ly::Text::Text(const std::string &value, const ImVec4 &color, bool hasColor) : m_value{value}, m_color{color}, m_hasColor {hasColor}
{

}

bool ly::Text::process()
{

    if(m_hasColor) ImGui::PushStyleColor(0, m_color);
    ImGui::Text(m_value.c_str());
    if(m_hasColor) ImGui::PopStyleColor(1);
    return true;
}

bool ly::Text::hasColor() const
{
    return m_hasColor;
}

void ly::Text::setHasColor(bool hasColor)
{
    m_hasColor = hasColor;
}

const std::string_view ly::Text::getValue() const
{
    return m_value;
}

void ly::Text::setValue(const std::string &value)
{
    m_value = value;
}

const ImVec4 &ly::Text::getColor() const
{
    return m_color;
}

void ly::Text::setColor(const ImVec4 &color)
{
    m_color = color;
}


