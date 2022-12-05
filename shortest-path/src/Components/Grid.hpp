#pragma once

#ifndef BLOCK_GRID_HPP
#define BLOCK_GRID_HPP 1

#include "../stdafx.hpp"

template <typename E> class GridController;

template <typename E>
class Grid {
public:
    Grid();
    ~Grid();

    // Getters & Setters
    std::vector<E*> getNodes() const;
    E* getNode(int x, int y) const;
    bool isValidNode(int x, int y) const;
    void setController(GridController<E>* controller);
    GridController<E>* getController() const;

    // Functions
    void draw(sf::RenderWindow* window);
    void reset();
    
    // Deleted Functions
    Grid operator=(const Grid& other) = delete;
    Grid(const Grid& other) = delete;
private:
    std::vector<E*> nodes;
    GridController<E>* controller;
};

//////////////////////////////////////////

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

template <typename E> void Grid<E>::reset() {
    for (E* node : this->nodes) {
        node->reset();
    }
}

template <typename E> std::vector<E*> Grid<E>::getNodes() const {
    return this->nodes;
}

template <typename E> E* Grid<E>::getNode(int x, int y) const {
    return this->nodes.at(y * DIM_X + x);
}

template <typename E> bool Grid<E>::isValidNode(int x, int y) const {
    return  !(x < 0 || y < 0 || x >= DIM_X || y >= DIM_Y);
}

template <typename E> void Grid<E>::setController(GridController<E>* controller) {
    this->controller = controller;
    for (E* node : this->nodes) {
        node->setController(this->getController());
    }
}

template <typename E> GridController<E>* Grid<E>::getController() const {
    return this->controller;
}

#endif