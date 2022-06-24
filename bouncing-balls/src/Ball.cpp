#include "Ball.hpp"

class Ball::Impl {
public:
    sf::RenderWindow *window;
    sf::CircleShape shape;
    sf::Vector2f d;
    sf::Vector2f p;
    float radius;
};

Ball::Ball(sf::RenderWindow *window, float radius, sf::Color color) :
    impl(new Ball::Impl()) 
{
    this->impl->window = window;
    this->impl->radius = radius;
    this->impl->shape = sf::CircleShape(radius);
    this->impl->shape.setFillColor(color);
    this->impl->p.x = float(rand() % int(this->impl->window->getSize().x + 1 - (radius * 2)));
    this->impl->p.y = float(rand() % int(this->impl->window->getSize().y + 1 - (radius * 2)));
    this->impl->d.x = (100.0f + float(rand() % 200)) * ((rand() % 2 == 0)? -1 : 1);
    this->impl->d.y = (75.0f + float(rand() % 150)) * ((rand() % 2 == 0)? -1 : 1);
}

Ball::~Ball() {
}

void Ball::render() {
    this->impl->window->draw(this->impl->shape);
}

void Ball::update(float dt) {
    if (float(this->impl->p.x + this->impl->radius * 2) >= float(this->impl->window->getSize().x) && this->impl->d.x > 0) {
        this->impl->d.x *= -1;
    } else if (this->impl->p.x <= 0.0f && this->impl->d.x < 0) {
        this->impl->d.x *= -1;
    }
    if (float(this->impl->p.y + this->impl->radius * 2) >= float(this->impl->window->getSize().y + 110) && this->impl->d.y > 0) {
        this->impl->d.y *= -1;
    } else if (this->impl->p.y <= 0.0f && this->impl->d.y < 0) {
        this->impl->d.y *= -1;
    }
    this->impl->p.x += this->impl->d.x * dt;
    this->impl->p.y += this->impl->d.y * dt;
    this->impl->shape.setPosition(this->impl->p.x, this->impl->p.y);
}

sf::Vector2f Ball::getPosition() {
    return this->impl->p;
}