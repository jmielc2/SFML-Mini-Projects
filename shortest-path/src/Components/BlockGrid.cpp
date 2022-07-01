#include "BlockGrid.hpp"

std::vector<Node*> BlockGrid::blocks;
std::vector<Node*> BlockGrid::resetBlocks;
BlockGrid* BlockGrid::grid = new BlockGrid();

BlockGrid::BlockGrid() {
    for (int i = 0; i < DIM_X * DIM_Y; i++) {
        BlockGrid::blocks.push_back(new Block(i));
    }
}

BlockGrid::~BlockGrid() {
    for (Node *block : BlockGrid::blocks) {
        delete block;
    }
    return;
}

BlockGrid* BlockGrid::getGrid() {
    return BlockGrid::grid;
}

void BlockGrid::draw(sf::RenderWindow *window) {
    for (Node* block : BlockGrid::blocks) {
        block->draw(window);
    }
}

void BlockGrid::update() {
    std::vector<Node*> path = SP_Algorithm::shortestPath(BlockGrid::blocks.at(0), BlockGrid::blocks.at(BlockGrid::blocks.size() - 1), BlockGrid::blocks);
    for (Node* node : path) {
        Block* block = dynamic_cast<Block*>(node);
        block->update(Block::Type::PATH);
    }
}

void BlockGrid::mouseUpdate(sf::Vector2i &pos, MouseState state) {
    for (Node* block : BlockGrid::resetBlocks) {
        block->reset();
    }
    BlockGrid::resetBlocks.clear();

    int x = pos.x / (WINDOW_WIDTH / DIM_X);
    int y = pos.y / (WINDOW_HEIGHT / DIM_Y);
    Block* curBlock = dynamic_cast<Block*>(this->blocks.at(y * DIM_X + x));
    curBlock->mouseUpdate(state);

    if (curBlock->getType() == Block::Type::NONE) {
        BlockGrid::resetBlocks.push_back(curBlock);
    }
}