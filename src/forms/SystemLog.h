//
// Created by robin on 30.08.18.
//

#ifndef LOGGERY_SYSTEMLOG_H
#define LOGGERY_SYSTEMLOG_H

#include <string>
#include <chrono>
#include "fmt/format.h"
#include "fmt/time.h"
#include "../classes/Color.hpp"
#include "../gui/Text.h"
#include "../gui/Textbox.h"


namespace ly
{
    class SystemLog
    {
        public:
            static SystemLog *get() {
                static SystemLog log;
                return &log;
            }

            bool process();

            void add(const std::string &text, const ImVec4 &color = {255, 255, 255, 255});
            void addSuccess(const std::string &text, bool useTimestamp = true);
            void addInfo(const std::string &text, bool useTimestamp = true);
            void addWarning(const std::string &text, bool useTimestamp = true);
            void addError(const std::string &text, bool useTimestamp = true);

            void clear();

            const std::string ID = "System log###666";

            const ImVec4 SuccessColor {0, 182, 0, 255};
            const ImVec4 InfoColor {146, 182, 254, 255};
            const ImVec4 WarningColor {255, 219, 0, 255};
            const ImVec4 ErrorColor {240, 0, 0, 255};

        protected:
            std::string getTimestamp(bool includeDate = false);
            std::vector<ly::Text> getFilteredTexts(const std::string_view &filter);

            //std::string m_id;
            ImVec2 m_sizeOnFirstUse;
            bool m_isVisible = true;
            Textbox m_filter = {"filter"};

            std::vector<ly::Text> m_filteredTexts;
            std::vector<ly::Text> m_texts;

        private:
            explicit SystemLog(const ImVec2 &sizeOnFirstUse = {640, 480});
    };
}

#endif //LOGGERY_SYSTEMLOG_H
