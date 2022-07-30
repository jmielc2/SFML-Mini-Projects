#pragma once

#ifndef GRID_CONTROLLER_HPP
#define GRID_CONTROLLER_HPP 1

#include "../stdafx.hpp"
#include "../Components/Grid.hpp"
#include "../Tools/SP_Algorithm.hpp"

template <typename E>
class GridController {
public:
    enum Phase {SETUP, SOLVING, DONE};
    
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
    E* resetNode;

    void setPhase(GridController::Phase phase);
};

//////////////////////////////////////////////

template<typename E> void GridController<E>::mouseUpdate(sf::Vector2i &pos, MouseState state) {
    if (this->resetNode && this->resetNode->getType() != Node::Type::PATH && this->resetNode->getType() != Node::Type::VISITED) {
        this->resetNode->reset();
    }
    
    int x = pos.x / (WINDOW_WIDTH / DIM_X);
    int y = pos.y / (WINDOW_HEIGHT / DIM_Y);
    E* curNode = this->grid.getNode(x, y);

    Node::Type curType = curNode->getType();
    if (getPhase() != Phase::SETUP) {
        state = MouseState::HOVER;
    }
    switch (state) {
        case(MouseState::RIGHT_HOLD):
            if (curType != Node::Type::START && curType != Node::Type::END) {
                curNode->update(Node::Type::WALL);
            }
            break;
        case(MouseState::LEFT_CLICK):
            if (curType == Node::Type::WALL) {
                break;
            } else if (hasStart()) {
                if (getStartNode() == curNode) {
                    curNode->update(Node::Type::NONE);
                    setStartNode(nullptr);
                } else if (hasEnd()) {
                    if (getEndNode() == curNode) {
                        curNode->update(Node::Type::NONE);
                        setEndNode(nullptr);
                    }
                } else {
                    curNode->update(Node::Type::END);
                    setEndNode(curNode);
                }
            } else if (curType != Node::Type::END) {
                curNode->update(Node::Type::START);
                setStartNode(curNode);
            } else {
                curNode->update(Node::Type::NONE);
                setEndNode(nullptr);
	     }
            break;
        case(MouseState::RIGHT_CLICK):
            if (curType != Node::Type::START && curType != Node::Type::END) {
                curNode->update(Node::Type::WALL);
            }
            break;
        default:
            if (curType == Node::Type::NONE) {
                curNode->update(Node::Type::NONE);
            }
            break;
    }

    if (curNode->getType() == Node::Type::NONE) {
        this->resetNode = curNode;
    } else {
        this->resetNode = nullptr;
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
    this->setStartNode(nullptr);
    this->setEndNode(nullptr);
    this->setPhase(GridController<E>::Phase::SETUP);
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
        this->setPhase(GridController::Phase::SOLVING);
        std::vector<E*> visited = SP_Algorithm::shortestPath<E>(this->getStartNode(), this->getEndNode(), this->grid.getNodes());
        for (int i = 1; i < (int) visited.size() - 1; i++) {
            visited[i]->update(Node::Type::VISITED);
        }
    
        E *cur = dynamic_cast<E*>(end->getParent());
        while (cur != nullptr && cur != start) {
            cur->update(Node::Type::PATH);
            cur = dynamic_cast<E*>(cur->getParent());
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