#include "raylib.h"

#include "entity/Hook.hpp"


//Constructor completo
Hook::Hook(float x,float y,int w, int h, Color col, float weight, float m_lift) : MyRectangle(x,y,w,h,col), weight(weight), max_lift(m_lift) {}


void Hook::update(float delta){
    //fisicas de hundimiento y movimiento en el agua en general
}

EntityType Hook::get_type() const {
    return EntityType::HOOK;
}