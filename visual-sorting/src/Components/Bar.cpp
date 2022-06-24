#include "Bar.hpp"

class Bar::Impl {
public:
    float value;
    sf::RectangleShape sprite;
};

////////////////////////////////////////////////////////

Bar::Bar(sf::Vector2f dimensions) : impl{new Impl()} {
    this->impl->value = dimensions.y;
    this->impl->sprite = sf::RectangleShape(dimensions);
    this->impl->sprite.setFillColor(sf::Color::White);
}

Bar::Bar() : impl(new Impl()) {
    return;
}

Bar::~Bar() {

}

Bar::Bar(const Bar &other) : impl(new Impl()) {
    this->impl->value = other.impl->value;
    this->impl->sprite = other.impl->sprite;
}

float Bar::getHeight() const {
    return this->impl->value;
}

void Bar::setPosition(const sf::Vector2f &pos) {
    this->impl->sprite.setPosition(pos);
}

Bar Bar::operator=(const Bar& other) {
    Bar newBar;
    newBar.impl->value = other.impl->value;
    newBar.impl->sprite = other.impl->sprite;
    return newBar;
}

void Bar::render(sf::RenderWindow* window) const {
    window->draw(this->impl->sprite);
}