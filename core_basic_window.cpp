#include "raylib.h"
#include <stdlib.h>
#include <vector>
#include "src/obstacles.hpp"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

enum pdir{
    right, left, up, down
}dir;

bool RecEx(){
    
}
//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------

    // const int screenWidth = 1024;
    // const int screenHeight = 600;

    const int screenWidth = 3840;
    const int screenHeight = 2160;

    InitWindow(screenWidth, screenHeight, "raylib");
    //ToggleFullscreen();
    RenderTexture2D renderTexture = LoadRenderTexture(screenWidth, screenHeight);

    Vector2 playerPos = {screenWidth / 2, screenHeight / 2};
    int playerSpeedX = screenHeight/100*0.75;
    //int playerSpeedY = playerSpeedX / 2;
    double RCircle = 60;
    int jumpHeight;
    bool jump = false;
    bool BoolOfJump = true;

    dir = up;

    Rectangle rightWall, leftWall, upWall, downWall;
    Rectangle defaultRightWall, defaultLeftWall, defaultUpWall, defaultDownWall;
    float innerRadius = 120.0f;
    float outerRadius = 150.0f;
    bool temp = true;
    float startAngle = 270.0f;
    float endAngle = 630.0f;
    float segments = 0.0f;

    std::vector<Rectangle> obstacles;
    std::vector<Rectangle> BufferObstacles;
    

    defaultLeftWall = {screenWidth / 2 - screenWidth / 100 * 31.25, screenHeight / 2 - screenHeight / 100 * 66.6666667 / 2, 25, screenHeight / 100 * 66.6666667};
    defaultRightWall = {screenWidth / 2 + screenWidth / 100 * 31.25, screenHeight / 2 - screenHeight / 100 * 66.6666667 / 2, 25, screenHeight / 100 * 66.6666667};
    defaultUpWall = {defaultLeftWall.x, defaultLeftWall.y, defaultRightWall.x - defaultLeftWall.x, defaultLeftWall.width};
    defaultDownWall = {defaultLeftWall.x, defaultLeftWall.y + defaultLeftWall.height - defaultLeftWall.width, defaultRightWall.x - defaultLeftWall.x, defaultLeftWall.width};
    
    rightWall = defaultRightWall;
    leftWall = defaultLeftWall;
    upWall = defaultUpWall;
    downWall = defaultDownWall;

    bool smplwlls = true;
    bool vrtclywlls = false;

    // int display = GetCurrentMonitor();
    //         if (!IsWindowFullscreen())
    //             {
    //                 // if we are full screen, then go back to the windowed size
    //                 SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
    //             }
    //         ToggleFullscreen();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop

    //--------------------------------------------------------------------------------------
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //----------------------------------------------------------------------------------
        
        // Update

        //----------------------------------------------------------------------------------

        
        simpleWalls(screenWidth, screenHeight, BufferObstacles);
        // if(smplwlls == true && BufferObstacles != obstacles)
        //     simpleWalls(screenWidth, screenHeight, BufferObstacles);
        // else{
        //     smplwlls = false;
        //     vrtclywlls = true;
        //     verticallyWalls(screenWidth, screenHeight, BufferObstacles);
        // }
        // if(vrtclywlls == true && BufferObstacles != obstacles)
        //     simpleWalls(screenWidth, screenHeight, BufferObstacles);

        obstacles.resize(BufferObstacles.size());

        for(int i = 0; i < static_cast<int>(BufferObstacles.size()); i++){
                if(obstacles[i].x == NULL){
                    obstacles.push_back(BufferObstacles[i]);
                }
                else{
                    if(obstacles[i].height > BufferObstacles[i].height)
                    obstacles[i].height -= 25;
                    if(obstacles[i].height < BufferObstacles[i].height)
                        obstacles[i].height += 25;
                    if(obstacles[i].width > BufferObstacles[i].width)
                        obstacles[i].width -= 25;
                    if(obstacles[i].width < BufferObstacles[i].width)
                        obstacles[i].width += 25;
                    if(obstacles[i].x > BufferObstacles[i].x)
                        obstacles[i].x -= 25;
                    if(obstacles[i].x < BufferObstacles[i].x)
                        obstacles[i].x += 25;
                    if(obstacles[i].y > BufferObstacles[i].y)
                        obstacles[i].y -= 25;
                    if(obstacles[i].y < BufferObstacles[i].y)
                        obstacles[i].y += 25;
                }
                
        }

        switch(GetKeyPressed()){
             case 'W':
             dir = up;
             break;

            case 'S':
            dir = down;
            break;

            case 'A':
            dir = left;
            break;

            case 'D':
            dir = right;
            break;
        }

        if ((IsKeyDown('W') || IsKeyPressed('W')) && (IsKeyDown('S') || IsKeyPressed('S')) 
        && !CheckCollisionCircleRec(playerPos, RCircle, upWall)){
            if(dir == up) playerPos.y -= playerSpeedX;
            else if(dir == down) playerPos.y += playerSpeedX;
        }
        else if ((IsKeyDown('S') || IsKeyPressed('S')) && (!IsKeyDown('w') || !IsKeyPressed('W'))
         && !CheckCollisionCircleRec(playerPos, RCircle, downWall)) 
            playerPos.y += playerSpeedX;
        else if((IsKeyDown('W') || IsKeyPressed('W')) && (!IsKeyDown('S') || !IsKeyPressed('S'))
         && !CheckCollisionCircleRec(playerPos, RCircle, upWall))
            playerPos.y -= playerSpeedX;

        if((IsKeyDown('D') || IsKeyPressed('D')) && (IsKeyDown('A') || IsKeyPressed('A'))){
            if(dir == right)playerPos.x += playerSpeedX;
            else if(dir == left)playerPos.x -= playerSpeedX;
        }
        else if ((IsKeyDown('A') || IsKeyPressed('A')) && (!IsKeyDown('D') || !IsKeyPressed('D')) 
         && !CheckCollisionCircleRec(playerPos, RCircle, leftWall))
            playerPos.x -= playerSpeedX;
        else if ((IsKeyDown('D') || IsKeyPressed('D')) && (!IsKeyDown('A') || !IsKeyPressed('A')) 
         && !CheckCollisionCircleRec(playerPos, RCircle, rightWall))
            playerPos.x += playerSpeedX;
        
        if(IsKeyPressed(KEY_SPACE) && BoolOfJump){
            BoolOfJump = false;
            switch(dir){
                case right:
                    jumpHeight = playerPos.x + (screenWidth / 100 * 6.25);
                break;

                case left:
                    jumpHeight = playerPos.x - (screenWidth / 100 * 6.25);
                break;

                case up:
                    jumpHeight = playerPos.y - (screenWidth / 100 * 6.25);
                break;

                case down:
                    jumpHeight = playerPos.y + (screenWidth / 100 * 6.25);
                break;
            }
            jump = true;
        }

        if(jump){
            
            switch(dir){
                case right:
                    if((playerPos.x < jumpHeight) && !CheckCollisionCircleRec(playerPos, RCircle, rightWall)){
                        playerPos.x += playerSpeedX + playerSpeedX / 0.128571429;
                    }
                    else{
                        jump = false;
                    }
                break;

                case left:
                    if((playerPos.x > jumpHeight) && !CheckCollisionCircleRec(playerPos, RCircle, leftWall)){
                        playerPos.x -= playerSpeedX + playerSpeedX / 0.128571429;
                    }
                    else{
                        jump = false;
                    }
                break;

                case up:
                    if((playerPos.y > jumpHeight) && !CheckCollisionCircleRec(playerPos, RCircle, upWall)){
                        playerPos.y -= playerSpeedX + playerSpeedX / 0.128571429;
                    }
                    else{
                        jump = false;
                    }
                break;

                case down:
                    if((playerPos.y < jumpHeight) && !CheckCollisionCircleRec(playerPos, RCircle, downWall)){
                        playerPos.y += playerSpeedX + playerSpeedX / 0.128571429;
                    }
                    else{
                        jump = false;
                    }
                break;
            }
        }

        if(!BoolOfJump){
            
            //timeOfjump.UpdateTimer();
            if(endAngle != 270.0f && endAngle > 270.0f && temp)
                endAngle -= 15;
            else if(endAngle != 630.0f && endAngle < 630.0f){
                temp = false;
                endAngle += 3;
            }
            else
                temp = true;
  
            if(/*timeOfjump.TimerDone() && */temp && endAngle == 630.0f){
                BoolOfJump = true;
                //timeOfjump.initTimer(2.0f);
            }
        }

        if(IsKeyPressed(KEY_F11)){
            int display = GetCurrentMonitor();
            if (!IsWindowFullscreen())
                {
                    // if we are full screen, then go back to the windowed size
                    SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
                }
            ToggleFullscreen();
 		    }

        if(CheckCollisionCircleRec(playerPos, RCircle, leftWall))
            playerPos.x = leftWall.x + leftWall.width + RCircle;
        if(CheckCollisionCircleRec(playerPos, RCircle, rightWall))
            playerPos.x = rightWall.x - RCircle;
        if(CheckCollisionCircleRec(playerPos, RCircle, downWall))
            playerPos.y = downWall.y - RCircle;
        if(CheckCollisionCircleRec(playerPos, RCircle, upWall))
            playerPos.y = upWall.y + upWall.height + RCircle;

        //----------------------------------------------------------------------------------

        // Draw

        //----------------------------------------------------------------------------------

        BeginTextureMode(renderTexture);
            ClearBackground(BLACK);

            for(int i = 0; i < static_cast<int>(obstacles.size()); i++){
                DrawRectangleRec(obstacles[i], WHITE);
            }
        
            // DrawRectangleRec(rightWall, WHITE);
            // DrawRectangleRec(leftWall, WHITE);
            // DrawRectangleRec(upWall, WHITE);
            // DrawRectangleRec(downWall, WHITE);
            DrawCircle(playerPos.x, playerPos.y, RCircle, WHITE);
            DrawRing(Vector2{screenWidth - 300, screenHeight - 300}, innerRadius, outerRadius, startAngle, endAngle, (int)segments, Fade(MAROON, 0.3f));
            DrawRing(playerPos, RCircle, RCircle + 30, startAngle, endAngle, (int)segments, Fade(MAROON, 0.3f));
            DrawText("SPACE", screenWidth - 402, screenHeight - 324, 60, DARKGRAY);
            

            DrawFPS(10, 10);
        EndTextureMode();

        BeginDrawing();

            DrawTexturePro(
            renderTexture.texture,
            Rectangle{ 0, 0, static_cast<float>(renderTexture.texture.width), static_cast<float>(-renderTexture.texture.height) },
            Rectangle{ 0, 0, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) },
            Vector2{ 0, 0 },0,WHITE);
            
        EndDrawing();
        //----------------------------------------------------------------------------------
        BufferObstacles.clear();
    }

    
    UnloadRenderTexture(renderTexture);

#endif
    

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
