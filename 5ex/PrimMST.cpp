#include "PrimMST.h"
#include <limits>

PrimMST::PrimMST() : total_(0.0) {}

std::vector<std::vector<int>> PrimMST::build(const DistanceMatrix& dm, int root) {
    int n = dm.n();
    parent_.assign(n, -1);
    total_ = 0.0;

    std::vector<double> minD(n, std::numeric_limits<double>::infinity());
    std::vector<char> used(n, 0);

    minD[root] = 0.0;

    for (int it = 0; it < n; it++) {
        int v = -1;
        for (int i = 0; i < n; i++) {
            if (!used[i] && (v == -1 || minD[i] < minD[v])) v = i;
        }
        used[v] = 1;
        if (parent_[v] != -1) total_ += dm.get(v, parent_[v]);

        for (int to = 0; to < n; to++) {
            if (used[to]) continue;
            double w = dm.get(v, to);
            if (w < minD[to]) {
                minD[to] = w;
                parent_[to] = v;
            }
        }
    }

    std::vector<std::vector<int>> tree(n);
    for (int v = 0; v < n; v++) {
        int p = parent_[v];
        if (p != -1) {
            tree[p].push_back(v);
            tree[v].push_back(p);
        }
    }
    return tree;
}

const std::vector<int>& PrimMST::parent() const { return parent_; }

double PrimMST::totalWeight() const { return total_; }
