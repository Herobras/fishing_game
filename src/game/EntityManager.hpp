#pragma once
#include <vector>
#include <memory>
#include "entity/Entity.hpp"

class EntityManager {
public:
    void add(std::unique_ptr<Entity> entity);
    void removeMarked();
    void updateAll(float delta);
    void drawAll() const;
    void clear();
    std::vector<std::unique_ptr<Entity>>& getEntities();
    Entity* getPlayer(); 

private:
    std::vector<std::unique_ptr<Entity>> entities;
};
