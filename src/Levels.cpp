#include "Levels.h"


void TestLevel(std::vector <std::pair <EnvItem, Vector2>> &obstacles){
    std::pair <EnvItem, Vector2> test;
    std::pair <EnvItem, Vector2> test1;
    std::pair <EnvItem, Vector2> test2;
    std::pair <EnvItem, Vector2> test3;

    // std::pair <EnvItem, Vector2> test0;
    // std::pair <EnvItem, Vector2> test11;
    // std::pair <EnvItem, Vector2> test22;
    // std::pair <EnvItem, Vector2> test33;

    test.first.AllSet(Rectangle{0, 0, 100, 50}, true, RED, 800);
    test.second = {1000, 800};

    test1.first.AllSet(Rectangle{1200, 0, 100, 50}, true, RED, 500);
    test1.second = {0, 800};

    test2.first.AllSet(Rectangle{0, 800, 100, 50}, true, RED, 600);
    test2.second = {1000, 0};

    test3.first.AllSet(Rectangle{1200, 800, 100, 50}, true, RED, 900);
    test3.second = {0, 0};

    // test.first.AllSet(Rectangle{0, 0, 100, 50}, true, RED, 360);
    // test.second = {1000, 800};

    // test.first.AllSet(Rectangle{0, 0, 100, 50}, true, RED, 360);
    // test.second = {1000, 800};

    obstacles.push_back(test);
    obstacles.push_back(test1);
    obstacles.push_back(test2);
    obstacles.push_back(test3);
}