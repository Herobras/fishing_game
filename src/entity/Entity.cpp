
#include "raylib.h"

#include "entity/Entity.hpp"
#include "Constants.hpp"
using namespace Constants;

// Constructor por defecto
Entity::Entity() : posX(0), posY(0) {}

// Constructor con posición inicial
Entity::Entity(float x, float y) : posX(x), posY(y) {}

// Getters
float Entity::get_posX() const {
    return posX;
}

float Entity::get_posY() const {
    return posY;
}

// Set posición
void Entity::set_position(float x, float y) {
    posX = x;
    posY = y;
}

// Movimiento con dirección y distancia
void Entity::move(Direction dir, float distance) {
    float _posX = posX;
    float _posY = posY;

    switch (dir) {
        case UP:           _posY -= distance; break;
        case DOWN:         _posY += distance; break;
        case LEFT:         _posX -= distance; break;
        case RIGHT:        _posX += distance; break;
        case UP_RIGHT:     _posX += distance; _posY -= distance; break;
        case UP_LEFT:      _posX -= distance; _posY -= distance; break;
        case DOWN_RIGHT:   _posX += distance; _posY += distance; break;
        case DOWN_LEFT:    _posX -= distance; _posY += distance; break;
        default: break;
    }

    bounds_check_x(_posX);
    bounds_check_y(_posY);
}

// Chequeo de bordes genérico (puede ser overrideado por clases derivadas)
void Entity::bounds_check_x(float &x) {
    if (x > SCREEN_WIDTH) {
        posX = SCREEN_WIDTH;
    } else if (x < 0) {
        posX = 0;
    } else {
        posX = x;
    }
}

void Entity::bounds_check_y(float &y) {
    if (y > SCREEN_HEIGHT) {
        posY = SCREEN_HEIGHT;
    } else if (y < 0) {
        posY = 0;
    } else {
        posY = y;
    }
}


//Funciones que ayudan al entity manager

void Entity::markForDeletion(){
    toBeDeleted = true;
}

bool Entity::isMarkedForDeletion() const {
    return toBeDeleted;
}