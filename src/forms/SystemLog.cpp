//
// Created by robin on 30.08.18.
//

#include "SystemLog.h"

ly::SystemLog::SystemLog(const ImVec2 &sizeOnFirstUse) : m_sizeOnFirstUse {sizeOnFirstUse}
{

}

void ly::SystemLog::add(const std::string &text, const ImVec4 &color)
{
    m_texts.emplace(m_texts.begin(), text, color);
}

void ly::SystemLog::addSuccess(const std::string &text, bool useTimestamp)
{
    std::string msg = (useTimestamp) ? fmt::format("[SUCCESS] ({0}) - {1}", getTimestamp(), text) : fmt::format("[SUCCESS] {1}", text);
    add(msg, SuccessColor);
}

void ly::SystemLog::addInfo(const std::string &text, bool useTimestamp)
{
    std::string msg = (useTimestamp) ? fmt::format("[INFO]    ({0}) - {1}", getTimestamp(), text) : fmt::format("[INFO] {1}", text);
    add(msg, InfoColor);
}

void ly::SystemLog::addWarning(const std::string &text, bool useTimestamp)
{
    std::string msg = (useTimestamp) ? fmt::format("[ERROR]   ({0}) - {1}", getTimestamp(), text) : fmt::format("[ERROR] {1}", text);
    add(msg, ErrorColor);
}

void ly::SystemLog::addError(const std::string &text, bool useTimestamp)
{
    std::string msg = (useTimestamp) ? fmt::format("[ERROR]   ({0}) - {1}", getTimestamp(), text) : fmt::format("[ERROR] {1}", text);
    add(msg, ErrorColor);
}

void ly::SystemLog::clear()
{
    m_texts.clear();
    m_filteredTexts.clear();
}

std::string ly::SystemLog::getTimestamp(bool includeDate)
{
    auto now = std::chrono::system_clock::now();
    time_t cftime = std::chrono::system_clock::to_time_t(now);
    std::string timefmt = fmt::format("{0:%Y.%m.%d %H:%M:%S}", *std::localtime(&cftime));
    return timefmt;
}

bool ly::SystemLog::process()
{
    if(m_isVisible)
    {
        ImGui::Begin(ID.c_str(), &m_isVisible, m_sizeOnFirstUse);
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

std::vector<ly::Text> ly::SystemLog::getFilteredTexts(const std::string_view &filter)
{
    std::vector<ly::Text> filteredTexts;
    std::copy_if(m_texts.begin(), m_texts.end(),
                 std::back_inserter(filteredTexts),
                 [&filter](const ly::Text& s) { return s.getValue().find(filter) != std::string::npos; });

    return filteredTexts;
}
