//
// Created by robin on 30.08.18.
//

#ifndef LOGGERY_LOGFORM_H
#define LOGGERY_LOGFORM_H

#include <string>
#include <string_view>
#include <algorithm>
#include <fstream>
#include "../gui/Textbox.h"
#include "../gui/Text.h"
#include "../classes/Timer.h"
#include "fmt/format.h"
#include "fmt/time.h"
#include "SystemLog.h"

#if MSVC
    #include <filesystem>
    namespace fs = std::filesystem;
#elif MINGW
    #if __MINGW64_VERSION_MAJOR > 5
        #include <filesystem>
        namespace fs = std::filesystem;
    #else
        #include <experimental/filesystem>
        namespace fs = std::experimental::filesystem;
    #endif
#elif APPLE
    #include <experimental/filesystem>
    namespace fs = std::experimental::filesystem;
#else
    #if __GNUC__ < 8 //GCC major version less than 8
        #include <experimental/filesystem>
        namespace fs = std::experimental::filesystem;
    #else
        #include <filesystem>
        namespace fs = std::filesystem;
    #endif
#endif

namespace ly
{
    class LogForm
    {
        public:
            LogForm();
            LogForm(const fs::path &path, const ImVec2 &sizeOnFirstUse = {640, 480});

            bool process();
            bool loadFile(const fs::path &path);
            std::vector<ly::Text> getFilteredTexts(const std::string_view &filter);
            std::string generateId(const fs::path &path);

            void setVisible(bool isVisisble);
            void setSizeOnFirstUse(const ImVec2 &sizeOnFirstUse);

            bool isVisible() const;
            const ImVec2 &getSizeOnFirstUse() const;

        private:
            void showProperties();
            void processProperties();

            fs::path m_path;
            fs::file_time_type m_lastUpdate;
            std::string m_id;
            ImVec2 m_sizeOnFirstUse;
            bool m_isVisible = true;
            Textbox m_filter = {"filter"};
            std::vector<ly::Text> m_filteredTexts;
            std::vector<ly::Text> m_texts;

            /*!
             * first: If you want to limit the lines or not
             * second: How many lines you want to show at a time if limit is on
             */
            std::pair<bool, int> m_limitLines {false, 1000};

            bool m_alwaysSetScrollMax = true;
            bool m_autoUpdate = true;
    };
}

#endif //LOGGERY_LOGFORM_H
