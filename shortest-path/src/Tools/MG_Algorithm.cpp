#include "MG_Algorithm.hpp"

std::map<int, sf::Vector2i> MG_Algorithm::directions;

void MG_Algorithm::init() {
    directions.emplace((int) UP, sf::Vector2i(0, -1));
    directions.emplace((int) RIGHT, sf::Vector2i(1, 0));
    directions.emplace((int) DOWN, sf::Vector2i(0, 1));
    directions.emplace((int) LEFT, sf::Vector2i(-1, 0));
}