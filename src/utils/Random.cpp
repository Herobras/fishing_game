#include "Random.hpp"
#include <random>

Direction random_dir() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dist(0,8);
    return static_cast<Direction>(dist(gen));
}

int random_int(int min_inclusive, int max_exclusive) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min_inclusive, max_exclusive - 1);
    return dist(gen);
}