#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int vertices) : adjacency_matrix(vertices, std::vector<int>(vertices, 0)) {}

// конструктор копирования 
MatrixGraph::MatrixGraph(const IGraph& other) {
    int vertices = other.VerticesCount();
    adjacency_matrix.resize(vertices, std::vector<int>(vertices, 0));
    
    for (int i = 0; i < vertices; ++i) {
        auto neighbors = other.GetNextVertices(i);
        for (int neighbor : neighbors) {
            adjacency_matrix[i][neighbor] = 1;
        }
    }
}

void MatrixGraph::AddEdge(int from, int to) {
    if (from < 0 || static_cast<size_t>(from) >= adjacency_matrix.size() || 
        to < 0 || static_cast<size_t>(to) >= adjacency_matrix.size()) {
        throw std::out_of_range("неправильный номер вершины");
    }
    
    adjacency_matrix[from][to] = 1;
}

int MatrixGraph::VerticesCount() const {
    return static_cast<int>(adjacency_matrix.size());
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    if (vertex < 0 || static_cast<size_t>(vertex) >= adjacency_matrix.size()) {
        throw std::out_of_range("неправильный номер вершины");
    }
    
    std::vector<int> result;
    const std::vector<int>& row = adjacency_matrix[vertex];
    
    for (size_t i = 0; i < row.size(); ++i) {
        if (row[i] == 1) {
            result.push_back(static_cast<int>(i));
        }
    }
    
    return result;
}

int main() {
    MatrixGraph graph(5);
    
    graph.AddEdge(0, 1);
    graph.AddEdge(0, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(2, 4);
    graph.AddEdge(3, 4);
    
    std::cout << "матричный граф создан\n";
    std::cout << "вершин: " << graph.VerticesCount() << "\n";
    
    int n = graph.VerticesCount();
    std::cout << "матрица смежности:\n";
        

    for (int i = 0; i < n; ++i) {
        auto neighbors = graph.GetNextVertices(i);
        
        for (int j = 0; j < n; ++j) {
            bool is_connected = false;
            for (int v : neighbors) {
                if (v == j) {
                    is_connected = true;
                    break;
                }
            }
            std::cout << (is_connected ? "1 " : "0 ");
        }
        std::cout << "\n";
    }
    
    MatrixGraph graph2(graph);
    std::cout << "\nкопия графа создана\n";
    std::cout << "вершин в копии: " << graph2.VerticesCount() << "\n";
    
    return 0;
}