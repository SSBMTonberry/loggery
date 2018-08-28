//
// Created by robin on 28.08.18.
//

#ifndef LOGGERY_FPSTIMER_H
#define LOGGERY_FPSTIMER_H

#include <ctime>
#include <ratio>
#include <chrono>

using namespace std::chrono;
namespace ly
{
    class Timer
    {
        public:
            Timer();

            bool update(double fps = 60);
            void reset(bool resetTotalStartTime = false);

            duration<double> getDuration();
            const duration<double> &getLastDuration() const;
            duration<double> getTotalDuration();

        protected:
            high_resolution_clock::time_point m_startTime;
            high_resolution_clock::time_point m_endTime;
            high_resolution_clock::time_point m_startTotalTime;
            duration<double> m_lastDuration;
    };
}

#endif //LOGGERY_FPSTIMER_H
