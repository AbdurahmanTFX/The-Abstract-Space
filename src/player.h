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
        playerdir dir = playerdir::NONE;
        playerdir RectSideCollision = playerdir::NONE;
        Rectangle playerHitBox;
        bool collisionDetected = false;
        int speed = 300;
    public:
        player(const Rectangle &rec);
        void setSpeed(const int &speed);
        Rectangle GetRec();
        void update(std::vector <std::pair <EnvItem, EnvItem>> obstacles, float delta);
};