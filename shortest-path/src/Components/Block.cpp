#include "Block.hpp"

#define DEFAULT_SPRITE sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH / DIM_X, WINDOW_HEIGHT / DIM_Y))
#define DEFAULT_TYPE Block::Type::NONE

Block::Block(int id) : type(DEFAULT_TYPE) {
    this->id = id;
    this->distance = INT_MAX;
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

void Block::reset() {
    this->setType(DEFAULT_TYPE);
    this->sprite.setFillColor(sf::Color::White);
}

void Block::mouseUpdate(MouseState state) {
    switch (state) {
        case(MouseState::HOVER):
            if (this->getType() == Block::Type::NONE) {
                this->sprite.setFillColor(sf::Color(0xD2D1D0ff));
            }
            break;
        case(MouseState::LEFT_CLICK):
            break;
        case(MouseState::RIGHT_CLICK):
            Block::Type curType = this->getType();
            if (curType != Block::Type::START && curType != Block::Type::END) {
                this->setType(Block::Type::WALL);
                this->sprite.setFillColor(sf::Color::Black);
            }
            break;
    }
}