#include "SetGraph.h"

SetGraph::SetGraph(int vertices) : adjacency_sets(vertices) {}

// конструктор копирования 
SetGraph::SetGraph(const IGraph& other) {
    int vertices = other.VerticesCount();
    adjacency_sets.resize(vertices);
    
    for (int i = 0; i < vertices; ++i) {
        auto neighbors = other.GetNextVertices(i);
        adjacency_sets[i].insert(neighbors.begin(), neighbors.end());
    }
}

void SetGraph::AddEdge(int from, int to) {
    if (from < 0 || static_cast<size_t>(from) >= adjacency_sets.size() || 
        to < 0 || static_cast<size_t>(to) >= adjacency_sets.size()) {
        throw std::out_of_range("неправильный номер вершины");
    }
    adjacency_sets[from].insert(to);
}
    
int SetGraph::VerticesCount() const {
    return static_cast<int>(adjacency_sets.size());
}
    
std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    if (vertex < 0 || static_cast<size_t>(vertex) >= adjacency_sets.size()) {
        throw std::out_of_range("неправильный номер вершины");
    }
    
    const auto& neighbors_set = adjacency_sets[vertex];
    return std::vector<int>(neighbors_set.begin(), neighbors_set.end());
}

int main() {
    SetGraph graph(5);

    graph.AddEdge(0, 1);
    graph.AddEdge(0, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(2, 4);

    for (int i = 0; i < graph.VerticesCount(); ++i) {
        auto neighbors = graph.GetNextVertices(i);
        std::cout << "вершина " << i << " => ";
        for (int v : neighbors) {
            std::cout << v << " ";
        }
        std::cout << "\n";
    }
    
    SetGraph graph2(graph);
    std::cout << "\nкопия графа создана\n";
    std::cout << "вершин в копии: " << graph2.VerticesCount() << "\n";

    return 0;
}