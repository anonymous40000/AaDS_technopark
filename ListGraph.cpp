#include "ListGraph.h"

ListGraph::ListGraph(int verticles) : adjacency_list(verticles) {}

ListGraph::ListGraph(const IGraph& other) { // конструктор копирования
    int verticles = other.VerticesCount();
    adjacency_list.resize(verticles);

    for (int i = 0; i < verticles; ++i) {
        adjacency_list[i] = other.GetNextVertices(i);
    }
}

void ListGraph::AddEdge(int from, int to) {
    if (from < 0 || static_cast<size_t>(from) >= adjacency_list.size() || to < 0 || static_cast<size_t>(to) >= adjacency_list.size()) {
        throw std::out_of_range("неправильный номер вершины");
    }

    adjacency_list[from].push_back(to);
}

int ListGraph::VerticesCount() const {
    return static_cast<size_t>(adjacency_list.size());
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    if (vertex < 0 || static_cast<size_t>(vertex) >= adjacency_list.size()) {
        throw std::out_of_range("неправильный номер вершины");
    }
    return adjacency_list[vertex];
}


int main() {
    int vertexCount = 10;
    
    ListGraph mygraph(vertexCount);
    
    for (int i = 0; i < mygraph.VerticesCount(); ++i) {
        int to = (i + 1) % vertexCount;
        mygraph.AddEdge(i, to);
        mygraph.AddEdge(i, (i + 2) % vertexCount);
    }
    
    std::cout << "в графе " << mygraph.VerticesCount() << " вершин" << "\n";
    
    std::vector<int> neighbors = mygraph.GetNextVertices(0);
    std::cout << "с вершиной 0 связаны следующие вершины: ";
    for (int v : neighbors) {
        std::cout << v << " ";
    }

    std::cout << "\n";
    
    for (int i = 0; i < mygraph.VerticesCount(); ++i) {
        std::cout << "вершины, смежные с вершиной " << i << ": ";
        
        std::vector<int> vertexNeighbors = mygraph.GetNextVertices(i);
        
        if (vertexNeighbors.empty()) {
            std::cout << "нет смежных вершин";
        } else {
            for (size_t j = 0; j < vertexNeighbors.size(); ++j) {
                std::cout << vertexNeighbors[j];
                if (j < vertexNeighbors.size() - 1) {
                    std::cout << ", ";
                }
            }
        }
        std::cout << std::endl;
    }   

    ListGraph mygraph2(mygraph);
    std::cout << "\nкопия графа создана\n";
    std::cout << "вершин в копии: " << mygraph2.VerticesCount() << "\n";

    return 0;
}