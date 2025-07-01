#include "raylib.h"

#include "game/EntityManager.hpp"



void EntityManager::add(std::unique_ptr<Entity> entity){
    entities.push_back(entity);
}

void EntityManager::removeMarked(){
    entities.erase(
        std::remove_if(entities.begin(), entities.end(),
            [](const std::unique_ptr<Entity>& e) {
                return e->isMarkedForDeletion();
            }),
        entities.end()
    );
}

void EntityManager::updateAll(float delta){
    for (auto it = entities.begin();it != entities.end();){
        (*it)-> update(delta);
    }
}

std::vector<std::unique_ptr<Entity>>& EntityManager::getEntities(){
    return entities;
}

void EntityManager::drawAll() const{
    for (const auto& e : entities) {
        e -> draw();
    }
}