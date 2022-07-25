#pragma once

#ifndef SP_ALGORITHM_HPP
#define SP_ALGORITHM_HPP

#include "../stdafx.hpp"
#include "../Components/Node.hpp"

class SP_Algorithm {
public:
    template <typename E> static std::vector<E*> shortestPath(E* start, E* end, const std::vector<E*> &grid);

private:
    template <typename E> static std::vector<E*> getNodeNeighbors(const E* cur, const std::vector<E*> &grid);
};


////////////////////////////////////////////////////////////

template <typename E> std::vector<E*> SP_Algorithm::shortestPath(E* start, E* end, const std::vector<E*> &grid) {
    std::priority_queue<E*, std::vector<E*>, Node::NodeComparator<E>> unvisited;
    std::vector<E*> path;
    
    for (E* node : grid) {
        if (node->getType() == Node::Type::WALL) {
            continue;
        } else if (node == start) {
            node->setDistance(0);
        } else {
            node->setDistance(INT_MAX);
        }
        node->setParent(nullptr);
        unvisited.emplace(node);
    }

    while (!unvisited.empty()) {
        E* cur = unvisited.top();
        unvisited.pop();
        if (cur->getID() == end->getID()) {
            break;
        }

        std::vector<E*> neighbors = SP_Algorithm::getNodeNeighbors(cur, grid);
        for (E* neighbor : neighbors) {
            int altDistance = 1 + cur->getDistance();
            if (altDistance < neighbor->getDistance() && cur->getDistance() != INT_MAX) {
                neighbor->setDistance(altDistance);
                neighbor->setParent(cur);
                unvisited.emplace(neighbor);
            }
        }
    }
    
    E *cur = end, *prev;
    do {
        prev = cur;
        path.push_back(cur);
        cur = dynamic_cast<E*>(cur->getParent());
    } while (prev->getParent() != nullptr && prev != start);

    return path;
}

template <typename E> std::vector<E*> SP_Algorithm::getNodeNeighbors(const E* cur, const std::vector<E*> &grid) {
    std::vector<E*> neighbors;
    int index = cur->getID();
    if (index % DIM_X != 0 && grid.at(index - 1)->getType() != Node::Type::WALL) {
        neighbors.push_back(grid.at(index - 1));
    }
    if (index % DIM_X != DIM_X - 1 && grid.at(index + 1)->getType() != Node::Type::WALL) {
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

#endif