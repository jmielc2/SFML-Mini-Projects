#pragma once

#ifndef BLOCK_HPP
#define BLOCK_HPP 1

#include "../stdafx.hpp"
#include "Node.hpp"
#include "../Controllers/GridController.hpp"

class Block : public Node {
public:
    // General
    Block(int id);

    // Getters & Setters
    void setController(GridController<Block>* controller);
    GridController<Block>* getController() const;

    // Functions
    void draw(sf::RenderWindow *window);
    void reset();
    void update(Node::Type type);
    void mouseUpdate(sf::Vector2i &pos, MouseState state);

    // Deleted Functions
    Block operator=(const Block& other) = delete;
    Block(const Block& other) = delete;
private:
    Node::Type type;
    sf::RectangleShape sprite;
    GridController<Block>* controller;
};

#endif