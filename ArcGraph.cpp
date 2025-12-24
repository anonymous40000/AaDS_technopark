#include "ArcGraph.h"

ArcGraph::ArcGraph(int vertices) : vertices_count(vertices) {}

ArcGraph::ArcGraph(const IGraph& other) : vertices_count(other.VerticesCount()) {
    for (int i = 0; i < vertices_count; ++i) {
        auto neighbors = other.GetNextVertices(i);
        for (int neighbor : neighbors) {
            edges.emplace_back(i, neighbor);
        }
    }
}

void ArcGraph::AddEdge(int from, int to) {
    if (from < 0 || from >= vertices_count || 
        to < 0 || to >= vertices_count) {
        throw std::out_of_range("неправильный номер вершины");
    }
    edges.emplace_back(from, to);
}

int ArcGraph::VerticesCount() const {
    return vertices_count;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    if (vertex < 0 || vertex >= vertices_count) {
        throw std::out_of_range("неправильный номер вершины");
    }
    
    std::vector<int> result;
    for (const auto& edge : edges) {
        if (edge.first == vertex) {
            result.push_back(edge.second);
        }
    }
    
    // убираем дубликаты
    std::sort(result.begin(), result.end());
    result.erase(std::unique(result.begin(), result.end()), result.end());
    
    return result;
}

int main() {
    ArcGraph graph(5);

    graph.AddEdge(0, 1);
    graph.AddEdge(0, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(2, 4);
    graph.AddEdge(0, 1);

    for (int i = 0; i < graph.VerticesCount(); ++i) {
        auto neighbors = graph.GetNextVertices(i);
        std::cout << "вершина " << i << " => ";
        for (int v : neighbors) {
            std::cout << v << " ";
        }
        std::cout << "\n";
    }
    
    ArcGraph graph2(graph);
    std::cout << "\nкопия графа создана\n";
    std::cout << "вершин в копии: " << graph2.VerticesCount() << "\n";

    return 0;
}