#include "raylib.h"

#include "entity/MyRectangle.hpp"
#include "Constants.hpp"
using namespace Constants;

// Constructor mínimo, sin posicion
MyRectangle::MyRectangle(int w, int h, Color col) : width(w), height(h), color(col) {}

// Constructor completo, le agrega posición
MyRectangle::MyRectangle(float x, float y, int w, int h, Color col) : Entity(x, y), width(w), height(h), color(col) {}

// Definición de update para MyRectangle
void MyRectangle::update(float delta)
{
    // No hace nada
}

// Función de dibujado de rectangulos
void MyRectangle::draw() const
{
    DrawRectangle(int(posX), int(posY), width, height, color);
}

// Checkeo de posición within limits para x
void MyRectangle::bounds_check_x(float &x)
{
    if (x > SCREEN_WIDTH - width)
    {
        posX = SCREEN_WIDTH - width;
    }
    else if (x < 0)
    {
        posX = 0;
    }
    else
    {
        posX = x;
    }
    return;
}

// Checkeo de posición within limits para y
void MyRectangle::bounds_check_y(float &y)
{
    if (y > SCREEN_HEIGHT - height)
    {
        posY = SCREEN_HEIGHT - height;
    }
    else if (y < 0)
    {
        posY = 0;
    }
    else
    {
        posY = y;
    }
    return;
}

// Función que retorna un Rectangle de raylib para colisiones
Rectangle MyRectangle::getBoundingBox() const
{
    Rectangle ret;
    ret.x = get_posX();
    ret.y = get_posY();
    ret.width = width;
    ret.height = height;
    return ret;
}