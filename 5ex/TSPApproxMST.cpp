#include "TSPApproxMST.h"
#include <vector>

TSPApproxMST::Result TSPApproxMST::solve(const DistanceMatrix& dm) {
    int n = dm.n();
    PrimMST mst;
    auto tree = mst.build(dm, 0);

    std::vector<int> order;
    order.reserve(n);
    std::vector<char> vis(n, 0);

    std::vector<std::pair<int,int>> st;
    st.reserve(n);
    st.push_back({0, -1});

    while (!st.empty()) {
        auto cur = st.back();
        st.pop_back();
        int v = cur.first;
        int p = cur.second;
        if (vis[v]) continue;
        vis[v] = 1;
        order.push_back(v);

        auto& adj = tree[v];
        for (int i = (int)adj.size() - 1; i >= 0; i--) {
            int to = adj[i];
            if (to == p) continue;
            st.push_back({to, v});
        }
    }

    double len = 0.0;
    for (int i = 0; i + 1 < n; i++) len += dm.get(order[i], order[i + 1]);
    len += dm.get(order.back(), order.front());

    return {order, len};
}
