#include <SFML/Graphics.hpp>
#include <vector>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "Ball.hpp"

#define RADIUS 25.f

void updateWindow(sf::RenderWindow &window, std::vector<Ball*> &balls, float dt);

int main() {
    srand(time(NULL));
    sf::Clock clock;
    sf::Event event;
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Bouncing Balls");

    std::vector<Ball*> balls(30);
    for (auto &a : balls) {
        float radius = float(rand() % 26) + 25.0f;
        uint8_t red = (rand() % 256);
        uint8_t green = rand() % 256;
        uint8_t blue = rand() % 256;
        a = new Ball(&window, radius, sf::Color(red, green, blue));
    }
    
    while (window.isOpen()) {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                window.close();
            }
        }
        updateWindow(window, balls, clock.restart().asSeconds());
    }

    for (int i = 0; i < (int) balls.size(); i++) {
        delete balls[i];
    }

    return 0;
}

void updateWindow(sf::RenderWindow &window, std::vector<Ball*> &balls, float dt) {
    window.clear();
    for (auto &ball : balls) {
        ball->update(dt);
        ball->render();
    }
    window.display();
}