#include "player.h"

player::player(const Rectangle &playerRec, const Rectangle &dashBar){
    this->rect = playerRec;
    this->dashProgressBar = dashBar;
}

void player::SetDashPos(const Rectangle &dashBar){
    this->dashProgressBar.y = dashBar.y;
    this->dashProgressBar.x = dashBar.x;
}

void player::SetSpeed(const int &speed){
    this->speed = speed;
}

void player::SetDashColor(const Color &color){
    this->dashColor = color;
}

Rectangle player::GetRec(){
    return this->rect;
}

Rectangle player::GetDashBarRec(){
    return this->dashProgressBar;
}

Color player::GetDashColor(){
    return this->dashColor;
}

 void player::update(std::vector <std::pair<EnvItem, Vector2>> obstacles, float delta, const float &dashBarWidth) {
    
    // Получаем состояние клавиш для движения
    bool isKeyLeftPressed = IsKeyDown('A') || IsKeyPressed('A');
    bool isKeyRightPressed = IsKeyDown('D') || IsKeyPressed('D');
    bool isKeyUpPressed = IsKeyDown('W') || IsKeyPressed('W');
    bool isKeyDownPressed = IsKeyDown('S') || IsKeyPressed('S');

    // Определяем направление движения
    dir Dir = dir::NONE;
    if (isKeyLeftPressed && isKeyUpPressed) Dir = dir::TOP_LEFT;
    else if (isKeyRightPressed && isKeyUpPressed) Dir = dir::TOP_RIGHT;
    else if (isKeyLeftPressed && isKeyDownPressed) Dir = dir::BOTTOM_LEFT;
    else if (isKeyRightPressed && isKeyDownPressed) Dir = dir::BOTTOM_RIGHT;
    else if (isKeyUpPressed) Dir = dir::TOP;
    else if (isKeyDownPressed) Dir = dir::BOTTOM;
    else if (isKeyLeftPressed) Dir = dir::LEFT;
    else if (isKeyRightPressed) Dir = dir::RIGHT;

    // Сохраняем начальные координаты игрока
    float originalX = this->rect.x;
    float originalY = this->rect.y;

    // Флаг для обозначения столкновения
    bool collisionDetected = false;
    
    if(IsKeyPressed(KEY_SPACE) && !this->dash && this->dashProgressBar.width >= dashBarWidth){
        this->dashProgressBar.width = 0;
        this->dashColor = RED;
        this->dash = true;
        this->dashDir = Dir;
        this->OriginalSpeed = this->speed;
        this->speed = this->speed * 3;
        this->dashCurrentTimer = GetTime();
        this->dashCurrentBarTimer = GetTime();
        this->dashDurationTimer = this->dashCurrentTimer + 0.05;
        this->dashDurationBarTimer = this->dashCurrentBarTimer + 0.1;
    }
    else if(this->dash && this->dashProgressBar.width <= dashBarWidth){
        this->dashCurrentTimer = GetTime();
        this->dashCurrentBarTimer = GetTime();

        dashProgressBar.width = 
            (dashBarWidth / 100) * ((this->dashCurrentBarTimer - this->dashDurationBarTimer) * 100);
        
        if((this->dashDurationTimer - this->dashCurrentTimer) <= 0){
            if(this->dashProgressBar.width >= dashBarWidth){
                this->dash = false;
                this->dashColor = GREEN;
            }
            this->dashDir = dir::NONE;
            this->speed = this->OriginalSpeed;
        }
    }
    
    // Обновляем координаты игрока в соответствии с направлением
    switch (Dir) {
        case dir::TOP_LEFT:
            this->rect.x -= speed * delta;
            this->rect.y -= speed * delta;
            break;
        case dir::TOP_RIGHT:
            this->rect.x += speed * delta;
            this->rect.y -= speed * delta;
            break;
        case dir::BOTTOM_LEFT:
            this->rect.x -= speed * delta;
            this->rect.y += speed * delta;
            break;
        case dir::BOTTOM_RIGHT:
            this->rect.x += speed * delta;
            this->rect.y += speed * delta;
            break;
        case dir::LEFT:
            this->rect.x -= speed * delta;
            break;
        case dir::RIGHT:
            this->rect.x += speed * delta;
            break;
        case dir::TOP:
            this->rect.y -= speed * delta;
            break;
        case dir::BOTTOM:
            this->rect.y += speed * delta;
            break;
        default:
            break;
    }

    switch (this->dashDir) {
        case dir::TOP_LEFT:
            this->rect.x -= speed * delta;
            this->rect.y -= speed * delta;
            break;
        case dir::TOP_RIGHT:
            this->rect.x += speed * delta;
            this->rect.y -= speed * delta;
            break;
        case dir::BOTTOM_LEFT:
            this->rect.x -= speed * delta;
            this->rect.y += speed * delta;
            break;
        case dir::BOTTOM_RIGHT:
            this->rect.x += speed * delta;
            this->rect.y += speed * delta;
            break;
        case dir::LEFT:
            this->rect.x -= speed * delta;
            break;
        case dir::RIGHT:
            this->rect.x += speed * delta;
            break;
        case dir::TOP:
            this->rect.y -= speed * delta;
            break;
        case dir::BOTTOM:
            this->rect.y += speed * delta;
            break;
        default:
            break;
    }

    // Проверяем столкновения с препятствиями
    for(const auto& obstaclePair : obstacles) {
        const Rectangle& obstacleRect = obstaclePair.first.rect;
 
        if (CheckCollisionRecs(this->rect, obstacleRect) && obstaclePair.first.blocking) {
            // Возвращаем игрока на предыдущие координаты
            this->rect.x = originalX;
            this->rect.y = originalY;
            
            if((obstaclePair.first.Dir == dir::BOTTOM
            || obstaclePair.first.Dir == dir::BOTTOM_LEFT
            || obstaclePair.first.Dir == dir::BOTTOM_RIGHT)
            && this->rect.y + obstaclePair.first.speed * delta >= obstacleRect.y + obstacleRect.height){
                this->rect.y += obstaclePair.first.speed * delta;
            }
            else if(obstaclePair.first.Dir == dir::BOTTOM_RIGHT){
                this->rect.x += obstaclePair.first.speed * delta;
            }
            else if(obstaclePair.first.Dir == dir::BOTTOM_LEFT){
                this->rect.x -= obstaclePair.first.speed * delta;
            }
            else if((obstaclePair.first.Dir == dir::TOP
            || obstaclePair.first.Dir == dir::TOP_LEFT
            || obstaclePair.first.Dir == dir::TOP_RIGHT)
            && this->rect.y + this->rect.height - obstaclePair.first.speed * delta <= obstacleRect.y){
                this->rect.y -= obstaclePair.first.speed * delta;
            }
            else if(obstaclePair.first.Dir == dir::TOP_RIGHT){
                this->rect.x += obstaclePair.first.speed * delta;
            }
            else if(obstaclePair.first.Dir == dir::TOP_LEFT){
                this->rect.x -= obstaclePair.first.speed * delta;
            }
            else if(obstaclePair.first.Dir == dir::TOP){
                this->rect.y -= obstaclePair.first.speed * delta;
            }
            else if(obstaclePair.first.Dir == dir::RIGHT){
                this->rect.x += obstaclePair.first.speed * delta;
            }
            else if(obstaclePair.first.Dir == dir::LEFT){
                this->rect.x -= obstaclePair.first.speed * delta;
            }

            if((Dir == dir::BOTTOM_LEFT || this->dashDir == dir::BOTTOM_LEFT) 
            && rect.y + rect.height - 1 < obstacleRect.y){
                this->rect.x -= speed * delta;
            }
            else if((Dir == dir::BOTTOM_RIGHT || this->dashDir == dir::BOTTOM_RIGHT)
            && rect.y + rect.height - 1 < obstacleRect.y){
                this->rect.x += speed * delta;
            }
            else if((Dir == dir::TOP_LEFT || this->dashDir == dir::TOP_LEFT)
            && rect.y + 1 > obstacleRect.y + obstacleRect.height){
                this->rect.x -= speed * delta;
            }
            else if((Dir == dir::TOP_RIGHT || this->dashDir == dir::TOP_RIGHT)
            && rect.y + 1 > obstacleRect.y + obstacleRect.height){
                this->rect.x += speed * delta;
            }
            else if((Dir == dir::BOTTOM_LEFT || Dir == dir::BOTTOM_RIGHT 
            || this->dashDir == dir::BOTTOM_LEFT || this->dashDir == dir::BOTTOM_RIGHT)
            && (rect.y - 1 < obstacleRect.y + obstacleRect.height
            || rect.y + rect.height > obstacleRect.y)){
                this->rect.y += speed * delta;
            }
            else if((Dir == dir::TOP_LEFT || Dir == dir::TOP_RIGHT 
            || this->dashDir == dir::TOP_LEFT || this->dashDir == dir::TOP_RIGHT)
            && (rect.y + 1 > obstacleRect.y + obstacleRect.height
            || rect.y + rect.height > obstacleRect.y)){
                this->rect.y -= speed * delta;
            }
            break; // Выходим из цикла после первого обнаружения столкновения
        }
    }
 }
    
