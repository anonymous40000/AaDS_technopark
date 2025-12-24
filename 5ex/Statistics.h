#pragma once
#include <vector>

class Statistics {
public:
    static double mean(const std::vector<double>& a);
    static double stddev(const std::vector<double>& a);
    static double minv(const std::vector<double>& a);
    static double maxv(const std::vector<double>& a);
    static double median(std::vector<double> a);
    static double quantile(std::vector<double> a, double q);
};
