#include "SP_Algorithm.hpp"

std::priority_queue<Node*, std::vector<Node*>, Node::NodeComparator> SP_Algorithm::unvisited;

std::vector<Node*> getNodeNeighbors(const Node* cur, const std::vector<Node*> &grid);

void SP_Algorithm::init(Node* start, const std::vector<Node*> &grid) {
    for (Node* node : grid) {
        node->setDistance(INT_MAX);
        if (node == start) {
            node->setDistance(0);
        }
        node->setParent(nullptr);
        unvisited.emplace(node);
    }
}

void SP_Algorithm::clean() {
    std::priority_queue<Node*, std::vector<Node*>, Node::NodeComparator> temp;
    SP_Algorithm::unvisited.swap(temp);
}

void SP_Algorithm::shortestPath(Node* start, Node* end, const std::vector<Node*> &grid) {
    SP_Algorithm::init(start, grid);

    while (!SP_Algorithm::unvisited.empty()) {
        Node* cur = SP_Algorithm::unvisited.top();
        LOG("CUR=" + std::to_string(cur->getID()));
        SP_Algorithm::unvisited.pop();
        if (cur->getID() == end->getID()) {
            break;
        }

        std::vector<Node*> neighbors = getNodeNeighbors(cur, grid);
        for (Node* neighbor : neighbors) {
            int altDistance = 1 + cur->getDistance();
            if (altDistance < neighbor->getDistance() && cur->getDistance() != INT_MAX) {
                neighbor->setDistance(altDistance);
                neighbor->setParent(cur);
                SP_Algorithm::unvisited.emplace(neighbor);
            }
        }
    }

    Node* cur = end, *prev;
    do {
        prev = cur;
        LOG(std::to_string(cur->getID()) + ": " + std::to_string(cur->getDistance()));
        cur = cur->getParent();
    } while (prev->getParent() != nullptr && prev != start);
    LOG("")

    SP_Algorithm::clean();
}

std::vector<Node*> getNodeNeighbors(const Node* cur, const std::vector<Node*> &grid) {
    std::vector<Node*> neighbors;
    int index = cur->getID();
    if (index != 0 && index % DIM_X != 0) {
        neighbors.push_back(grid.at(index - 1));
    }
    if (index != DIM_X * DIM_Y - 1 && index % DIM_X != DIM_X - 1) {
        neighbors.push_back(grid.at(index + 1));
    }
    if (index >= DIM_X) {
        neighbors.push_back(grid.at(index - DIM_X));
    }
    if (index < (DIM_Y - 1) * DIM_X) {
        neighbors.push_back(grid.at(index + DIM_X));
    }

    return neighbors;
}