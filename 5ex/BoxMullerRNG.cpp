#include "BoxMullerRNG.h"
#include <cmath>

BoxMullerRNG::BoxMullerRNG(unsigned long long seed)
    : rng_(seed), uni_(0.0, 1.0), has_spare_(false), spare_(0.0) {}

double BoxMullerRNG::normal01() {
    if (has_spare_) {
        has_spare_ = false;
        return spare_;
    }

    double u1 = 0.0;
    while (u1 <= 1e-12) u1 = uni_(rng_);
    double u2 = uni_(rng_);

    double r = std::sqrt(-2.0 * std::log(u1));
    double theta = 2.0 * std::acos(-1.0) * u2;

    double z0 = r * std::cos(theta);
    double z1 = r * std::sin(theta);

    spare_ = z1;
    has_spare_ = true;
    return z0;
}

Point BoxMullerRNG::normalPoint() {
    return Point(normal01(), normal01());
}
