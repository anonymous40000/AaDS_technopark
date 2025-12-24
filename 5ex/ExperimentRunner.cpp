#include "ExperimentRunner.h"
#include "DistanceMatrix.h"
#include "TSPApproxMST.h"
#include "TSPExactBruteForce.h"
#include "Statistics.h"
#include <iostream>
#include <iomanip>
#include <cmath>

ExperimentRunner::ExperimentRunner(int n_min, int n_max, int trials, unsigned long long seed)
    : n_min_(n_min), n_max_(n_max), trials_(trials), seed_(seed) {}

void ExperimentRunner::run() {
    std::cout.setf(std::ios::fixed);
    std::cout << std::setprecision(6);

    std::cout << "эксперимент: метрическая неориентированная задача коммивояжера (TSP)\n";
    std::cout << "метод: 2-аппроксимация через минимальное остовное дерево (алгоритм Прима) + обход DFS (preorder)\n";
    std::cout << "точки: N(0,1) на плоскости, генерация Бокса–Мюллера\n";
    std::cout << "качество: q = L_approx / L_opt (L_opt ищется перебором, подходит для N<=10)\n";
    std::cout << "параметры: N in [" << n_min_ << "," << n_max_ << "], trials=" << trials_ << ", seed=" << seed_ << "\n\n";

    std::cout
        << "N  "
        << "mean_q  sd_q  min_q  q25  median  q75  max_q  "
        << "CI95_low  CI95_high  "
        << "mean_Lapprox  mean_Lopt\n";

    BoxMullerRNG rng(seed_);
    TSPApproxMST approxSolver;
    TSPExactBruteForce exactSolver;

    for (int n = n_min_; n <= n_max_; n++) {
        std::vector<double> q;
        std::vector<double> aL;
        std::vector<double> oL;

        q.reserve(trials_);
        aL.reserve(trials_);
        oL.reserve(trials_);

        for (int t = 0; t < trials_; t++) {
            std::vector<Point> pts;
            pts.reserve(n);
            for (int i = 0; i < n; i++) pts.push_back(rng.normalPoint());

            DistanceMatrix dm(pts);

            double approxLen = approxSolver.solve(dm).length;
            double optLen = exactSolver.solve(dm);

            aL.push_back(approxLen);
            oL.push_back(optLen);
            q.push_back(approxLen / optLen);
        }

        double mean_q = Statistics::mean(q);
        double sd_q = Statistics::stddev(q);
        double min_q = Statistics::minv(q);
        double max_q = Statistics::maxv(q);
        double q25 = Statistics::quantile(q, 0.25);
        double med = Statistics::median(q);
        double q75 = Statistics::quantile(q, 0.75);

        double se = (trials_ > 0) ? (sd_q / std::sqrt((double)trials_)) : 0.0;
        double ci_low = mean_q - 1.96 * se;
        double ci_high = mean_q + 1.96 * se;

        double mean_aL = Statistics::mean(aL);
        double mean_oL = Statistics::mean(oL);

        std::cout
            << n << "  "
            << mean_q << "  " << sd_q << "  "
            << min_q << "  " << q25 << "  " << med << "  " << q75 << "  " << max_q << "  "
            << ci_low << "  " << ci_high << "  "
            << mean_aL << "  " << mean_oL << "\n";
    }

    std::cout << "\nпояснение столбцов:\n";
    std::cout << "mean_q/sd_q/min_q/max_q — среднее/СКО/минимум/максимум качества q.\n";
    std::cout << "q25/median/q75 — квартили качества (25%, 50%, 75%).\n";
    std::cout << "CI95_low..CI95_high — 95% доверительный интервал для mean_q (нормальная аппроксимация).\n";
    std::cout << "mean_Lapprox/mean_Lopt — средние длины приближённого и оптимального туров.\n";
}
