#pragma once

#ifndef SP_ALGORITHM_HPP
#define SP_ALGORITHM_HPP

#include "../stdafx.hpp"
#include "../Components/Node.hpp"

class SP_Algorithm {
public:
    static void shortestPath(Node start, Node& end, const std::vector<Node> &grid);
private:
    void init();
    void clean();
    static std::priority_queue<Node, std::vector<Node>, Node> queue;
    static std::unordered_set<Node, Node::NodeHash> visited;
};

#endif