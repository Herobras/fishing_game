#include "raylib.h"

#include <chrono>

#include "entity/Enemy.hpp"
#include "utils/Random.hpp"

using namespace std::chrono;


// Constructor básico, sin posicion
Enemy::Enemy(int w, int h, Color col, float s) : MyRectangle(w,h,col) {
    speed=s;
    auto now = system_clock::now();
    born_date = duration_cast<milliseconds>(now.time_since_epoch()).count();
    move_dir = NONE;
}

// Constructor completo
Enemy::Enemy(float x,float y,int w, int h, Color col, float s) : MyRectangle(x,y,w,h,col) {
    speed=s;
    auto now = system_clock::now();
    born_date = duration_cast<milliseconds>(now.time_since_epoch()).count();
    move_dir = NONE;
}

// Type getter de enemy
EntityType Enemy::get_type() const {return EntityType::ENEMY;}

// Update para
void Enemy::update(float delta) {
move(move_dir,speed*delta);
        auto now = system_clock::now();
        int now_millis = duration_cast<milliseconds>(now.time_since_epoch()).count();
        if (now_millis - born_date >= 200){
            move_dir = random_dir();
            born_date = now_millis;
        }
}