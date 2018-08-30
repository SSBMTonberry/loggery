//
// Created by robin on 29.08.18.
//

#ifndef LOGGERY_TEXTBOX_H
#define LOGGERY_TEXTBOX_H

#include <string>
#include <string_view>
#include "imgui/imgui.h"
#include "imgui/misc/stl/imgui_stl.h"
namespace ly
{
    class Textbox
    {
        public:
            Textbox();
            Textbox(const std::string &id, size_t size = 0);

            bool process();

            void setId(const std::string &id);
            void setValue(const std::string &value);
            void setFlags(ImGuiInputTextFlags flags);
            void setSize(size_t size);
            void setVisible(bool visible);

            bool isVisible() const;
            const std::string &getId() const;
            const std::string_view getValue() const;
            ImGuiInputTextFlags getFlags() const;
            size_t getSize() const;

        private:
            std::string m_id;
            std::string m_value;
            size_t m_size;
            bool m_isVisible = true;
            ImGuiInputTextFlags m_flags = 0;
    };
}

#endif //LOGGERY_TEXTBOX_H
