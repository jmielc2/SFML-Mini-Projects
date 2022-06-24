#include "Block.hpp"

class Block::Impl
{
public:
    sf::RectangleShape block;
    sf::RenderWindow* window;
    sf::Color color;
    bool filled;
    
};




//////////////////////////////////////////////////////////////////////////


Block::Block(const sf::Vector2f pos, float size, sf::RenderWindow* window) :
    impl(new Block::Impl())
{
    this->impl->block.setPosition(pos);
    this->impl->block.setFillColor(sf::Color::White);
    this->impl->block.setSize(sf::Vector2f(size, size));
    this->impl->window = window;
    this->impl->color = sf::Color::White;
    this->impl->filled = false;
}

Block::~Block()
{
    return;
}

// Updates the Blocks State Based on 
void Block::update() {
    if (this->impl->filled) {
        this->setFill(sf::Color::Black);
        return;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        this->setFill(sf::Color::Black);
        this->impl->filled = true;
    }
}

void Block::reset()
{
    this->impl->filled = false;
    this->setFill(sf::Color::White);
}

void Block::render()
{
    this->impl->block.setFillColor(this->impl->color);
    this->impl->window->draw(this->impl->block);
}

bool Block::isFilled() const {
    return this->impl->filled;
}

void Block::setFill(const sf::Color &color) const {
    this->impl->color = color;
}

