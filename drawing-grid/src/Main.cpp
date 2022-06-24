#include "Core.hpp"
#include "Components/Grid.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "8 Bit Art", sf::Style::Close | sf::Style::Titlebar);
    sf::Event event;
    const int blockSize = 8;
    Grid grid({WINDOW_WIDTH / blockSize, WINDOW_HEIGHT / blockSize}, blockSize, &window);

    while (window.isOpen())
    {
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            grid.reset();
        }
        grid.update();
        window.clear();
        grid.render();
        window.display();
    }

    return EXIT_SUCCESS;
}