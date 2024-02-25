// #pragma once
// #include "raylib.h"



// class player{
//     public:
//         enum pdir{
//         right, left, up, down
//         };

//         void moveUpdate(int playerSpeedX, Vector2 playerPos){
//             if ((IsKeyDown('W') || IsKeyPressed('W')) && (IsKeyDown('S') || IsKeyPressed('S')) 
//             && !CheckCollisionCircleRec(playerPos, RCircle, upWall)){
//                 if(dir == up) playerPos.y -= playerSpeedX;
//                     else if(dir == down) playerPos.y += playerSpeedX;
//             }
//             else if ((IsKeyDown('S') || IsKeyPressed('S')) && (!IsKeyDown('w') || !IsKeyPressed('W'))
//             && !CheckCollisionCircleRec(playerPos, RCircle, downWall)) 
//                 playerPos.y += playerSpeedX;
//             else if((IsKeyDown('W') || IsKeyPressed('W')) && (!IsKeyDown('S') || !IsKeyPressed('S'))
//             && !CheckCollisionCircleRec(playerPos, RCircle, upWall))
//                 playerPos.y -= playerSpeedX;

//             if((IsKeyDown('D') || IsKeyPressed('D')) && (IsKeyDown('A') || IsKeyPressed('A'))){
//                 if(dir == right)playerPos.x += playerSpeedX;
//                     else if(dir == left)playerPos.x -= playerSpeedX;
//             }
//             else if ((IsKeyDown('A') || IsKeyPressed('A')) && (!IsKeyDown('D') || !IsKeyPressed('D')) 
//             && !CheckCollisionCircleRec(playerPos, RCircle, leftWall))
//                 playerPos.x -= playerSpeedX;
//             else if ((IsKeyDown('D') || IsKeyPressed('D')) && (!IsKeyDown('A') || !IsKeyPressed('A')) 
//             && !CheckCollisionCircleRec(playerPos, RCircle, rightWall))
//                 playerPos.x += playerSpeedX;
//         }

//         switch(GetKeyPressed()){
//             case 'W':
//             dir = up;
//             break;

//             case 'S':
//             dir = down;
//             break;

//             case 'A':
//             dir = left;
//             break;

//             case 'D':
//             dir = right;
//             break;
//         }

        
        
//         if(IsKeyPressed(KEY_SPACE) && BoolOfJump){
//             BoolOfJump = false;
//             switch(dir){
//                 case right:
//                     jumpHeight = playerPos.x + (screenWidth / 100 * 6.25);
//                 break;

//                 case left:
//                     jumpHeight = playerPos.x - (screenWidth / 100 * 6.25);
//                 break;

//                 case up:
//                     jumpHeight = playerPos.y - (screenWidth / 100 * 6.25);
//                 break;

//                 case down:
//                     jumpHeight = playerPos.y + (screenWidth / 100 * 6.25);
//                 break;
//             }
//             jump = true;
//         }

//         if(jump){
            
//             switch(dir){
//                 case right:
//                     if((playerPos.x < jumpHeight) && !CheckCollisionCircleRec(playerPos, RCircle, rightWall)){
//                         playerPos.x += playerSpeedX + playerSpeedX / 0.128571429;
//                     }
//                     else{
//                         jump = false;
//                     }
//                 break;

//                 case left:
//                     if((playerPos.x > jumpHeight) && !CheckCollisionCircleRec(playerPos, RCircle, leftWall)){
//                         playerPos.x -= playerSpeedX + playerSpeedX / 0.128571429;
//                     }
//                     else{
//                         jump = false;
//                     }
//                 break;

//                 case up:
//                     if((playerPos.y > jumpHeight) && !CheckCollisionCircleRec(playerPos, RCircle, upWall)){
//                         playerPos.y -= playerSpeedX + playerSpeedX / 0.128571429;
//                     }
//                     else{
//                         jump = false;
//                     }
//                 break;

//                 case down:
//                     if((playerPos.y < jumpHeight) && !CheckCollisionCircleRec(playerPos, RCircle, downWall)){
//                         playerPos.y += playerSpeedX + playerSpeedX / 0.128571429;
//                     }
//                     else{
//                         jump = false;
//                     }
//                 break;
//             }
//         }

//         if(!BoolOfJump){
            
//             //timeOfjump.UpdateTimer();
//             if(endAngle != 270.0f && endAngle > 270.0f && temp)
//                 endAngle -= 15;
//             else if(endAngle != 630.0f && endAngle < 630.0f){
//                 temp = false;
//                 endAngle += 3;
//             }
//             else
//                 temp = true;
  
//             if(/*timeOfjump.TimerDone() && */temp && endAngle == 630.0f){
//                 BoolOfJump = true;
//                 //timeOfjump.initTimer(2.0f);
//             }
//         }
// };
