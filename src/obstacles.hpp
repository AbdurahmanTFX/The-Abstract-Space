#pragma once
#include <vector>
#include "raylib.h"

void simpleWalls(int screenWidth, int screenHeight, std::vector<Rectangle> &obstacles){
    Rectangle defaultRightWall, defaultLeftWall, defaultUpWall, defaultDownWall;

    obstacles.push_back(defaultLeftWall = {float(screenWidth / 2 - screenWidth / 100 * 31.25),
     float(screenHeight / 2 - screenHeight / 100 * 66.6666667 / 2), 25, float(screenHeight / 100 * 66.6666667)});
    obstacles.push_back(defaultRightWall = {float(screenWidth / 2 + screenWidth / 100 * 31.25),
     float(screenHeight / 2 - screenHeight / 100 * 66.6666667 / 2), 25, float(screenHeight / 100 * 66.6666667)});
    obstacles.push_back(defaultUpWall = {defaultLeftWall.x, defaultLeftWall.y, defaultRightWall.x - defaultLeftWall.x,
     defaultLeftWall.width});
    obstacles.push_back(defaultDownWall = {defaultLeftWall.x, defaultLeftWall.y + defaultLeftWall.height - defaultLeftWall.width,
     defaultRightWall.x - defaultLeftWall.x, defaultLeftWall.width});
} 

void verticallyWalls(int screenWidth, int screenHeight, std::vector<Rectangle> &obstacles){
    Rectangle defaultRightWall, defaultLeftWall, defaultUpWall, defaultDownWall;

    obstacles.push_back(defaultLeftWall = {float(screenWidth / 2 - screenWidth / 100 * 62.50),
     float(screenHeight / 2 - screenHeight / 100 * 66.6666667 / 2), 25, float(screenHeight / 100 * 66.6666667)});
    obstacles.push_back(defaultRightWall = {float(screenWidth / 2 + screenWidth / 100 * 62.50),
     float(screenHeight / 2 - screenHeight / 100 * 66.6666667 / 2), 25, float(screenHeight / 100 * 66.6666667)});
    obstacles.push_back(defaultUpWall = {defaultLeftWall.x, defaultLeftWall.y, defaultRightWall.x - defaultLeftWall.x,
     defaultLeftWall.width});
    obstacles.push_back(defaultDownWall = {defaultLeftWall.x, defaultLeftWall.y + defaultLeftWall.height - defaultLeftWall.width,
     defaultRightWall.x - defaultLeftWall.x, defaultLeftWall.width});
} 
