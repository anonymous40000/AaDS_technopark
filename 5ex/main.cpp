#include <iostream>
#include <string>
#include <chrono>
#include "ExperimentRunner.h"

int main(int argc, char** argv) {
    int n_min = 2;
    int n_max = 10;
    int trials = 50;
    unsigned long long seed = (unsigned long long)std::chrono::high_resolution_clock::now().time_since_epoch().count();

    if (argc >= 2) n_min = std::stoi(argv[1]);
    if (argc >= 3) n_max = std::stoi(argv[2]);
    if (argc >= 4) trials = std::stoi(argv[3]);
    if (argc >= 5) seed = (unsigned long long)std::stoull(argv[4]);

    ExperimentRunner runner(n_min, n_max, trials, seed);
    runner.run();
    return 0;
}
