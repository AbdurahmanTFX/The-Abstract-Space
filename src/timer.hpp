#pragma once
#include "raylib.h"
#include <stdlib.h>

struct Timer{
    public:
        float Lifetime;

        void initTimer(float lifetime);

        // update a timer with the current frame time
        void UpdateTimer();

        // check if a timer is done.
        bool TimerDone();
};