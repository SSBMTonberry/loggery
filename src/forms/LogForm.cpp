//
// Created by robin on 30.08.18.
//

#include "LogForm.h"

ly::LogForm::LogForm() : m_id {"Testlog###undefined_id"}
{

}

ly::LogForm::LogForm(const fs::path &path, const ImVec2 &sizeOnFirstUse) : m_path {path}, m_sizeOnFirstUse {sizeOnFirstUse}
{
    loadFile(m_path);
}

bool ly::LogForm::process()
{
    if(m_isVisible)
    {
        ImGui::Begin(m_id.c_str(), &m_isVisible, m_sizeOnFirstUse);
        //ImGui::BeginChild("debug_child_1", {-1, 60}, true, 0);
        if (m_filter.process())
        {
            m_filteredTexts = getFilteredTexts(m_filter.getValue().data());
        }

        showProperties();

        //if(ImGui::SmallButton("Clear log"))
        //{
        //    //clear();
        //}
        //ImGui::EndChild();

        ImGui::BeginChild("debug_child_2", {-1, -1}, false, 0);
        processProperties();
        if (!m_filter.getValue().empty())
        {
            if(!m_limitLines.first)
            {
                for (auto &text : m_filteredTexts)
                    text.process();
            }
            else
            {
                if(m_limitLines.second < m_filteredTexts.size())
                {
                    for(unsigned long i = (m_filteredTexts.size() - m_limitLines.second); i < m_filteredTexts.size(); ++i)
                        m_filteredTexts[i].process();
                }
                else
                {
                    for (auto &text : m_filteredTexts)
                        text.process();
                }
            }
        }
        else
        {
            if(!m_limitLines.first)
            {
                for (auto &text : m_texts)
                    text.process();
            }
            else
            {
                if(m_limitLines.second < m_texts.size())
                {
                    for(unsigned long i = (m_texts.size() - m_limitLines.second); i < m_texts.size(); ++i)
                        m_texts[i].process();
                }
                else
                {
                    for (auto &text : m_texts)
                        text.process();
                }
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
    m_texts.clear();
    m_filteredTexts.clear();
    if(fs::exists(path) && fs::is_regular_file(path))
    {
        m_path = path;
        m_lastUpdate = fs::last_write_time(m_path);
        m_id = generateId(path);
        ly::Timer timer;
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
        SystemLog::get()->addSuccess(fmt::format("File \"{0}\" ({1} lines) successfully loaded in {2} seconds", path.string(), lineno, timer.getTotalDuration().count()));
        return true;
    }
    else
        SystemLog::get()->addError(fmt::format("File \"{0}\" not found!", path.string()));

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

std::string ly::LogForm::generateId(const fs::path &path)
{
    return fmt::format("{0}###{1}", path.filename().string(), path.string());
}

void ly::LogForm::showProperties()
{
    ImGui::Checkbox("Limit lines", &m_limitLines.first);
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("Will limit all the lines shown to the limit to the right. \n"
                          "It's important to notice that filtering still is based on the full data.");

    ImGui::SameLine();
    ImGui::InputInt("Limit to", &m_limitLines.second);
    ImGui::Checkbox("Always scroll max", &m_alwaysSetScrollMax);
    ImGui::Checkbox("Auto-update log", &m_autoUpdate);
}

void ly::LogForm::processProperties()
{
    //Process
    if(m_alwaysSetScrollMax) ImGui::SetScrollY(ImGui::GetScrollMaxY());
    if(m_autoUpdate)
    {
        auto fileWriteTime = fs::last_write_time(m_path);
        if(fileWriteTime != m_lastUpdate)
        {
            SystemLog::get()->addInfo(fmt::format("File '{0}' has changed. Reloading...", m_path.filename().string()));
            loadFile(m_path);
        }
    }
}



