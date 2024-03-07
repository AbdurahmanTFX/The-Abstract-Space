#include "player.h"

player::player(const Rectangle &rec){
    this->playerHitBox.x = rec.x;
    this->playerHitBox.y = rec.y;
    this->playerHitBox = rec;
}

void player::setSpeed(const int &speed){
    this->speed = speed;
}

Rectangle player::GetRec(){
    return this->playerHitBox;
}


void player::updateTwo(std::vector <std::pair <EnvItem, int>> obstacles, float delta)
{
    switch(GetKeyPressed()){
        case 'W':
            this->dir = this->playerdir::up;
            break;

        case 'S':
            this->dir = this->playerdir::down;
            break;

        case 'A':
            this->dir = this->playerdir::left;
            break;

        case 'D':
            this->dir = this->playerdir::right;
            break;
    }

    for(int i = 0; i < static_cast<int>(obstacles.size()); i++){
        if(CheckCollisionRecs(this->playerHitBox, obstacles[i].first.rect) && obstacles[i].second){

            if(this->playerHitBox.y >= obstacles[i].first.rect.y 
            && this->playerHitBox.y <= obstacles[i].first.rect.y + obstacles[i].first.rect.height &&
            (IsKeyDown('S') || IsKeyPressed('S')) 
            && ((IsKeyDown('A') || IsKeyPressed('A')))){
                playerHitBox.x = obstacles[i].first.rect.x + obstacles[i].first.rect.width;
            }
            else if(this->playerHitBox.y + this->playerHitBox.height >= obstacles[i].first.rect.y 
            && this->playerHitBox.y + this->playerHitBox.height <= obstacles[i].first.rect.y + obstacles[i].first.rect.height &&
            (IsKeyDown('W') || IsKeyPressed('W')) 
            && ((IsKeyDown('A') || IsKeyPressed('A')))){
                playerHitBox.x = obstacles[i].first.rect.x + obstacles[i].first.rect.width;
            }

            else if(this->playerHitBox.y >= obstacles[i].first.rect.y 
            && this->playerHitBox.y <= obstacles[i].first.rect.y + obstacles[i].first.rect.height &&
            (IsKeyDown('S') || IsKeyPressed('S')) 
            && ((IsKeyDown('D') || IsKeyPressed('D')))){
                playerHitBox.x = obstacles[i].first.rect.x - playerHitBox.width;
            }
            else if(this->playerHitBox.y + this->playerHitBox.height >= obstacles[i].first.rect.y 
            && this->playerHitBox.y + this->playerHitBox.height <= obstacles[i].first.rect.y + obstacles[i].first.rect.height &&
            (IsKeyDown('W') || IsKeyPressed('W')) 
            && ((IsKeyDown('D') || IsKeyPressed('D')))){
                playerHitBox.x = obstacles[i].first.rect.x - playerHitBox.width;
            }
////////////////////////////////////////////////////////

            

///////////////////////////////////////////////////////

            else if(this->playerHitBox.x >= obstacles[i].first.rect.x 
            && this->playerHitBox.x <= obstacles[i].first.rect.x + obstacles[i].first.rect.width &&
            (IsKeyDown('S') || IsKeyPressed('S')) 
            && ((IsKeyDown('A') || IsKeyPressed('A')))){
                playerHitBox.y = obstacles[i].first.rect.y - playerHitBox.height;
            }
            else if(this->playerHitBox.x + this->playerHitBox.width >= obstacles[i].first.rect.x 
            && this->playerHitBox.x + this->playerHitBox.width <= obstacles[i].first.rect.x + obstacles[i].first.rect.width &&
            (IsKeyDown('W') || IsKeyPressed('W')) 
            && ((IsKeyDown('A') || IsKeyPressed('A')))){
                playerHitBox.y = obstacles[i].first.rect.y + obstacles[i].first.rect.height;
            }

            else if(this->playerHitBox.x >= obstacles[i].first.rect.x 
            && this->playerHitBox.x <= obstacles[i].first.rect.x + obstacles[i].first.rect.width &&
            (IsKeyDown('S') || IsKeyPressed('S')) 
            && ((IsKeyDown('D') || IsKeyPressed('D')))){
                playerHitBox.y = obstacles[i].first.rect.y - playerHitBox.height;
            }
            else if(this->playerHitBox.x + this->playerHitBox.width >= obstacles[i].first.rect.x
            && this->playerHitBox.x + this->playerHitBox.width <= obstacles[i].first.rect.x + obstacles[i].first.rect.width &&
            (IsKeyDown('W') || IsKeyPressed('W')) 
            && ((IsKeyDown('D') || IsKeyPressed('D')))){
                playerHitBox.y = obstacles[i].first.rect.y + obstacles[i].first.rect.height;
            }

/////////////////////////////////////////////

            else if((this->dir == this->playerdir::up || IsKeyDown('W')) && !IsKeyDown('A') && !IsKeyDown('D')  &&
            playerHitBox.y + playerHitBox.height > obstacles[i].first.rect.y + obstacles[i].first.rect.height){
                playerHitBox.y = obstacles[i].first.rect.y + obstacles[i].first.rect.height;
                //this->upSide = false;
            }
            else if((this->dir == this->playerdir::down || IsKeyDown('S')) && !IsKeyDown('A') && !IsKeyDown('D') &&
            playerHitBox.y <= obstacles[i].first.rect.y ){
                playerHitBox.y = obstacles[i].first.rect.y - playerHitBox.height;
                //this->downSide = false;
            }
            

            else if((this->dir == this->playerdir::right || IsKeyDown('D')) &&
            playerHitBox.x <= obstacles[i].first.rect.x){
                playerHitBox.x = obstacles[i].first.rect.x - playerHitBox.width;
                //this->rightSide = false;
            }
            else if((this->dir == this->playerdir::left || IsKeyDown('A')) &&
            playerHitBox.x + playerHitBox.width > obstacles[i].first.rect.x + obstacles[i].first.rect.width){
                playerHitBox.x = obstacles[i].first.rect.x + obstacles[i].first.rect.width;
                //this->leftSide = false;
            }
            
            
        }
        else
        {
            this->rightSide = true;
            this->leftSide = true;
            this->upSide = true;
            this->downSide = true;
        }
    }
    

    if((IsKeyDown('D') || IsKeyPressed('D')) && (IsKeyDown('A') || IsKeyPressed('A'))){
            if(this->dir == this->playerdir::right && this->rightSide)this->playerHitBox.x += this->speed*delta;
            else if(this->dir == this->playerdir::left && this->leftSide)this->playerHitBox.x -= this->speed*delta;
    }
    else if ((IsKeyDown('A') || IsKeyPressed('A')) && (!IsKeyDown('D') || !IsKeyPressed('D'))){
     if(this->leftSide)this->playerHitBox.x -= this->speed*delta;
    }
    else if ((IsKeyDown('D') || IsKeyPressed('D')) && (!IsKeyDown('A') || !IsKeyPressed('A'))){
     if(this->rightSide)this->playerHitBox.x += this->speed*delta;
    }


    if ((IsKeyDown('W') || IsKeyPressed('W')) && (IsKeyDown('S') || IsKeyPressed('S'))){
        if(this->dir == this->playerdir::up && this->upSide) this->playerHitBox.y -= this->speed*delta;
        else if(this->dir == this->playerdir::down && this->downSide) this->playerHitBox.y += this->speed*delta;
    }
    else if ((IsKeyDown('S') || IsKeyPressed('S')) && (!IsKeyDown('W') || !IsKeyPressed('W'))){
        if(this->downSide)this->playerHitBox.y += this->speed*delta;
    }
    else if((IsKeyDown('W') || IsKeyPressed('W')) && (!IsKeyDown('S') || !IsKeyPressed('S'))){
        if(this->upSide)this->playerHitBox.y -= this->speed*delta;
    }
}


