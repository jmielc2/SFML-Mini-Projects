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

    // Deleted Functions
    BlockGrid operator=(const BlockGrid& other) = delete;
    BlockGrid(const BlockGrid& other) = delete;
private:
    BlockGrid();
    ~BlockGrid();

    static BlockGrid* grid;
    std::vector<Block> blocks;
};

#endif