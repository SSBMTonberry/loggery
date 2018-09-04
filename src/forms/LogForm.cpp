//
// Created by robin on 30.08.18.
//

#include "LogForm.h"

ly::LogForm::LogForm() : m_id {"Testlog###undefined_id"}
{

}

ly::LogForm::LogForm(const std::string &id, const ImVec2 &sizeOnFirstUse) : m_id {id}, m_sizeOnFirstUse {sizeOnFirstUse}
{

}

bool ly::LogForm::process()
{
    if(m_isVisible)
    {
        ImGui::Begin(m_id.c_str(), &m_isVisible, m_sizeOnFirstUse);
        ImGui::BeginChild("debug_child_1", {-1, 60}, true, 0);
        if (m_filter.process())
        {
            m_filteredTexts = getFilteredTexts(m_filter.getValue().data());
        }
        //ImGui::SameLine();
        if(ImGui::SmallButton("Clear log"))
        {
            //clear();
        }
        ImGui::EndChild();

        ImGui::BeginChild("debug_child_2", {-1, -1}, false, 0);
        if (!m_filter.getValue().empty())
        {
            for (auto &text : m_filteredTexts)
            {
                text.process();
            }
        }
        else
        {
            for (auto &text : m_texts)
            {
                text.process();
            }
        }
        ImGui::EndChild();
        ImGui::End();

        return true;
    }
    return false;
}

std::vector<ly::Text> ly::LogForm::getFilteredTexts(const std::string_view &filter)
{
    std::vector<ly::Text> filteredTexts;
    std::copy_if(m_texts.begin(), m_texts.end(),
                 std::back_inserter(filteredTexts),
                 [&filter](const ly::Text& s) { return s.getValue().find(filter) != std::string::npos; });

    return filteredTexts;
}

bool ly::LogForm::loadFile(const fs::path &path)
{
    if(fs::exists(path) && fs::is_regular_file(path))
    {
        std::ifstream ifs(path); //"../../test_logs/test.log");
        if (!ifs)
        {
            return false;
        }

        std::string line;
        m_texts.clear();
        int lineno = 1;
        while (std::getline(ifs, line))
        {
            m_texts.emplace_back(fmt::format("[{0}] {1}", lineno, line));
            ++lineno;
        }
        return true;
    }
    return false;
}

bool ly::LogForm::isVisible() const
{
    return m_isVisible;
}

void ly::LogForm::setVisible(bool isVisible)
{
    m_isVisible = isVisible;
}

void ly::LogForm::setSizeOnFirstUse(const ImVec2 &sizeOnFirstUse)
{
    m_sizeOnFirstUse = sizeOnFirstUse;
}

const ImVec2 &ly::LogForm::getSizeOnFirstUse() const
{
    return m_sizeOnFirstUse;
}


