#pragma once

#ifndef SP_ALGORITHM_HPP
#define SP_ALGORITHM_HPP

#include "../stdafx.hpp"
#include "../Components/Node.hpp"

class SP_Algorithm {
public:
    static std::vector<Node*> shortestPath(Node* start, Node* end, const std::vector<Node*> &grid);
private:
    static void init(Node* start, const std::vector<Node*> &grid);
    static void clean();
    static std::vector<Node*> getNodeNeighbors(const Node* cur, const std::vector<Node*> &grid);
    static std::priority_queue<Node*, std::vector<Node*>, Node::NodeComparator> unvisited;
};

#endif