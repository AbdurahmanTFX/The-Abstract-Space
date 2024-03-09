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


void player::update(std::vector <std::pair <EnvItem, int>> obstacles, float delta)
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
            if(playerHitBox.y + 4 > obstacles[i].first.rect.y + obstacles[i].first.rect.height
            && playerHitBox.x < obstacles[i].first.rect.x + obstacles[i].first.rect.width)
            {
                if(IsKeyDown('W')){
                    playerHitBox.y = obstacles[i].first.rect.y + obstacles[i].first.rect.height + 1;
                }
                else{
                    playerHitBox.y = obstacles[i].first.rect.y + obstacles[i].first.rect.height;
                    this->upSide = false;
                }
            }

            else if(playerHitBox.y - 4 + playerHitBox.height < obstacles[i].first.rect.y 
            && playerHitBox.x < obstacles[i].first.rect.x + obstacles[i].first.rect.width)
            {
                if(IsKeyDown('S')){
                    playerHitBox.y = obstacles[i].first.rect.y - playerHitBox.height - 1;
                }
                else{
                    playerHitBox.y = obstacles[i].first.rect.y - playerHitBox.height;
                    this->downSide = false;
                }
            }

            else if(playerHitBox.x + playerHitBox.width > obstacles[i].first.rect.x + obstacles[i].first.rect.width 
            && playerHitBox.y < obstacles[i].first.rect.y + obstacles[i].first.rect.height)
            {
                if(IsKeyDown('A')){
                    playerHitBox.x = obstacles[i].first.rect.x + obstacles[i].first.rect.width + 1;
                }
                else{
                    playerHitBox.x = obstacles[i].first.rect.x + obstacles[i].first.rect.width;
                    this->leftSide = false;
                }
            }

            else if(playerHitBox.x < obstacles[i].first.rect.x 
            && playerHitBox.y < obstacles[i].first.rect.y + obstacles[i].first.rect.height)
            {
                if(IsKeyDown('D')){
                    playerHitBox.x = obstacles[i].first.rect.x - playerHitBox.width - 1;
                }
                else{
                    playerHitBox.x = obstacles[i].first.rect.x - playerHitBox.width;
                    this->rightSide = false;
                }
            }
        }

        else {
            this->rightSide = true;
            this->leftSide = true;
            this->upSide = true;
            this->downSide = true;
            this->speed = 200;
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