#include "DistanceMatrix.h"

DistanceMatrix::DistanceMatrix(const std::vector<Point>& pts) : n_((int)pts.size()), d_(n_ * n_, 0.0) {
    for (int i = 0; i < n_; i++) {
        for (int j = i + 1; j < n_; j++) {
            double dist = pts[i].distTo(pts[j]);
            d_[i * n_ + j] = dist;
            d_[j * n_ + i] = dist;
        }
    }
}

int DistanceMatrix::n() const { return n_; }

double DistanceMatrix::get(int i, int j) const {
    return d_[i * n_ + j];
}
