#pragma once

#include "Entity.hpp"

class MyRectangle : public Entity {
protected:
    int width, height;
    Color color;
public:
    MyRectangle(int w, int h, Color col);
    MyRectangle(float x, float y, int w, int h, Color col);
    void update(float delta) override;
    void draw() const override;
    void bounds_check_x(float &x) override;
    void bounds_check_y(float &y) override;
    Rectangle getBoundingBox() const override;
};
