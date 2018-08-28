//
// Created by robin on 28.08.18.
//

#include "Timer.h"

ly::Timer::Timer()
{
    reset(true);
}

/*!
 * Updates the timer and returns true if the time elapsed is equivalent to the fps specified.
 *
 * @param fps Frames Per Second.
 * -1: Makes the function always return true. Also returns the same if below -1.
 *  0: Makes the function always return false.
 * 1+: Makes the function return true when the time passed is equivalent to the number of FPS specified.
 *
 * @return Whether or not an update should occur in the program using the timer
 */
bool ly::Timer::update(double fps)
{
    m_endTime = high_resolution_clock::now();

    if(fps < 0) return true;
    else if(fps == 0) return false;
    else
    {
        double fpsAsTime = 1 / fps;
        duration<double> duration = getDuration();
        if(duration.count() > fpsAsTime)
        {
            reset();
            return true;
        }
    }

    return false;
}

void ly::Timer::reset(bool resetTotalStartTime)
{
    m_startTime = high_resolution_clock::now();
    m_endTime = high_resolution_clock::now();
    if(resetTotalStartTime)
        m_startTotalTime = high_resolution_clock::now();
}

/*
 * Gets the duration
 */
duration<double> ly::Timer::getDuration()
{
    m_lastDuration = duration_cast<duration<double>>(m_endTime-m_startTime);
    return m_lastDuration;
}

/*!
 * Gets the duration stored under last update() call
 * @return
 */
const duration<double> &ly::Timer::getLastDuration() const
{
    return m_lastDuration;
}

/*!
 * Gets the duration since the very start or since last reset()
 * @return
 */
duration<double> ly::Timer::getTotalDuration()
{
    auto now = high_resolution_clock::now();
    return duration_cast<duration<double>>(now-m_startTotalTime);
}
