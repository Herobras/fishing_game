// game.cpp
#include "raylib.h"

#include <string>

#include "Constants.hpp"
#include "game/game.hpp"
#include "entity/Player.hpp"

#include "utils/BackgroundDraw.hpp"
#include "utils/Random.hpp"

//Inicializador del juego
Game::Game(int target_fps) {

    //Configuracion de visualizacion
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "MyGame");
    SetTargetFPS(target_fps);

    //Configuracion de jugador
    const int player_w = SCREEN_WIDTH/10;
    const int player_h = SCREEN_HEIGHT/10;

    const float player_speed = 500.0f;

    Color player_col = GREEN;

    float player_posX = SCREEN_WIDTH / 2 - player_w / 2;
    float player_posY = SCREEN_HEIGHT / 2 - player_h / 2;

    //Creacion del jugador

    entityManager.add(
        std::make_unique<Player>(player_posX, player_posY, player_w, player_h, player_col, player_speed)
    );
}


//Destructor, por ahora solo cierra ventana
Game::~Game() {
    CloseWindow();
}

void Game::run(){
    while (!WindowShouldClose()){
        deltaTime = GetFrameTime();
        update();
        draw();
    }
}

void Game::update() {
    entityManager.updateAll(deltaTime);
    handleCollisions();
    txt_contador = "Contador = " + std::to_string(contador);
    entityManager.removeMarked();
    if (enemySpawnTimer >= enemySpawnInterval) {
        spawnEnemy();              // función que instancia y agrega el enemigo
        enemySpawnTimer = 0.0f;    // reinicio del temporizador
    }
}

void Game::handleCollisions(){
    auto& entities = entityManager.getEntities();
    Entity* player = entityManager.getPlayer();
    if(!player) return;

    Rectangle playerBox = player -> getBoundingBox();

    for (const auto& e : entities){
        // es enemigo y está colisionando
        if (e-> get_type() == EntityType::ENEMY &&
        CheckCollisionRecs(playerBox, e->getBoundingBox())){
            contador++;
            e-> markForDeletion();
            //demas
        }
    }
}

void Game::draw(){
    BeginDrawing();
        backgroundDraw(BKG_COLOR, txt_contador.c_str(), 2, 0, 20, BLACK);
        entityManager.drawAll();
    EndDrawing();
}

void Game::spawnEnemy(){
    int w = SCREEN_WIDTH/20;
    int h = SCREEN_HEIGHT/20;
    float x = random_int(0,SCREEN_WIDTH - w);
    float y = random_int(0,SCREEN_HEIGHT - h);
    Color col = RED;
    float speed = 200.0f;

    entityManager.add(std::make_unique<Enemy>(x, y, w, h, col, speed));
}