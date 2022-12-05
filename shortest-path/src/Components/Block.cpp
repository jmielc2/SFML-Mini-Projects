#include "Block.hpp"

#define DEFAULT_SPRITE sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH / DIM_X, WINDOW_HEIGHT / DIM_Y))
#define DEFAULT_TYPE Node::Type::NONE

Block::Block(int id) {
    this->id = id;
    this->distance = INT_MAX;
    this->sprite = DEFAULT_SPRITE;
    this->sprite.setFillColor(sf::Color::White);
    this->sprite.setOutlineThickness(1.0f);
    this->sprite.setOutlineColor(sf::Color::Black);
    int y = id / DIM_X;
    int x = id - (y * DIM_X);
    this->sprite.setPosition(sf::Vector2f(x * (WINDOW_WIDTH / DIM_X), y * (WINDOW_HEIGHT / DIM_Y)));
    this->setType(DEFAULT_TYPE);
}

void Block::draw(sf::RenderWindow* window) {
    window->draw(this->sprite);
}

void Block::reset() {
    this->setType(DEFAULT_TYPE);
    this->setDistance(INT_MAX);
    this->sprite.setFillColor(sf::Color::White);
}

void Block::update(Node::Type type) {
    this->setType(type);
    switch (type) {
    case(Node::Type::END):
        this->sprite.setFillColor(sf::Color::Red);
        break;
    case(Node::Type::HOVER):
        this->sprite.setFillColor(sf::Color(0xD2D1D0ff));
        break;
    case(Node::Type::NONE):
        this->sprite.setFillColor(sf::Color::White);
        break;
    case(Node::Type::PATH):
        this->sprite.setFillColor(sf::Color::Blue);
        break;
    case(Node::Type::START):
        this->sprite.setFillColor(sf::Color::Green);
        break;
    case(Node::Type::WALL):
        this->sprite.setFillColor(sf::Color::Black);
        break;
    case(Node::Type::VISITED):
        this->sprite.setFillColor(sf::Color::Yellow);
        break;
    }
}

void Block::setController(GridController<Block>* controller) {
    this->controller = controller;
}

GridController<Block>* Block::getController() const {
    return this->controller;
}