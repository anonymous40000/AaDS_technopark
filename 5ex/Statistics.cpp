#include "Statistics.h"
#include <cmath>
#include <algorithm>
#include <limits>

double Statistics::mean(const std::vector<double>& a) {
    if (a.empty()) return 0.0;
    double s = 0.0;
    for (double x : a) s += x;
    return s / (double)a.size();
}

double Statistics::stddev(const std::vector<double>& a) {
    int n = (int)a.size();
    if (n <= 1) return 0.0;
    double m = mean(a);
    double s2 = 0.0;
    for (double x : a) {
        double t = x - m;
        s2 += t * t;
    }
    return std::sqrt(s2 / (double)(n - 1));
}

double Statistics::minv(const std::vector<double>& a) {
    if (a.empty()) return 0.0;
    double mn = std::numeric_limits<double>::infinity();
    for (double x : a) mn = std::min(mn, x);
    return mn;
}

double Statistics::maxv(const std::vector<double>& a) {
    if (a.empty()) return 0.0;
    double mx = -std::numeric_limits<double>::infinity();
    for (double x : a) mx = std::max(mx, x);
    return mx;
}

double Statistics::quantile(std::vector<double> a, double q) {
    if (a.empty()) return 0.0;
    if (q <= 0.0) return *std::min_element(a.begin(), a.end());
    if (q >= 1.0) return *std::max_element(a.begin(), a.end());

    std::sort(a.begin(), a.end());
    double pos = q * (a.size() - 1);
    int i = (int)std::floor(pos);
    int j = (int)std::ceil(pos);
    if (i == j) return a[i];
    double t = pos - i;
    return a[i] * (1.0 - t) + a[j] * t;
}

double Statistics::median(std::vector<double> a) {
    return quantile(std::move(a), 0.5);
}
