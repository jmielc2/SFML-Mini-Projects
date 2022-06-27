#pragma once

#ifndef BLOCK_HPP
#define BLOCK_HPP 1

#include "../stdafx.hpp"

class Block {
public:
    enum Type {START, END, NONE, PATH};
    Block(int id);

    // Getters & Setters
    int getID() const;
    int getDistance() const;
    void setDistance(int distance);
    Block::Type getType() const;
    void setType(Block::Type type);

    // Functions
    void draw(sf::RenderWindow *window);
    Block operator=(const Block& other) = delete;
private:
    int id;
    int distance;
    Block::Type type;
    sf::RectangleShape sprite;
};

#endif