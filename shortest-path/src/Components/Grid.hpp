#pragma once

#ifndef BLOCK_GRID_HPP
#define BLOCK_GRID_HPP 1

#include "../stdafx.hpp"

template <typename E>
class Grid {
public:
    Grid();
    ~Grid();

    // Getters & Setters
    std::vector<E*> getNodes();
    E* getNode(int x, int y);

    // Functions
    void draw(sf::RenderWindow* window);
    
    // Deleted Functions
    Grid operator=(const Grid& other) = delete;
    Grid(const Grid& other) = delete;
private:
    std::vector<E*> nodes;
};

////////////////////////////////////

template <typename E> Grid<E>::Grid() {
    for (int i = 0; i < DIM_X * DIM_Y; i++) {
        this->nodes.push_back(new E(i));
    }
}

template <typename E> Grid<E>::~Grid() {
    for (E* node : this->nodes) {
        delete node;
    }
    return;
}

template <typename E> void Grid<E>::draw(sf::RenderWindow *window) {
    for (E* node : this->nodes) {
        node->draw(window);
    }
}

template <typename E> std::vector<E*> Grid<E>::getNodes() {
    return this->nodes;
}

template <typename E> E* Grid<E>::getNode(int x, int y) {
    return this->nodes.at(y * DIM_X + x);
}

#endif