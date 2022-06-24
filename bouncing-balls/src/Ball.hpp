#ifndef BALL_HPP
#define BALL_HPP 1

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <memory>

class Ball {
public:
    // Constructor & Destructor
    Ball(sf::RenderWindow *window, float radius, sf::Color color);
    ~Ball();

    // Functions
    void update(float dt);
    void render();
    sf::Vector2f getPosition();
private:
    class Impl;
    std::unique_ptr<Impl> impl;
};

#endif