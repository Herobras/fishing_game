#pragma once

#include <memory>

#include "MyRectangle.hpp"
#include "Hook.hpp"

class Player : public MyRectangle {
    const float base_speed;
    float speed;
public:
    Player(int w, int h, Color col, float s);
    Player(float x,float y,int w, int h, Color col, float s);
    void update(float delta) override;
    std::unique_ptr<Hook> fireHook();
    EntityType get_type() const override;
private:
    Direction getInput();
    void movSpeed();
};
