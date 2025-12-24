#include "TSPExactBruteForce.h"
#include <vector>
#include <algorithm>
#include <limits>

double TSPExactBruteForce::solve(const DistanceMatrix& dm) {
    int n = dm.n();
    if (n <= 1) return 0.0;

    std::vector<int> p;
    p.reserve(n - 1);
    for (int i = 1; i < n; i++) p.push_back(i);

    double best = std::numeric_limits<double>::infinity();

    do {
        double len = 0.0;
        int prev = 0;
        for (int v : p) {
            len += dm.get(prev, v);
            prev = v;
        }
        len += dm.get(prev, 0);
        if (len < best) best = len;
    } while (std::next_permutation(p.begin(), p.end()));

    return best;
}
