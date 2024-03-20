#pragma once
#include "raylib.h"
#include "EnvItem.h"
#include <iostream>
#include <vector>

enum playerdir{
            RIGHT,
            LEFT,
            TOP,
            BOTTOM,
            TOP_RIGHT,
            TOP_LEFT,
            BOTTOM_RIGHT,
            BOTTOM_LEFT,
            NONE
        };

class player{
    private:

        Rectangle playerHitBox;
        int OriginalSpeed = 300;
        int speed = 300;


        Rectangle dashProgressBar;
        bool dash = false;
        playerdir dashDir = playerdir::NONE;
        float dashCurrentTimer;
        float dashDurationTimer;
        float dashCurrentBarTimer;
        float dashDurationBarTimer;
        Color dashColor = GREEN;

    public:

        player(const Rectangle &playerRec, const Rectangle &dashBar);
        void SetSpeed(const int &speed);
        void SetDashColor(const Color &clr);
        Rectangle GetPlayerRec();
        Rectangle GetDashBarRec();
        Color GetDashColor();
        void update(std::vector <std::pair <EnvItem, EnvItem>> obstacles, float delta, const float &dashbar);

};