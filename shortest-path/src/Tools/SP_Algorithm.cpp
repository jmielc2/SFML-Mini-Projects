#include "SP_Algorithm.hpp"

std::priority_queue<Node*, std::vector<Node*>, Node::NodeComparator> SP_Algorithm::unvisited;

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

std::vector<Node*> SP_Algorithm::shortestPath(Node* start, Node* end, const std::vector<Node*> &grid) {
        SP_Algorithm::init(start, grid);
        std::vector<Node*> path;

        while (!SP_Algorithm::unvisited.empty()) {
            Node* cur = SP_Algorithm::unvisited.top();
            SP_Algorithm::unvisited.pop();
            if (cur->getID() == end->getID()) {
                break;
            }

            std::vector<Node*> neighbors = SP_Algorithm::getNodeNeighbors(cur, grid);
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
            path.push_back(cur);
            cur = cur->getParent();
        } while (prev->getParent() != nullptr && prev != start);

        SP_Algorithm::clean();
        return path;
    }

std::vector<Node*> SP_Algorithm::getNodeNeighbors(const Node* cur, const std::vector<Node*> &grid) {
    std::vector<Node*> neighbors;
    int index = cur->getID();
    if (index != 0 && index % DIM_X != 0 && grid.at(index - 1)->getType() != Node::Type::WALL) {
        neighbors.push_back(grid.at(index - 1));
    }
    if (index != DIM_X * DIM_Y - 1 && index % DIM_X != DIM_X - 1 && grid.at(index + 1)->getType() != Node::Type::WALL) {
        neighbors.push_back(grid.at(index + 1));
    }
    if (index >= DIM_X && grid.at(index - DIM_X)->getType() != Node::Type::WALL) {
        neighbors.push_back(grid.at(index - DIM_X));
    }
    if (index < (DIM_Y - 1) * DIM_X && grid.at(index + DIM_X)->getType() != Node::Type::WALL) {
        neighbors.push_back(grid.at(index + DIM_X));
    }

    return neighbors;
}

