#pragma once
#include <random>
#include "Point.h"

class BoxMullerRNG {
private:
    std::mt19937_64 rng_;
    std::uniform_real_distribution<double> uni_;
    bool has_spare_;
    double spare_;
public:
    BoxMullerRNG(unsigned long long seed);

    double normal01();
    Point normalPoint();
};
