#pragma once
#include "raylib.h"
#include "iostream"
#include "vector"

enum dir{
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

// struct EnvItem{
//     Rectangle rect;
    
//     Color color = RED;
//     bool number;
//     float updateSpeed = 300;
//     dir move = dir::NONE;
// };

// void UpdateObstacles(std::vector <std::pair <EnvItem, Vector2>> &obstacles,
//  const float &speed, const float &delta, const float &screenWidth, const float &screenHeight, Rectangle &plr/*float time*/);

class EnvItem{
    public:
        float speed;
        Color color = RED;
        Rectangle rect;
        dir Dir = dir::NONE;
        bool blocking = 1;
        void AllSet(const Rectangle& rect, const bool& blocking, const Color& color, const float& speed);
        void update(Vector2 finishPos, float delta);
        dir GetDir();
};