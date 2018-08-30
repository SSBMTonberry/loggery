//
// Created by robin on 30.08.18.
//

#ifndef LOGGERY_LOGMANAGER_H
#define LOGGERY_LOGMANAGER_H

#include "../forms/LogForm.h"
namespace ly
{
    class LogManager
    {
        public:
            LogManager() = default;

        private:
            std::vector<ly::LogForm> m_logs;
    };
}

#endif //LOGGERY_LOGMANAGER_H
