#ifndef GRID_HPP
#define GRID_HPP 1

#include "../Core.hpp"
#include "Block.hpp"

class Grid {
public:
    // Constructor & Destructor
    Grid(const sf::Vector2u dim, float size, sf::RenderWindow* window);
    ~Grid();

    // Functions
    void update();
    void render();
    void reset();
private:
    class Impl;
    std::unique_ptr<Impl> impl;
};

#endif