#include "Levels.h"


void TestLevel(std::vector <std::pair <EnvItem, Vector2>> &obstacles){
    std::pair <EnvItem, Vector2> rightWall;
    std::pair <EnvItem, Vector2> leftWall;
    std::pair <EnvItem, Vector2> upWall;
    std::pair <EnvItem, Vector2> downWall;

    rightWall.first.AllSet(Rectangle{0, 0, 100, 50}, true, RED, 600);
    rightWall.second = {1000, 800};

    leftWall.first.AllSet(Rectangle{1200, 0, 100, 50}, true, RED, 600);
    leftWall.second = {0, 800};

    upWall.first.AllSet(Rectangle{1000, 200, 100, 50}, true, RED, 600);
    upWall.second = {1000, 200};

    downWall.first.AllSet(Rectangle{1200, 800, 100, 50}, true, RED, 600);
    downWall.second = {0, 0};

    obstacles.push_back(rightWall);
    obstacles.push_back(leftWall);
    obstacles.push_back(upWall);
    obstacles.push_back(downWall);
}