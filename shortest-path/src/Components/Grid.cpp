#include "Grid.hpp"

std::vector<Node*> Grid::blocks;
std::vector<Node*> Grid::resetBlocks;
Grid* Grid::grid = new Grid();

Grid::Grid() {
    for (int i = 0; i < DIM_X * DIM_Y; i++) {
        Grid::blocks.push_back(new Block(i));
    }
}

Grid::~Grid() {
    for (Node *block : Grid::blocks) {
        delete block;
    }
    return;
}

Grid* Grid::getGrid() {
    return Grid::grid;
}

void Grid::draw(sf::RenderWindow *window) {
    for (Node* block : Grid::blocks) {
        block->draw(window);
    }
}

void Grid::update() {
    std::vector<Node*> path = SP_Algorithm::shortestPath(Grid::blocks.at(0), Grid::blocks.at(Grid::blocks.size() - 1), Grid::blocks);
    for (Node* node : path) {
        node->update(Node::Type::PATH);
    }
}

void Grid::mouseUpdate(sf::Vector2i &pos, MouseState state) {
    for (Node* node : Grid::resetBlocks) {
        node->reset();
    }
    Grid::resetBlocks.clear();

    int x = pos.x / (WINDOW_WIDTH / DIM_X);
    int y = pos.y / (WINDOW_HEIGHT / DIM_Y);
    Block* curBlock = dynamic_cast<Block*>(this->blocks.at(y * DIM_X + x));
    curBlock->mouseUpdate(state);

    if (curBlock->getType() == Node::Type::NONE) {
        Grid::resetBlocks.push_back(curBlock);
    }
}