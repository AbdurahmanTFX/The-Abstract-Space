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


 void player::update(std::vector<std::pair<EnvItem, EnvItem>> obstacles, float delta) {
    // Получаем состояние клавиш для движения
    bool isKeyLeftPressed = IsKeyDown('A') || IsKeyPressed('A');
    bool isKeyRightPressed = IsKeyDown('D') || IsKeyPressed('D');
    bool isKeyUpPressed = IsKeyDown('W') || IsKeyPressed('W');
    bool isKeyDownPressed = IsKeyDown('S') || IsKeyPressed('S');

    // Определяем направление движения
    playerdir newDir = playerdir::NONE;
    if (isKeyLeftPressed && isKeyUpPressed) newDir = playerdir::TOP_LEFT;
    else if (isKeyRightPressed && isKeyUpPressed) newDir = playerdir::TOP_RIGHT;
    else if (isKeyLeftPressed && isKeyDownPressed) newDir = playerdir::BOTTOM_LEFT;
    else if (isKeyRightPressed && isKeyDownPressed) newDir = playerdir::BOTTOM_RIGHT;
    else if (isKeyUpPressed) newDir = playerdir::TOP;
    else if (isKeyDownPressed) newDir = playerdir::BOTTOM;
    else if (isKeyLeftPressed) newDir = playerdir::LEFT;
    else if (isKeyRightPressed) newDir = playerdir::RIGHT;

    // Сохраняем начальные координаты игрока
    float originalX = this->playerHitBox.x;
    float originalY = this->playerHitBox.y;

    // Флаг для обозначения столкновения
    bool collisionDetected = false;

    // Обновляем координаты игрока в соответствии с направлением
    switch (newDir) {
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
    if (IsKeyPressed('Q')) {
        this->speed = (this->speed != 800) ? 800 : 300;
    }

    // Проверяем столкновения с препятствиями
    for(const auto& obstaclePair : obstacles) {
        const Rectangle& obstacleRect = obstaclePair.first.rect;

        if (CheckCollisionRecs(this->playerHitBox, obstacleRect) && obstaclePair.first.blocking) {
            // Возвращаем игрока на предыдущие координаты
            this->playerHitBox.x = originalX;
            this->playerHitBox.y = originalY;
            if(newDir == playerdir::BOTTOM_LEFT
            && playerHitBox.y + playerHitBox.height < obstacleRect.y){
                this->playerHitBox.x -= speed * delta;
            }
            else if(newDir == playerdir::BOTTOM_RIGHT
            && playerHitBox.y + playerHitBox.height < obstacleRect.y){
                this->playerHitBox.x += speed * delta;
            }
            else if(newDir == playerdir::TOP_LEFT
            && playerHitBox.y > obstacleRect.y + obstacleRect.height){
                this->playerHitBox.x -= speed * delta;
            }
            else if(newDir == playerdir::TOP_RIGHT
            && playerHitBox.y > obstacleRect.y + obstacleRect.height){
                this->playerHitBox.x += speed * delta;
            }
            else if((newDir == playerdir::BOTTOM_LEFT || newDir == playerdir::BOTTOM_RIGHT)
            && (playerHitBox.y < obstacleRect.y + obstacleRect.height
            || playerHitBox.y + playerHitBox.height > obstacleRect.y)){
                this->playerHitBox.y += speed * delta;
            }
            else if(newDir == playerdir::TOP_LEFT || newDir == playerdir::TOP_RIGHT
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
    
