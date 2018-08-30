//
// Created by robin on 30.08.18.
//

#ifndef LOGGERY_SYSTEMLOG_H
#define LOGGERY_SYSTEMLOG_H

#include <string>
#include "../classes/Color.hpp"
namespace ly
{
    class SystemLog
    {
        public:
            SystemLog() = default;

            void add(const std::string &text, const ly::Color &color = {255, 255, 255, 255});
            void addSuccess(const std::string &text, bool useTimestamp = true);
            void addInfo(const std::string &text, bool useTimestamp = true);
            void addWarning(const std::string &text, bool useTimestamp = true);
            void addError(const std::string &text, bool useTimestamp = true);
            void addTestTexts();

            void clear();

            const std::string ID = "System log###666";

            const ly::Color SuccessColor{0, 182, 0, 255};
            const ly::Color InfoColor{146, 182, 255, 255};
            const ly::Color WarningColor{255, 219, 0, 255};
            const ly::Color ErrorColor{240, 0, 0, 255};
    };
}

#endif //LOGGERY_SYSTEMLOG_H
