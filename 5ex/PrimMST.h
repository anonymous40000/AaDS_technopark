#pragma once
#include <vector>
#include "DistanceMatrix.h"

class PrimMST {
private:
    std::vector<int> parent_;
    double total_;
public:
    PrimMST();

    std::vector<std::vector<int>> build(const DistanceMatrix& dm, int root = 0);

    const std::vector<int>& parent() const;
    double totalWeight() const;
};
