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
        bool check;
        entry(int dir, int x, int y, bool check) {
            this->dir = dir;
            this->x = x;
            this->y = y;
            this->check = check;
        }
    };
    static std::map<int, sf::Vector2i> directions;
    template <typename E> static bool isWall(const Grid<E> &grid, MG_Algorithm::entry &node, int i);
    template <typename E> static bool canClearWall(const Grid<E> &grid, MG_Algorithm::entry &node);
};

//////////////////////////////////////////////

// Uses a variation of DFS algorithm to create the maze.
template <typename E> void MG_Algorithm::generateMaze(const Grid<E> &grid) {
    for (E* node : grid.getNodes()) {
        node->update(Node::Type::WALL);
    }
    int x = 0, y = 0;
    int dir = rand() % 4;
    std::stack<entry> record;
    std::set<E*> explored;

    record.push(MG_Algorithm::entry(dir, x, y, true));
    while (!record.empty()) {
        entry node = record.top();
        record.pop();
        E* ref = grid.getNode(node.x, node.y);
        if (explored.count(ref) || !canClearWall(grid, node)) {
            continue;
        }
        ref->update(Node::Type::NONE);
        explored.insert(ref);
        if (node.check) {
            if (rand() % 100 >= 35) {
                node.dir = rand() % 4;
            }

            for (int i = 0; i < 4; i++) {
                if (i == node.dir) {
                    continue;
                }
                x = node.x + directions[i].x;
                y = node.y + directions[i].y;
                if (grid.isValidNode(x, y)) {
                    record.push(MG_Algorithm::entry(i, x, y, !node.check));
                }
            }
        }
        x = node.x + directions[node.dir].x;
        y = node.y + directions[node.dir].y;
        if (grid.isValidNode(x, y)) {
            record.push(MG_Algorithm::entry(node.dir, x, y, !node.check));
        }
    }
}

template <typename E> bool MG_Algorithm::isWall(const Grid<E> &grid, MG_Algorithm::entry &node, int i) {
    int x = node.x + MG_Algorithm::directions[i].x;
    int y = node.y + MG_Algorithm::directions[i].y;
    return (!grid.isValidNode(x, y) || grid.getNode(x, y)->getType() == Node::Type::WALL);
}

template <typename E> bool MG_Algorithm::canClearWall(const Grid<E> &grid, MG_Algorithm::entry &node) {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        count += (isWall(grid, node, i))? 1 : 0;
    }
    return count >= 3;
}

#endif