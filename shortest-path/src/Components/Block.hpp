#pragma once

#ifndef BLOCK_HPP
#define BLOCK_HPP 1

#include "../stdafx.hpp"
// #include "Node.hpp"

class Block : public Node {
public:
    // General
    enum Type {START, END, NONE, PATH, WALL};
    Block(int id);

    // Getters & Setters
    Block::Type getType() const;
    void setType(Block::Type type);

    // Functions
    void draw(sf::RenderWindow *window);
    void reset();
    void mouseUpdate(MouseState state);

    // Deleted Functions
    Block operator=(const Block& other) = delete;
    Block(const Block& other) = delete;
private:
    Block::Type type;
    sf::RectangleShape sprite;
};

#endif