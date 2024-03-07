#pragma once
#include "raylib.h"

typedef struct EnvItem{
    Rectangle rect;
    bool blocking;
    Color color;
};