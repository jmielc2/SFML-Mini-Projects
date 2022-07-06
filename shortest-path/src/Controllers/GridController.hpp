#pragma once

#ifndef GRID_CONTROLLER_HPP
#define GRID_CONTROLLER_HPP 1

#include "../stdafx.hpp"
#include "../Components/Grid.hpp"
#include "../Tools/SP_Algorithm.hpp"

template <typename E>
class GridController {
public:
    enum Phase {SETUP, SORTING, DONE};
    
    GridController();
    ~GridController();

    bool hasStart() const;
    bool hasEnd() const;
    void findPath();
    GridController::Phase getPhase() const;

    void drawGrid(sf::RenderWindow* window);
    void mouseUpdate(sf::Vector2i &pos, MouseState state);

private:
    Grid<E> grid;
    E* start;
    E* end;
    GridController::Phase phase;
    std::vector<E*> resetNodes;

    void setPhase(GridController::Phase phase);
};

//////////////////////////////////////////////

template<typename E> void GridController<E>::mouseUpdate(sf::Vector2i &pos, MouseState state) {
    for (E* node : this->resetNodes) {
        node->reset();
    }
    this->resetNodes.clear();

    int x = pos.x / (WINDOW_WIDTH / DIM_X);
    int y = pos.y / (WINDOW_HEIGHT / DIM_Y);
    E* curNode = this->grid.getNode(x, y);
    curNode->mouseUpdate(pos, state);

    if (curNode->getType() == Node::Type::NONE) {
        this->resetNodes.push_back(curNode);
    }
}

template<typename E> GridController<E>::GridController() {
    this->start = nullptr;
    this->end = nullptr;
    this->phase = GridController::Phase::SETUP;
}

template<typename E> GridController<E>::~GridController() {
    return;
}

template<typename E> bool GridController<E>::hasStart() const {
    return start != nullptr;
}

template<typename E> bool GridController<E>::hasEnd() const {
    return end != nullptr;
}

template<typename E> void GridController<E>::findPath() {
    this->start = this->grid.getNode(0,0);
    this->end = this->grid.getNode(DIM_X - 1, DIM_Y - 1);
    std::vector<E*> path = SP_Algorithm::shortestPath<E>(this->start, this->end, this->grid.getNodes());
    for (E* node : path) {
        node->update(Node::Type::PATH);
    }
    this->start = nullptr;
    this->end = nullptr;
}

template<typename E> typename GridController<E>::Phase GridController<E>::getPhase() const {
    return this->phase;
}

template<typename E> void GridController<E>::drawGrid(sf::RenderWindow* window) {
    this->grid.draw(window);
}

#endif