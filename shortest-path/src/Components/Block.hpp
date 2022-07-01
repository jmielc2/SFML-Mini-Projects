#pragma once

#ifndef BLOCK_HPP
#define BLOCK_HPP 1

#include "../stdafx.hpp"
#include "Node.hpp"

class Block : public Node {
public:
    // General
    Block(int id);

    // Functions
    void draw(sf::RenderWindow *window);
    void reset();
    void update(Node::Type type);
    void mouseUpdate(MouseState state);

    // Deleted Functions
    Block operator=(const Block& other) = delete;
    Block(const Block& other) = delete;
private:
    Node::Type type;
    sf::RectangleShape sprite;
};

#endif