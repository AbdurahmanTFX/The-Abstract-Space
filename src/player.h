#pragma once
#include <utility>
#include <vector>
#include "raylib.h"
#include "EnvItem.h"

class player{
    private:
        int OriginalSpeed = 300;
        Rectangle dashProgressBar;
        bool dash = false;
        dir dashDir = dir::NONE;
        float dashCurrentTimer;
        float dashDurationTimer;
        float dashCurrentBarTimer;
        float dashDurationBarTimer;
        Color dashColor = GREEN;

        int speed = OriginalSpeed;
        Rectangle rect;

    public:
        player(const Rectangle &playerRec, const Rectangle &dashBar);
        void SetSpeed(const int &speed);
        void SetDashColor(const Color &clr);
        Rectangle GetRec();
        Rectangle GetDashBarRec();
        Color GetDashColor();
        void update(std::vector <std::pair<EnvItem, Vector2>> obstacles, float delta, const float &dashBarWidth);
        void SetDashPos(const Rectangle &dashBar);

};