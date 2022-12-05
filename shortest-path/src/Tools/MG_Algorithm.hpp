#pragma once

#ifndef MG_ALGORITHM
#define MG_ALGORITHM 1

#include "../stdafx.hpp"
#include "../Components/Grid.hpp"
#include "../Components/Node.hpp"


class MG_Algorithm {
public:
    static void init();
    template <typename E> static void generateMaze(const Grid<E> &grid);

private:
    struct entry {
        int dir, x, y;

        entry(int dir, int x, int y) {
            this->dir = dir;
            this->x = x;
            this->y = y;
        }
    };
    static std::map<int, sf::Vector2i> directions;
    template <typename E> static bool canAddEntry(const Grid<E> &grid, int x, int y);
};

//////////////////////////////////////////////

template <typename E> void MG_Algorithm::generateMaze(const Grid<E> &grid) {
    for (E* node : grid.getNodes()) {
        node->update(Node::Type::WALL);
    }
    int x = rand() % DIM_X;
    int y = rand() % DIM_Y;
    int dir = rand() % 4;
    std::stack<entry> record;
    std::set<E*> explored;

    LOG("Generating maze...");
    LOG("Starting At: " << x << ", " << y);
    record.push(MG_Algorithm::entry(dir, x, y));
    while (!record.empty()) {
        entry top = record.top();
        record.pop();
        E* node = grid.getNode(top.x, top.y);
        if (explored.count(node)) {
            continue;
        }
        node->update(Node::Type::NONE);
        explored.insert(node);
        LOG("Cleared : " << top.x << ", " << top.y);
        for (int i = 0; i < 4; i++) {
            if (i == top.dir) {
                continue;
            }
            x = top.x + directions[dir].x;
            y = top.y + directions[dir].y;
            if (grid.isValidNode(x, y) && !explored.count(grid.getNode(x, y)) && canAddEntry(grid, x, y)) {
                record.push(MG_Algorithm::entry(i, x, y));
            }
        }
        x = top.x + directions[top.dir].x;
        y = top.y + directions[top.dir].y;
        if (grid.isValidNode(x, y) && !explored.count(grid.getNode(x, y)) && canAddEntry(grid, x, y)) {
            record.push(MG_Algorithm::entry(top.dir, x, y));
        }
    }
}

template <typename E> bool MG_Algorithm::canAddEntry(const Grid<E> &grid, int x, int y) {
    return false;
}
#endif