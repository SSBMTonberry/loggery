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
#include "fmt/format.h"
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
            LogForm(const std::string &id, const ImVec2 &sizeOnFirstUse = {640, 480});

            bool process();
            bool loadFile(const fs::path &path);
            std::vector<ly::Text> getFilteredTexts(const std::string_view &filter);

            void setVisible(bool isVisisble);
            void setSizeOnFirstUse(const ImVec2 &sizeOnFirstUse);

            bool isVisible() const;
            const ImVec2 &getSizeOnFirstUse() const;

        private:
            std::string m_id;
            ImVec2 m_sizeOnFirstUse;
            bool m_isVisible = true;
            Textbox m_filter = {"filter"};
            std::vector<ly::Text> m_filteredTexts;
            std::vector<ly::Text> m_texts;

            SystemLog *m_log;
    };
}

#endif //LOGGERY_LOGFORM_H
