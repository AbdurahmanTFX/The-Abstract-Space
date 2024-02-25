#include "timer.hpp"

void Timer::initTimer(float lifetime)
{
    if (lifetime != NULL)
        Timer::Lifetime = lifetime;
}

// update a timer with the current frame time
void Timer::UpdateTimer()
{
    // subtract this frame from the timer if it's not allready expired
    if (Timer::Lifetime != NULL && Timer::Lifetime > 0)
        Timer::Lifetime -= GetFrameTime();
}

// check if a timer is done.
bool Timer::TimerDone()
{
    if (Timer::Lifetime != NULL)
        return Timer::Lifetime <= 0;

	return false;
}