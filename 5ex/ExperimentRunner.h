#pragma once
#include <vector>
#include "BoxMullerRNG.h"

class ExperimentRunner {
private:
    int n_min_;
    int n_max_;
    int trials_;
    unsigned long long seed_;
public:
    ExperimentRunner(int n_min, int n_max, int trials, unsigned long long seed);

    void run();
};
