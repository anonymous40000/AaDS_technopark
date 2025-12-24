#pragma once
#include <vector>
#include <stdexcept>
#include <iostream>

struct IGraph {
    virtual ~IGraph() {}
    
    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
};

// деструктор есть в базовом классе а в том используем вектор поэтому не будем писать 
struct MatrixGraph : public IGraph {
private:
    std::vector<std::vector<int>> adjacency_matrix;
    
public:
    explicit MatrixGraph(int vertices);
    explicit MatrixGraph(const IGraph& other);
    
    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    std::vector<int> GetNextVertices(int vertex) const override;
    int GetEdge(int from, int to) const;
};
