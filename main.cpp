#include "raylib.h"
#include "src/player.h"
#include "src/EnvItem.h"
#include <vector>
#include <iostream>

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

    Rectangle plrRec{
        float(screenWidth / 2), float(screenHeight / 2), 25, 25
    };
    Rectangle dashProgressBar{
        float((screenWidth / 2) - 500), float(screenHeight - (screenHeight / 5)), 1000, 25
    };

    player plr(plrRec, dashProgressBar);

    std::vector <std::pair <EnvItem, EnvItem>> obstacles;
    std::pair <EnvItem, EnvItem> temp;
    temp.first = {{500, 250, 10, 50},  false, BLUE, 0};

    std::pair <EnvItem, EnvItem> temp2;
    temp2.first = {{700, 250, 10, 50}, true, RED, 1};

    std::pair <EnvItem, EnvItem> temp3;
    temp3.first = {{800, 250, 50, 10}, true, RED, 1};

    std::pair <EnvItem, EnvItem> temp4;
    temp4.first = {{800, 400, 50, 10}, true, RED, 1};

    obstacles.push_back(temp);
    obstacles.push_back(temp2);
    obstacles.push_back(temp3);
    obstacles.push_back(temp4);
    
    float deltaTime = GetFrameTime();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else

    SetTargetFPS(360);

    while (!WindowShouldClose())
    {
        deltaTime = GetFrameTime();
        plr.update(obstacles, deltaTime, dashProgressBar.width);

        BeginDrawing();

            ClearBackground(RAYWHITE);
            for(int i = 0; i < static_cast<int>(obstacles.size()); i++){
                DrawRectangleRec(obstacles[i].first.rect, obstacles[i].first.color);
            }
            DrawRectangleRec(plr.GetDashBarRec(), plr.GetDashColor());
            DrawRectangleRec(plr.GetPlayerRec(), GREEN);

        EndDrawing();
    }

#endif

    CloseWindow();

    return 0;
}
