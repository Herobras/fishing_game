#pragma once

#include "MyRectangle.hpp"

class Enemy : public MyRectangle {
    float speed;
    int born_date;
    Direction move_dir;
public:
    Enemy(int w, int h, Color col, float s);
    Enemy(float x,float y,int w, int h, Color col, float s);
    EntityType get_type() const override;
    void update(float delta) override;
};
