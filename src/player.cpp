#include "player.h"

player::player(const Rectangle &playerRec, const Rectangle &dashBar){
    this->playerHitBox = playerRec;
    this->dashProgressBar = dashBar;
}

void player::SetSpeed(const int &speed){
    this->speed = speed;
}

void player::SetDashColor(const Color &clr){
    this->dashColor = clr;
}

Rectangle player::GetPlayerRec(){
    return this->playerHitBox;
}

Rectangle player::GetDashBarRec(){
    return this->dashProgressBar;
}

Color player::GetDashColor(){
    return this->dashColor;
}


 void player::update(std::vector<std::pair<EnvItem, EnvItem>> obstacles, float delta, const float &dashBarWidth) {
    // Получаем состояние клавиш для движения
    bool isKeyLeftPressed = IsKeyDown('A') || IsKeyPressed('A');
    bool isKeyRightPressed = IsKeyDown('D') || IsKeyPressed('D');
    bool isKeyUpPressed = IsKeyDown('W') || IsKeyPressed('W');
    bool isKeyDownPressed = IsKeyDown('S') || IsKeyPressed('S');

    // Определяем направление движения
    playerdir dir = playerdir::NONE;
    if (isKeyLeftPressed && isKeyUpPressed) dir = playerdir::TOP_LEFT;
    else if (isKeyRightPressed && isKeyUpPressed) dir = playerdir::TOP_RIGHT;
    else if (isKeyLeftPressed && isKeyDownPressed) dir = playerdir::BOTTOM_LEFT;
    else if (isKeyRightPressed && isKeyDownPressed) dir = playerdir::BOTTOM_RIGHT;
    else if (isKeyUpPressed) dir = playerdir::TOP;
    else if (isKeyDownPressed) dir = playerdir::BOTTOM;
    else if (isKeyLeftPressed) dir = playerdir::LEFT;
    else if (isKeyRightPressed) dir = playerdir::RIGHT;

    // Сохраняем начальные координаты игрока
    float originalX = this->playerHitBox.x;
    float originalY = this->playerHitBox.y;

    // Флаг для обозначения столкновения
    bool collisionDetected = false;

    //dashProgressBar.width = (dashProgressBar.width / 100) * ();
    
    if(IsKeyPressed(KEY_SPACE) && !this->dash && this->dashProgressBar.width >= dashBarWidth){
        this->dashProgressBar.width = 0;
        this->dashColor = RED;
        this->dash = true;
        this->dashDir = dir;
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
            this->dashDir = playerdir::NONE;
            this->speed = this->OriginalSpeed;
        }
    }
    
    
    // Обновляем координаты игрока в соответствии с направлением
    switch (dir) {
        case playerdir::TOP_LEFT:
            this->playerHitBox.x -= speed * delta;
            this->playerHitBox.y -= speed * delta;
            break;
        case playerdir::TOP_RIGHT:
            this->playerHitBox.x += speed * delta;
            this->playerHitBox.y -= speed * delta;
            break;
        case playerdir::BOTTOM_LEFT:
            this->playerHitBox.x -= speed * delta;
            this->playerHitBox.y += speed * delta;
            break;
        case playerdir::BOTTOM_RIGHT:
            this->playerHitBox.x += speed * delta;
            this->playerHitBox.y += speed * delta;
            break;
        case playerdir::LEFT:
            this->playerHitBox.x -= speed * delta;
            break;
        case playerdir::RIGHT:
            this->playerHitBox.x += speed * delta;
            break;
        case playerdir::TOP:
            this->playerHitBox.y -= speed * delta;
            break;
        case playerdir::BOTTOM:
            this->playerHitBox.y += speed * delta;
            break;
        default:
            break;
    }

    switch (this->dashDir) {
        case playerdir::TOP_LEFT:
            this->playerHitBox.x -= speed * delta;
            this->playerHitBox.y -= speed * delta;
            break;
        case playerdir::TOP_RIGHT:
            this->playerHitBox.x += speed * delta;
            this->playerHitBox.y -= speed * delta;
            break;
        case playerdir::BOTTOM_LEFT:
            this->playerHitBox.x -= speed * delta;
            this->playerHitBox.y += speed * delta;
            break;
        case playerdir::BOTTOM_RIGHT:
            this->playerHitBox.x += speed * delta;
            this->playerHitBox.y += speed * delta;
            break;
        case playerdir::LEFT:
            this->playerHitBox.x -= speed * delta;
            break;
        case playerdir::RIGHT:
            this->playerHitBox.x += speed * delta;
            break;
        case playerdir::TOP:
            this->playerHitBox.y -= speed * delta;
            break;
        case playerdir::BOTTOM:
            this->playerHitBox.y += speed * delta;
            break;
        default:
            break;
    }


    // Переключение скорости при нажатии клавиши Q

    // Проверяем столкновения с препятствиями
    for(const auto& obstaclePair : obstacles) {
        const Rectangle& obstacleRect = obstaclePair.first.rect;

        if (CheckCollisionRecs(this->playerHitBox, obstacleRect) && obstaclePair.first.blocking) {
            // Возвращаем игрока на предыдущие координаты
            this->playerHitBox.x = originalX;
            this->playerHitBox.y = originalY;
            if((dir == playerdir::BOTTOM_LEFT || this->dashDir == playerdir::BOTTOM_LEFT) 
            && playerHitBox.y + playerHitBox.height < obstacleRect.y){
                this->playerHitBox.x -= speed * delta;
            }
            else if((dir == playerdir::BOTTOM_RIGHT || this->dashDir == playerdir::BOTTOM_RIGHT)
            && playerHitBox.y + playerHitBox.height < obstacleRect.y){
                this->playerHitBox.x += speed * delta;
            }
            else if((dir == playerdir::TOP_LEFT || this->dashDir == playerdir::TOP_LEFT)
            && playerHitBox.y > obstacleRect.y + obstacleRect.height){
                this->playerHitBox.x -= speed * delta;
            }
            else if((dir == playerdir::TOP_RIGHT || this->dashDir == playerdir::TOP_RIGHT)
            && playerHitBox.y > obstacleRect.y + obstacleRect.height){
                this->playerHitBox.x += speed * delta;
            }
            else if((dir == playerdir::BOTTOM_LEFT || dir == playerdir::BOTTOM_RIGHT 
            || this->dashDir == playerdir::BOTTOM_LEFT || this->dashDir == playerdir::BOTTOM_RIGHT)
            && (playerHitBox.y < obstacleRect.y + obstacleRect.height
            || playerHitBox.y + playerHitBox.height > obstacleRect.y)){
                this->playerHitBox.y += speed * delta;
            }
            else if((dir == playerdir::TOP_LEFT || dir == playerdir::TOP_RIGHT 
            || this->dashDir == playerdir::TOP_LEFT || this->dashDir == playerdir::TOP_RIGHT)
            && (playerHitBox.y < obstacleRect.y + obstacleRect.height
            || playerHitBox.y + playerHitBox.height > obstacleRect.y)){
                this->playerHitBox.y -= speed * delta;
            }
            
            collisionDetected = true;
            break; // Выходим из цикла после первого обнаружения столкновения
        }
    }

    // Если было столкновение, не продолжаем обновление направления движения
    if (collisionDetected) {
        return;
    }
}
    
