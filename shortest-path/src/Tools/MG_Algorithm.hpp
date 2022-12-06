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
    template <typename E> static bool canClearWall(const Grid<E> &grid, MG_Algorithm::entry &node);
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

    record.push(MG_Algorithm::entry(dir, x, y));
    while (!record.empty()) {
        entry node = record.top();
        record.pop();
        E* ref = grid.getNode(node.x, node.y);
        if (explored.count(ref) || !canClearWall(grid, node)) {
            continue;
        }
        ref->update(Node::Type::NONE);
        explored.insert(ref);
        if (rand() % 100 >= 25) {
            node.dir = rand() % 4;
        }

        for (int i = 0; i < 4; i++) {
            if (i == node.dir) {
                continue;
            }
            x = node.x + directions[i].x;
            y = node.y + directions[i].y;
            if (grid.isValidNode(x, y)) {
                record.push(MG_Algorithm::entry(i, x, y));
            }
        }
        x = node.x + directions[node.dir].x;
        y = node.y + directions[node.dir].y;
        if (grid.isValidNode(x, y)) {
            record.push(MG_Algorithm::entry(node.dir, x, y));
        }
    }
}

template <typename E> bool MG_Algorithm::canClearWall(const Grid<E> &grid, MG_Algorithm::entry &node) {
    if (!grid.isValidNode(node.x, node.y)) {
        return true;
    }
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int tempX = node.x + MG_Algorithm::directions[i].x;
        int tempY = node.y + MG_Algorithm::directions[i].y;
        if (!grid.isValidNode(tempX, tempY) || grid.getNode(tempX, tempY)->getType() == Node::Type::WALL) {
            count++;
        }
    }
    return count >= 5;
}

#endif