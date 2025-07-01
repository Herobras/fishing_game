#include "Random.hpp"
#include <random>

Direction random_dir() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dist(0,8);
    return static_cast<Direction>(dist(gen));
}

int random_int(int range) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, range);
    return dist(gen);
}
