#include "raylib.h"

#include "entity/Player.hpp"



//Constructor mínimo, sin posicion
Player::Player(int w, int h, Color col, float s) : MyRectangle(w,h,col), base_speed(s) {speed = base_speed;}

//Constructor completo
Player::Player(float x,float y,int w, int h, Color col, float s) : MyRectangle(x,y,w,h,col), base_speed(s) {}

// Update para player
void Player::update(float delta){
    movSpeed();
    move(getInput(),speed*delta);
}

// GetType para player
EntityType Player::get_type() const{
    return EntityType::PLAYER;
}

// función que toma el input por teclado y cambia dirmov del player
Direction Player::getInput() {
    bool left=false,right=false;

    if (IsKeyDown(KEY_RIGHT)){
        right = true;
    }
    if (IsKeyDown(KEY_LEFT)){
        left = true;
    }

    Direction dirh = NONE;



    //horizontal direction
    if ((left && right)||(!left && !right)){
        dirh = NONE;
    }
    else if (left){
        dirh = LEFT;
    }
    else if (right){
        dirh = RIGHT;
    }

   

    return dirh;
}


// Funcion que modifica la velocidad de movimiento
void Player::movSpeed() {
    if (IsKeyDown(KEY_LEFT_SHIFT)){
        speed = base_speed*2;
        }
        else {
            speed = base_speed;
        }
    return;
}

// Función que lanza y crea el anzuelo
std::unique_ptr<Hook> Player::fireHook() {
    float hookX = get_posX() + width / 2;
    float hookY = get_posY() + height + 4 * height;
    return std::make_unique<Hook>(
        hookX,
        hookY,
        static_cast<float>(width) / 10.0f,
        static_cast<float>(height) / 10.0f,
        color,
        static_cast<float>(0),
        static_cast<float>(0)
    );
}