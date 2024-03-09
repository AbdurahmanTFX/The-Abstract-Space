#pragma once
#include "raylib.h"
#include "EnvItem.h"
#include <vector>

class player{
    private:
        bool rightSide = true, leftSide = true, upSide = true, downSide = true; 
        Rectangle playerHitBox;
        int speed = 200;
    public:
        enum playerdir{
            right, left, up, down, none
        }dir = playerdir::up;
        player(const Rectangle &rec);
        void setSpeed(const int &speed);
        Rectangle GetRec();
        void update(std::vector <std::pair <EnvItem, int>> obstacles, float delta);
};