#include "EnvItem.h"

void EnvItem::AllSet(const Rectangle& rect, const bool& blocking, const Color& color, const float& speed){
    this->rect = rect;
    this->blocking = blocking;
    this->color = color;
    this->speed = speed;
}

dir EnvItem::GetDir(){
    return this->Dir;
}

void EnvItem::update(Vector2 finishPos, float delta, Rectangle plr) {
    // Получаем состояние клавиш для движения
    bool LeftMove = this->rect.x > finishPos.x;
    bool RightMove = this->rect.x < finishPos.x;
    bool UpMove = this->rect.y > finishPos.y;
    bool DownMove = this->rect.y < finishPos.y;

    float originalX = this->rect.x;
    float originalY = this->rect.y;

    if (LeftMove && UpMove) this->Dir = dir::TOP_LEFT;
    else if (RightMove && UpMove) this->Dir = dir::TOP_RIGHT;
    else if (LeftMove && DownMove) this->Dir = dir::BOTTOM_LEFT;
    else if (RightMove && DownMove) this->Dir = dir::BOTTOM_RIGHT;
    else if (UpMove) this->Dir = dir::TOP;
    else if (DownMove) this->Dir = dir::BOTTOM;
    else if (LeftMove) this->Dir = dir::LEFT;
    else if (RightMove) this->Dir = dir::RIGHT;
    else if(this->rect.y == finishPos.y && this->rect.x == finishPos.x) this->Dir = dir::NONE;

    // Обновляем координаты игрока в соответствии с направлением
    switch (this->Dir) {
        case dir::TOP_LEFT:
            this->rect.x -= speed * delta;
            this->rect.y -= speed * delta;
            if(rect.x <= finishPos.x){
                rect.x = finishPos.x;
            }
            if(rect.y <= finishPos.y){
                rect.y = finishPos.y;
            }
            break;
        case dir::TOP_RIGHT:
            this->rect.x += speed * delta;
            this->rect.y -= speed * delta;
            if(rect.x >= finishPos.x){
                rect.x = finishPos.x;
            }
            if(rect.y <= finishPos.y){
                rect.y = finishPos.y;
            }
            break;
        case dir::BOTTOM_LEFT:
            this->rect.x -= speed * delta;
            this->rect.y += speed * delta;
            if(rect.x <= finishPos.x){
                rect.x = finishPos.x;
            }
            if(rect.y >= finishPos.y){
                rect.y = finishPos.y;
            }
            break;
        case dir::BOTTOM_RIGHT:
            this->rect.x += speed * delta;
            this->rect.y += speed * delta;
            if(rect.x >= finishPos.x){
                rect.x = finishPos.x;
            }
            if(rect.y >= finishPos.y){
                rect.y = finishPos.y;
            }
            break;
        case dir::LEFT:
            this->rect.x -= speed * delta;
            if(rect.x <= finishPos.x){
                rect.x = finishPos.x;
            }
            break;
        case dir::RIGHT:
            this->rect.x += speed * delta;
            if(rect.x >= finishPos.x){
                rect.x = finishPos.x;
            }
            break;
        case dir::TOP:
            this->rect.y -= speed * delta;
            if(rect.y <= finishPos.y){
                rect.y = finishPos.y;
            }
            break;
        case dir::BOTTOM:
            this->rect.y += speed * delta;
            if(rect.y >= finishPos.y){
                rect.y = finishPos.y;
            }
            break;
        default:
            break;
    }
 }