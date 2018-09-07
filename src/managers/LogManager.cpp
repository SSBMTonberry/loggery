//
// Created by robin on 30.08.18.
//

#include "LogManager.h"

void ly::LogManager::add(const fs::path &path)
{
    m_logs.emplace_back(path);
    //m_logs[m_logs.size()-1].loadFile(path);
}

void ly::LogManager::process()
{
    for(auto &log : m_logs)
    {
        log.process();
    }
}
