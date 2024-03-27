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
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    Rectangle plrRec{
        float(screenWidth / 2), float(screenHeight / 2), 25, 25
    };
    Rectangle dashProgressBar{
        plrRec.x - 50, plrRec.y - 50, 100, 25
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
            obstacles[i].first.update(obstacles[i].second, deltaTime, plr.GetRec());
        }

        

        plr.update(obstacles, deltaTime, dashProgressBar.width);

        dashProgressBar.x = plr.GetRec().x - 50;
        dashProgressBar.y = plr.GetRec().y - 50;
        plr.SetDashPos(dashProgressBar);

        if(IsKeyPressed('Q')){
            obstacles.clear();
            TestLevel(obstacles);
        }

        if (IsKeyPressed(KEY_F5))
		{
			if (IsWindowFullscreen())
			{
				ToggleFullscreen();
				SetWindowSize(screenWidth, screenHeight);
			}
			else
			{
				int monitor = GetCurrentMonitor();
				SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
				ToggleFullscreen();
			}
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
