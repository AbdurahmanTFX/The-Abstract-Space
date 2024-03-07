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
            right, left, up, down
        }dir = playerdir::up;
        player(const Rectangle &rec);
        void setSpeed(const int &speed);
        void update(const std::vector <Rectangle> &obstacles);
        Rectangle GetRec();
        void updateTwo(std::vector <std::pair <EnvItem, int>> obstacles, float delta);
};