#pragma once
#include <utility>
#include <vector>
#include "raylib.h"

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

class EnvItem{
    public:
        float speed;
        Color color = RED;
        Rectangle rect;
        dir Dir = dir::NONE;
        bool blocking = 1;
        void AllSet(const Rectangle& rect, const bool& blocking, const Color& color, const float& speed);
        void update(Vector2 finishPos, float delta, Rectangle plr);
        dir GetDir();
};