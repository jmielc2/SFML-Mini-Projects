#ifndef BLOCK_HPP
#define BLOCK_HPP 1

#include "../Core.hpp"

class Block
{
public:
    // Constructor Destructor
    Block(const sf::Vector2f pos, float size, sf::RenderWindow* window);
    ~Block();

    // Functions
    void update();
    void reset();
    void render();

    // Accessors
    bool isFilled() const;
    void setFill(const sf::Color &color) const;
private:
    class Impl;
    std::unique_ptr<Impl> impl;
};

#endif