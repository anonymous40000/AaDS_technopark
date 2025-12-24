#pragma once
#include <vector>
#include "PrimMST.h"
#include "DistanceMatrix.h"

class TSPApproxMST {
public:
    struct Result {
        std::vector<int> tour;
        double length;
    };

    Result solve(const DistanceMatrix& dm);
};