// void player::IsPlayerCheckCollision(const std::vector <Rectangle> &obstacles){

//     switch(GetKeyPressed()){
//         case 'W':
//             this->dir = this->playerdir::up;
//             break;

//         case 'S':
//             this->dir = this->playerdir::down;
//             break;

//         case 'A':
//             this->dir = this->playerdir::left;
//             break;

//         case 'D':
//             this->dir = this->playerdir::right;
//             break;
//     }

//     for(int i = 0; i < static_cast<int>(obstacles.size()); i++){
//         //if(CheckCollisionRecs(this->playerHitBox, obstacles[i])){

//             if(IsKeyDown('D') && this->dir == right){
//                 this->temp.right = true;
//             }
//             else
//                 this->temp.right = false;

//             if(IsKeyDown('A') && this->dir == left){
//                 this->temp.left = true;
//             }
//             else
//                 this->temp.left = false;

//             if(IsKeyDown('S') && this->dir == down){
//                 this->temp.up = true;
//             }
//             else
//                 this->temp.up = false;

//             if(IsKeyDown('W') && this->dir == up){
//                 this->temp.down = true;
//             }
//             else
//                 this->temp.down = false;
    
//         //}
//     }
// }

void player::update(const std::vector <Rectangle> &obstacles){

    // IsPlayerCheckCollision(obstacles);

    // if ((IsKeyDown('W') || IsKeyPressed('W')) && (IsKeyDown('S') || IsKeyPressed('S')) 
    //     && (!this->temp.up && !this->temp.down)){
    //         if(dir == up) this->playerHitBox.y -= this->speed;
    //         else if(dir == down) this->playerHitBox.y += this->speed;
    //     }
    //     else if ((IsKeyDown('S') || IsKeyPressed('S')) && (!IsKeyDown('W') || !IsKeyPressed('W'))
    //      && !this->temp.up) 
    //         this->playerHitBox.y += this->speed;
    //     else if((IsKeyDown('W') || IsKeyPressed('W')) && (!IsKeyDown('S') || !IsKeyPressed('S'))
    //      && !this->temp.down)
    //         this->playerHitBox.y -= this->speed;

    //     if((IsKeyDown('D') || IsKeyPressed('D')) && (IsKeyDown('A') || IsKeyPressed('A'))){
    //         if(dir == right)this->playerHitBox.x += this->speed;
    //         else if(dir == left)this->playerHitBox.x -= this->speed;
    //     }
    //     else if ((IsKeyDown('A') || IsKeyPressed('A')) && (!IsKeyDown('D') || !IsKeyPressed('D')) 
    //      && !this->temp.left)
    //         this->playerHitBox.x -= this->speed;
    //     else if ((IsKeyDown('D') || IsKeyPressed('D')) && (!IsKeyDown('A') || !IsKeyPressed('A')) 
    //      && !this->temp.right)
    //         this->playerHitBox.x += this->speed;

        
}