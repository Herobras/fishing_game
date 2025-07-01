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
    bool up=false,down=false,left=false,right=false;
    if (IsKeyDown(KEY_DOWN)){
        down = true;
    }
    if (IsKeyDown(KEY_UP)){
        up = true;
    }
    if (IsKeyDown(KEY_RIGHT)){
        right = true;
    }
    if (IsKeyDown(KEY_LEFT)){
        left = true;
    }

    Direction dirv = NONE, dirh = NONE;


    // vertical direction
    if ((up && down) || (!up && !down)){
        dirv = NONE;
    }
    else if (up){
        dirv = UP;
    }
    else if (down){
        dirv = DOWN;
    }
    

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


    // direction decider
    if (dirv == NONE){
    
        return dirh;
    }
    else if (dirh == RIGHT){
        if (dirv == UP){
            return UP_RIGHT;
        }
        else {
            return DOWN_RIGHT;
        }
    }
    else if (dirh == LEFT){
        if (dirv == UP){
            return UP_LEFT;
        }
        else {
            return DOWN_LEFT;
        }
    }
    else if (dirv == UP){
        return UP;
    }
    else if (dirv == DOWN){
        return DOWN;
    }
    
    if (dirh == NONE){
        return dirv;
    }


    

    return NONE;
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