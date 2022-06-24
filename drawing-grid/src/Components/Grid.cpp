#include "Grid.hpp"

class Grid::Impl
{
public:
    const int MAX_X = 100;
    const int MAX_Y = 100;

    int xStart;
    int yStart;
    sf::Vector2u dim;
    float size;
    sf::RenderWindow* window;
    sf::Vector2i prevMousePos;

    std::stack<Block*> prevRoundBlocks;
    Block* pointerBlock;
    std::vector<std::vector<Block*>> grid;

    void updateBlock(int x, int y);
    bool blockExists(int x, int y);
    void resetPrevBlocks();
};

void Grid::Impl::updateBlock(int x, int y) {
    if (this->blockExists(x,y)) {
        this->grid.at(y).at(x)->update();
        if (!this->grid.at(y).at(x)->isFilled()) {
            this->prevRoundBlocks.push(this->grid.at(y).at(x));
        }
    }
}

bool Grid::Impl::blockExists(int x, int y) {
    return (x >= 0 && x < this->dim.x && y >= 0 && y < this->dim.y);
}

void Grid::Impl::resetPrevBlocks() {
    Block* cur;
    while (!this->prevRoundBlocks.empty()) {
        cur = this->prevRoundBlocks.top();
        this->prevRoundBlocks.pop();
        cur->reset();
    }
}


/////////////////////////////////////////////////////////////


Grid::Grid(const sf::Vector2u dim, float size, sf::RenderWindow* window) :
    impl(new Grid::Impl())
{
    if (dim.x > this->impl->MAX_X || dim.x <= 0) {
        LOG("ERROR: Invalid grid 'x' dimension.");
        window->close();
    } else if (dim.y > this->impl->MAX_Y || dim.y <= 0) {
        LOG("ERROR: Invalid grid 'y' dimension.");
        window->close();
    }
    this->impl->xStart = (window->getSize().x - (dim.x * size)) / 2;
    this->impl->yStart = (window->getSize().y - (dim.y * size)) / 2;
    for (int y = 0; y < dim.y; y++) {
        std::vector<Block*> row;
        for (int x = 0; x < dim.x; x++) {
            row.push_back(new Block({float(this->impl->xStart + size * x), float(this->impl->yStart + size * y)}, size, window));
        }
        this->impl->grid.push_back(row);
    }
    this->impl->window = window;
    this->impl->prevMousePos = sf::Mouse::getPosition(*window);
    this->impl->size = size;
    this->impl->dim = dim;
    this->impl->pointerBlock = nullptr;
}

Grid::~Grid()
{
    for (int y = 0; y < this->impl->grid.size(); y++) {
        for (int x = 0; x < this->impl->grid.at(y).size(); x++) {
            delete this->impl->grid.at(y).at(x);
        }
    }
}

void Grid::update()
{
    // Calculate the minimum number of jumps to new mouse position (by block size)
    int tempX, tempY;    
    sf::Vector2i mousePos = sf::Mouse::getPosition(*this->impl->window);

    tempX = static_cast<int>((mousePos.x - this->impl->xStart) / this->impl->size);
    tempY = static_cast<int>((mousePos.y - this->impl->yStart) / this->impl->size);
    sf::Vector2i curBoxIndex {tempX, tempY};

    tempX = static_cast<int>((this->impl->prevMousePos.x - this->impl->xStart) / this->impl->size);
    tempY = static_cast<int>((this->impl->prevMousePos.y - this->impl->yStart) / this->impl->size);
    sf::Vector2i prevBoxIndex {tempX, tempY};
    
    sf::Vector2i jump {prevBoxIndex.x - curBoxIndex.x, prevBoxIndex.y - curBoxIndex.y};
    int numJumps = std::max(fabs(jump.y), fabs(jump.x));
    
    // Reset Unfilled Blocks from the last Update
    this->impl->resetPrevBlocks();
    
    // Calculate Jump Size for Each Axis & Update Each jump block
    float jumpSizeY = jump.y / static_cast<float>(numJumps);
    float jumpSizeX = jump.x / static_cast<float>(numJumps);
    do {
        tempX = static_cast<int>(curBoxIndex.x + (jumpSizeX * numJumps));
        tempY = static_cast<int>(curBoxIndex.y + (jumpSizeY * numJumps));
        this->impl->updateBlock(tempX, tempY);
        numJumps--;
    } while (numJumps >= 0);

    // Set the Pointer Block and Color it Red
    if (this->impl->pointerBlock) {
        this->impl->pointerBlock->update();
    }
    if (this->impl->blockExists(curBoxIndex.x, curBoxIndex.y)) {
        this->impl->pointerBlock = this->impl->grid.at(curBoxIndex.y).at(curBoxIndex.x);
        this->impl->pointerBlock->setFill(sf::Color::Red);
    }
    
    // Update prevMousePos for Next Update
    this->impl->prevMousePos = mousePos;
}

void Grid::render()
{
    for (auto &row : this->impl->grid) {
        for (auto &block : row) {
            block->render();
        }
    }
}

void Grid::reset()
{
    for (auto &row : this->impl->grid) {
        for (auto &block : row) {
            block->reset();
        }
    }
}