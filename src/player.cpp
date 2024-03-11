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
            this->dir = playerdir::TOP;
            break;

        case 'S':
            this->dir = playerdir::BOTTOM;
            break;

        case 'A':
            this->dir = playerdir::LEFT;
            break;

        case 'D':
            this->dir = playerdir::RIGHT;
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
                    this->RectSideCollision = playerdir::TOP;
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
                    this->RectSideCollision = playerdir::BOTTOM;
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
                    this->RectSideCollision = playerdir::LEFT;
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
                    this->RectSideCollision = playerdir::RIGHT;
                }
            }
        }

        else {
            this->RectSideCollision = playerdir::NONE;
        }
        }

    if((IsKeyDown('D') || IsKeyPressed('D')) && (IsKeyDown('A') || IsKeyPressed('A'))){
            if(this->dir == playerdir::RIGHT && this->RectSideCollision != playerdir::RIGHT)
                this->playerHitBox.x += this->speed*delta;
            else if(this->dir == playerdir::LEFT && this->RectSideCollision != playerdir::LEFT)
                this->playerHitBox.x -= speed*delta;
    }
    else if ((IsKeyDown('A') || IsKeyPressed('A')) && (!IsKeyDown('D') || !IsKeyPressed('D'))){
     if(this->RectSideCollision != playerdir::LEFT)this->playerHitBox.x -= this->speed*delta;
    }
    else if ((IsKeyDown('D') || IsKeyPressed('D')) && (!IsKeyDown('A') || !IsKeyPressed('A'))){
     if(this->RectSideCollision != playerdir::RIGHT)this->playerHitBox.x += this->speed*delta;
    }


    if ((IsKeyDown('W') || IsKeyPressed('W')) && (IsKeyDown('S') || IsKeyPressed('S'))){
        if(this->dir == playerdir::TOP && this->RectSideCollision != playerdir::TOP)
            this->playerHitBox.y -= this->speed*delta;
        else if(this->dir == playerdir::BOTTOM && this->RectSideCollision != playerdir::BOTTOM)
            this->playerHitBox.y += this->speed*delta;
    }
    else if ((IsKeyDown('S') || IsKeyPressed('S')) && (!IsKeyDown('W') || !IsKeyPressed('W'))){
        if(this->RectSideCollision != playerdir::BOTTOM)this->playerHitBox.y += this->speed*delta;
    }
    else if((IsKeyDown('W') || IsKeyPressed('W')) && (!IsKeyDown('S') || !IsKeyPressed('S'))){
        if(this->RectSideCollision != playerdir::TOP)this->playerHitBox.y -= this->speed*delta;
    }

    if(IsKeyPressed('Q')){
        if(this->speed != 800)this->speed = 800;
        else this->speed = 300;
    }
}