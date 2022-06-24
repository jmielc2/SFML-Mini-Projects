#pragma once

#ifndef BAR_H
#define BAR_H 1

#include "../stdafx.hpp"

class Bar {
public:
    Bar(sf::Vector2f dimensions);
    Bar(const Bar &other);
    ~Bar();
    
    float getHeight() const;
    void setPosition(const sf::Vector2f &pos);
    void render(sf::RenderWindow* window) const;

    Bar operator=(const Bar &other);
private:
    Bar();
    class Impl;
    std::unique_ptr<Impl> impl;
};

#endif