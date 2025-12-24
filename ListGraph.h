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


struct ListGraph : public IGraph {
private:
    std::vector<std::vector<int>> adjacency_list;
    
public:
    explicit ListGraph(int vertices);
    explicit ListGraph(const IGraph& other);
    
    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    std::vector<int> GetNextVertices(int vertex) const override;
};
