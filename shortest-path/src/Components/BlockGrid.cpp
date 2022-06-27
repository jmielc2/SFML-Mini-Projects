#include "BlockGrid.hpp"

BlockGrid* BlockGrid::grid = new BlockGrid();

BlockGrid::BlockGrid() {
    for (int i = 0; i < DIM_X * DIM_Y; i++) {
        this->blocks.push_back(Block(i));
    }
}

BlockGrid::~BlockGrid() {
    delete BlockGrid::grid;
}

BlockGrid* BlockGrid::getGrid() {
    return BlockGrid::grid;
}

void BlockGrid::draw(sf::RenderWindow *window) {
    for (Block &block : this->blocks) {
        block.draw(window);
    }
}