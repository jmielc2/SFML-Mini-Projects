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

    // Functions
    bool hasStart() const;
    bool hasEnd() const;
    void findPath();
    void resetGrid();

    // Getters & Setters
    GridController::Phase getPhase() const;
    E* getStartNode() const;
    E* getEndNode() const;
    void setStartNode(E* node);
    void setEndNode(E* node);

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
        if (node->getType() != Node::Type::PATH) {
            node->reset();
        }
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
    this->grid.setController(this);
    this->start = nullptr;
    this->end = nullptr;
    this->phase = GridController::Phase::SETUP;
}

template <typename E> void GridController<E>::resetGrid() {
    this->grid.reset();
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
    if (this->hasStart() && this->hasEnd()) {
        this->setPhase(GridController::Phase::SORTING);
        std::vector<E*> path = SP_Algorithm::shortestPath<E>(this->getStartNode(), this->getEndNode(), this->grid.getNodes());
        for (long long unsigned int i = 1; i < path.size() - 1; i++) {
            path[i]->update(Node::Type::PATH);
        }
        this->setPhase(GridController::Phase::DONE);
    }

}

template<typename E> typename GridController<E>::Phase GridController<E>::getPhase() const {
    return this->phase;
}

template<typename E> void GridController<E>::drawGrid(sf::RenderWindow* window) {
    this->grid.draw(window);
}

template<typename E> E* GridController<E>::getStartNode() const {
    return this->start;
}

template<typename E> E* GridController<E>::getEndNode() const {
    return this->end;
}

template<typename E> void GridController<E>::setStartNode(E* start) {
    this->start = start;
}

template<typename E> void GridController<E>::setEndNode(E* end) {
    this->end = end;
}

template<typename E> void GridController<E>::setPhase(GridController<E>::Phase phase) {
    this->phase = phase;
}

#endif