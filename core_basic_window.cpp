#include "raylib.h"
#include "src/player.h"
#include "src/EnvItem.h"
#include <vector>
#include <iostream>
#include <string>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif





int main()
{
    InitWindow(0, 0, "raylib [core] example - basic window");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    int monitor = GetCurrentMonitor();
    int screenWidth = GetMonitorWidth(monitor);
    int screenHeight = GetMonitorHeight(monitor);
    SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
    ToggleFullscreen();

    Rectangle plrRec = {float(screenWidth / 2), float(screenHeight / 2), 25, 25};
    player plr(plrRec);

    std::vector <std::pair <EnvItem, int>> obstacles;
    std::pair <EnvItem, int> temp;// {true, RED, {10, 10, 10, 50}};
    temp.first.rect = {500, 250, 10, 50};
    temp.first.blocking = true;
    temp.first.color = BLUE;
    temp.second = 1;

    std::pair <EnvItem, int> temp2;
    temp2.first.rect = {700, 250, 10, 50};
    temp2.first.blocking = true;
    temp2.first.color = GREEN;
    temp2.second = 1;

    std::pair <EnvItem, int> temp3;
    temp3.first.rect = {800, 250, 50, 10};
    temp3.first.blocking = true;
    temp3.first.color = BROWN;
    temp3.second = 1;

    obstacles.push_back(temp);
    obstacles.push_back(temp2);
    obstacles.push_back(temp3);
    float deltaTime = GetFrameTime();
    char c = static_cast<char>(100);
#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else

    SetTargetFPS(200);

    while (!WindowShouldClose())
    {
        deltaTime = GetFrameTime();
        plr.update(obstacles, deltaTime);

        BeginDrawing();

            ClearBackground(RAYWHITE);
            for(int i = 0; i < static_cast<int>(obstacles.size()); i++){
                DrawRectangleRec(obstacles[i].first.rect, obstacles[i].first.color);
            }
            DrawText(&c, screenWidth / 2, screenHeight / 2, 20, LIGHTGRAY);
            DrawRectangleRec(plr.GetRec(), RED);

        EndDrawing();
    }

#endif

    CloseWindow();

    return 0;
}
