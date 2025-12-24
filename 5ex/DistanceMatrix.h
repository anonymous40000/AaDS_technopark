#pragma once
#include <vector>
#include "Point.h"

class DistanceMatrix {
private:
    int n_;
    std::vector<double> d_;
public:
    explicit DistanceMatrix(const std::vector<Point>& pts);

    int n() const;
    double get(int i, int j) const;
};
