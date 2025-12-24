#pragma once
#include <vector>
#include <unordered_set>
#include <stdexcept>
#include <iostream>

struct IGraph {
    virtual ~IGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
};

// буду делать хешсетом
// деструктор есть в базовом классе а в том используем вектор поэтому не будем писать 
struct SetGraph : public IGraph {
private:
    std::vector<std::unordered_set<int>> adjacency_sets;
    
public:
    explicit SetGraph(int vertices);
    explicit SetGraph(const IGraph& other);

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    std::vector<int> GetNextVertices(int vertex) const override;
};