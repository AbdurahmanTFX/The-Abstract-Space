#include "raylib.h"
#include "src/player.h"
#include "src/EnvItem.h"
#include "src/Levels.h"
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

    std::vector <std::pair <EnvItem, Vector2>> obstacles;
    TestLevel(obstacles);

    float deltaTime = GetFrameTime();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else

    SetTargetFPS(1000);

    while (!WindowShouldClose())
    {
        deltaTime = GetFrameTime();
        
        for(int i = 0; i < static_cast<int>(obstacles.size()); i++){
            obstacles[i].first.update(obstacles[i].second, deltaTime);
        }

        plr.update(obstacles, deltaTime, dashProgressBar.width);

        if(IsKeyPressed('Q')){
            obstacles.clear();
            TestLevel(obstacles);
        }
        BeginDrawing();

            ClearBackground(RAYWHITE);
            for(int i = 0; i < static_cast<int>(obstacles.size()); i++){
                DrawRectangleRec(obstacles[i].first.rect, obstacles[i].first.color);
            }
            DrawRectangleRec(plr.GetDashBarRec(), plr.GetDashColor());
            DrawRectangleLinesEx(dashProgressBar, 2, GRAY);
            DrawRectangleRec(plr.GetRec(), GREEN);

        EndDrawing();
    }

#endif

    CloseWindow();

    return 0;
}
