#include <iostream>
#include <memory>
#include <functional>

class Enemy {
public:
    Enemy(int hp) : health(hp) {}

    void takeDamage(int dmg) {
        health -= dmg;
        std::cout << "Daño recibido: " << dmg << ", vida restante: " << health << "\n";
        if (health <= 0 && onDeath) {
            onDeath(); // llamamos al callback
        }
    }

    std::function<void()> onDeath;

private:
    int health;
};

int main() {
    // creamos el enemigo como unique_ptr
    auto enemy = std::make_unique<Enemy>(100);

    // definimos qué pasa cuando muere
    /*
    enemy->onDeath = []() {
        std::cout << "¡Enemigo destruido!\n";
    };
    */
    int puntaje = 0;

    enemy->onDeath = [&puntaje]() {
        puntaje += 100;
        std::cout << "¡+100 puntos!\n";
    };

    // lo atacamos
    enemy->takeDamage(30);  // vida: 70
    enemy->takeDamage(50);  // vida: 20
    enemy->takeDamage(20);  // vida: 0 → ¡Enemigo destruido!

    return 0;
}
