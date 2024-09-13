#include "utils.h"

std::random_device rd;
std::mt19937 gen(rd());

int getRandomInt(int max) {
    std::uniform_int_distribution<int> distrib(0, max);
    return distrib(gen);
}

int getRandomInt(int min, int max) {
    std::uniform_int_distribution<int> distrib(min, max);
    return distrib(gen);
}