//
// Created by robin on 29.08.18.
//

#include "Textbox.h"

ly::Textbox::Textbox() : m_id {"undefined"}, m_size {25}
{

}

ly::Textbox::Textbox(const std::string &id, size_t size) : m_id {id}, m_size {size}
{

}

const std::string &ly::Textbox::getId() const
{
    return m_id;
}

/*!
 * ID is the label title of the Textbox. If using ### followed by an id, this id will be hidden, and represent
 * the internal ID used by ImGui.
 * @param id
 */
void ly::Textbox::setId(const std::string &id)
{
    m_id = id;
}

const std::string &ly::Textbox::getValue() const
{
    return m_value;
}

void ly::Textbox::setValue(const std::string &value)
{
    m_value = value;
}

size_t ly::Textbox::getSize() const
{
    return m_size;
}

void ly::Textbox::setSize(size_t size)
{
    m_size = size;
}

ImGuiInputTextFlags ly::Textbox::getFlags() const
{
    return m_flags;
}

void ly::Textbox::setFlags(ImGuiInputTextFlags flags)
{
    m_flags = flags;
}

bool ly::Textbox::isVisible() const
{
    return m_isVisible;
}

void ly::Textbox::setVisible(bool visible)
{
    m_isVisible = visible;
}


bool ly::Textbox::process()
{
    if(!m_isVisible)
        return false;

    char buf[m_size];
    strncpy(buf, m_value.c_str(), sizeof(buf));
    bool isChanged = false;

    if (ImGui::InputText(m_id.c_str(), buf, m_size, m_flags))
        isChanged = true;

    m_value = buf;

    return isChanged;
}