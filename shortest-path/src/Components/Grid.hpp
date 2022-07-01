#pragma once

#ifndef BLOCK_GRID_HPP
#define BLOCK_GRID_HPP 1

#include "../stdafx.hpp"
#include "Block.hpp"
#include "../Tools/SP_Algorithm.hpp"

// template <typename E>
class Grid {
public:
    // Getters & Setters
    static Grid* getGrid();

    // Functions
    void draw(sf::RenderWindow* window);
    void update();
    void mouseUpdate(sf::Vector2i &pos, MouseState state);

    // Deleted Functions
    Grid operator=(const Grid& other) = delete;
    Grid(const Grid& other) = delete;
private:
    Grid();
    ~Grid();

    static Grid* grid;
    static std::vector<Node*> blocks;
    static std::vector<Node*> resetBlocks; 
};

#endif