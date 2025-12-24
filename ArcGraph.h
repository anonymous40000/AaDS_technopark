#pragma once
#include <vector>
#include <stdexcept>
#include <iostream>
#include <algorithm>

struct IGraph {
    virtual ~IGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
};


// деструктор есть в базовом классе а в том используем вектор поэтому не будем писать 
struct ArcGraph : public IGraph {
private:
    std::vector<std::pair<int, int>> edges;
    int vertices_count;   
    
public:
    explicit ArcGraph(int vertices);
    explicit ArcGraph(const IGraph& other);

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    std::vector<int> GetNextVertices(int vertex) const override;
};