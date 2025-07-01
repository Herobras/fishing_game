#pragma once

#include <vector>
#include <memory>
#include <string>

#include "game/EntityManager.hpp"
#include "entity/Enemy.hpp"
#include "entity/Player.hpp"

class Game {
public:
    Game(int target_fps);
    ~Game();

    // Funcion de ejecucion del juego
    void run();

private:
    EntityManager entityManager;

    float deltaTime;
    int contador;
    std::string txt_contador = "Contador = 0";

    float enemySpawnTimer = 0.0f;            // Acumulador de tiempo
    const float enemySpawnInterval = 1.5f;   // Intervalo en segundos (ej: cada 1.5 segundos)


    // Actualizacion de todas las entidades
    void update();
    //Dibujo en pantalla
    void draw();
    // Colisiones jugador - entidades
    void handleCollisions();
    // Generador de enemigos
    void spawnEnemy();
};
