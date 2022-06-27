#include "Block.hpp"

#define DEFAULT_SPRITE sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH / DIM_X, WINDOW_HEIGHT / DIM_Y))
#define DEFAULT_TYPE Block::Type::NONE

Block::Block(int id) : type(DEFAULT_TYPE), distance(INT_MAX) {
    this->id = id;
    this->sprite = DEFAULT_SPRITE;
    this->sprite.setFillColor(sf::Color::White);
    this->sprite.setOutlineThickness(1.0f);
    this->sprite.setOutlineColor(sf::Color::Black);
    int y = id / DIM_X;
    int x = id - (y * DIM_X);
    this->sprite.setPosition(sf::Vector2f(x * (WINDOW_WIDTH / DIM_X), y * (WINDOW_HEIGHT / DIM_Y)));
}

Block::Type Block::getType() const {
    return this->type;
}

void Block::setType(Block::Type type) {
    this->type = type;
}

void Block::draw(sf::RenderWindow* window) {
    window->draw(this->sprite);
}