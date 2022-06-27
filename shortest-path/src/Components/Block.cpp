#include "Block.hpp"

#define DEFAULT_SPRITE sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH / 20.0f, WINDOW_HEIGHT / 20.0f))
#define DEFAULT_TYPE Block::Type::NONE

Block::Block(int id) : type(DEFAULT_TYPE) {
    this->id = id;
    this->distance = INT_MAX;
    this->sprite = DEFAULT_SPRITE;
    this->sprite.setFillColor(sf::Color::White);
    this->sprite.setOutlineThickness(1.0f);
    this->sprite.setOutlineColor(sf::Color::Black);
    float y = id % 20;
    float x = id - (y * 20.0f);
    this->sprite.setPosition(sf::Vector2f(x * 35.0f, y * 35.0f));
}

int Block::getID() const {
    return this->id;
}

int Block::getDistance() const {
    return this->distance;
}

void Block::setDistance(int distance) {
    this->distance = distance;
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