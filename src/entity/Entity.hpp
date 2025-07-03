#pragma once

#include "raylib.h"
#include "utils/Direction.hpp"


enum class EntityType {
    PLAYER,
    ENEMY,
    HOOK
};

class Entity {
protected:
    float posX, posY;
    bool toBeDeleted = false;
public:
    Entity();
    Entity(float x, float y);
    virtual ~Entity() = default;

    float get_posX() const;
    float get_posY() const;
    void set_position(float x, float y);
    void move(Direction dir, float distance);

    virtual void bounds_check_x(float &x);
    virtual void bounds_check_y(float &y);

    virtual void draw() const = 0;
    virtual void update(float delta) = 0;
    virtual EntityType get_type() const = 0;
    virtual Rectangle getBoundingBox() const = 0;

    void markForDeletion();
    bool isMarkedForDeletion() const;
};
