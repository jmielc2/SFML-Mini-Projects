#pragma once

#ifndef BLOCK_GRID_HPP
#define BLOCK_GRID_HPP 1

#include "../stdafx.hpp"
#include "Block.hpp"

class BlockGrid {
public:
    // Getters & Setters
    static BlockGrid* getGrid();

    // Functions
    void draw(sf::RenderWindow* window);
    void mouseUpdate(sf::Vector2i &pos, MouseState state);

    // Deleted Functions
    BlockGrid operator=(const BlockGrid& other) = delete;
    BlockGrid(const BlockGrid& other) = delete;
private:
    BlockGrid();
    ~BlockGrid();

    static BlockGrid* grid;
    static std::vector<Block*> blocks;
    static std::vector<Block*> resetBlocks; 
};

#endif