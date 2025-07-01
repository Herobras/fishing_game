#include "raylib.h"

#include <vector>
#include <memory>
#include <chrono>
#include <string>

#include "entity/Player.hpp"
#include "entity/Enemy.hpp"
#include "utils/Random.hpp"
#include "utils/BackgroundDraw.hpp"
#include "Constants.hpp"

using namespace std;
using namespace std::chrono;

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Ventana ejemplo");
    SetTargetFPS(60);

    Color bkg_color = { 0, 255, 244, 255 };

    // Tamaño del jugador
    const int player_width = SCREEN_WIDTH / 10;
    const int player_height = SCREEN_HEIGHT / 10;
    const float player_speed = 500.0f;
    Color player_col = GREEN;

    float player_posX = SCREEN_WIDTH / 2 - player_width / 2;
    float player_posY = SCREEN_HEIGHT / 2 - player_height / 2;

    vector<unique_ptr<Entity>> entities;

    // Jugador al centro
    entities.push_back(make_unique<Player>(
        player_posX, player_posY,
        player_width, player_height,
        player_col, player_speed
    ));

    // Primer enemigo inicial
    const int enemy_width = player_width / 2;
    const int enemy_height = player_height / 2;
    Color enemy_col = RED;

    entities.push_back(make_unique<Enemy>(
        random_int(SCREEN_WIDTH - enemy_width),
        random_int(SCREEN_HEIGHT - enemy_height),
        enemy_width, enemy_height,
        enemy_col, player_speed
    ));

    float deltaTime = 0.0f;
    int contador = 0;
    string texto_contador = "Contador = 0";

    auto now = system_clock::now();
    int inicio = duration_cast<milliseconds>(now.time_since_epoch()).count();
    int actual = inicio;
    const int delta_enemies = 1000; // en milisegundos

    while (!WindowShouldClose()) {
        deltaTime = GetFrameTime();

        // Actualizar entidades
        for (auto it = entities.begin(); it != entities.end();) {
            (*it)->update(deltaTime);

            if ((*it)->get_type() == EntityType::ENEMY) {
                if (CheckCollisionRecs(entities.at(0)->getBoundingBox(), (*it)->getBoundingBox())) {
                    it = entities.erase(it);
                    contador++;
                    texto_contador = "Contador = " + to_string(contador);
                    continue;
                }
            }

            ++it;
        }

        // Agregar enemigos periódicamente
        now = system_clock::now();
        actual = duration_cast<milliseconds>(now.time_since_epoch()).count();
        if (actual - inicio >= delta_enemies && entities.size() - 1 < MAX_ENEMIES) {
            inicio = actual;
            entities.push_back(make_unique<Enemy>(
                random_int(SCREEN_WIDTH - enemy_width),
                random_int(SCREEN_HEIGHT - enemy_height),
                enemy_width, enemy_height,
                enemy_col, player_speed
            ));
        }

        // Dibujado
        BeginDrawing();
            backgroundDraw(bkg_color, texto_contador.c_str(), 2, 0, 20, BLACK);
            for (auto& e : entities) {
                e->draw();
            }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
