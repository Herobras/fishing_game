#pragma once

#include "MyRectangle.hpp"

class Hook : public MyRectangle {
    const float weight;
    const float max_lift;
public:
    Hook(float x,float y,int w, int h, Color col, float weight, float m_lift);
    void update (float delta) override;
    EntityType get_type() const override;
};