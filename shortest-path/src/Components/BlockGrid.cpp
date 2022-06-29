#include "BlockGrid.hpp"

std::vector<Block*> BlockGrid::blocks;
std::vector<Block*> BlockGrid::resetBlocks;
BlockGrid* BlockGrid::grid = new BlockGrid();

BlockGrid::BlockGrid() {
    for (int i = 0; i < DIM_X * DIM_Y; i++) {
        BlockGrid::blocks.push_back(new Block(i));
    }
}

BlockGrid::~BlockGrid() {
    for (Block *block : BlockGrid::blocks) {
        delete block;
    }
    return;
}

BlockGrid* BlockGrid::getGrid() {
    return BlockGrid::grid;
}

void BlockGrid::draw(sf::RenderWindow *window) {
    for (Block* block : BlockGrid::blocks) {
        block->draw(window);
    }
}

void BlockGrid::mouseUpdate(sf::Vector2i &pos, MouseState state) {
    for (Block* block : BlockGrid::resetBlocks) {
        block->reset();
    }
    BlockGrid::resetBlocks.clear();

    int x = pos.x / (WINDOW_WIDTH / DIM_X);
    int y = pos.y / (WINDOW_HEIGHT / DIM_Y);
    Block* curBlock = this->blocks.at(y * DIM_X + x);
    curBlock->mouseUpdate(state);

    if (curBlock->getType() == Block::Type::NONE) {
        BlockGrid::resetBlocks.push_back(curBlock);
    }
}