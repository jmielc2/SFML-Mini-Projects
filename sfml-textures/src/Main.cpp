#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#define NUM_PICS 9

// Function Forward Declarations
void resizeSprite(sf::Sprite* &sprite, const sf::RenderWindow &window, const sf::Vector2u &windowDimensions, sf::Vector2f &scale);
std::string getPictureFilename(unsigned int num);
void loadTextures(std::vector<sf::Texture*> &textures);
void linkTexturesToSprites(const std::vector<sf::Texture*> &textures, std::vector<sf::Sprite*> &sprites);
void deleteTextures(std::vector<sf::Texture*> &textures);
void deleteSprites(std::vector<sf::Sprite*> &sprites);
void cyclePicture(const std::vector<sf::Texture*> &textures, sf::Texture* &texture,
    const std::vector<sf::Sprite*> &sprites, sf::Sprite* &sprite, unsigned int &num);


// Starting point of the Program
int main(int argc, char **argv)
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Pic Cycle", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
    sf::Event event;
    sf::Vector2f scale = {0.95f, 0.95f};
    sf::Clock clock;
    sf::Clock mouseTimer;

    // Textures
    std::vector<sf::Texture*> textures(NUM_PICS);
    std::vector<sf::Sprite*>  sprites(NUM_PICS);
    loadTextures(textures);
    linkTexturesToSprites(textures, sprites);
    
    // Set a sprite reference that will be drawn
    unsigned int curPicture = 1;
    sf::Texture* texture = textures[curPicture];
    sf::Sprite* sprite = sprites[curPicture];

    sprite->setScale(scale.x, scale.y);
    sprite->setPosition(((window.getSize().x / 2) - (texture->getSize().x * scale.x) / 2), ((window.getSize().y / 2) - (texture->getSize().y * scale.y) / 2));

    sf::Vector2u windowDimensions = window.getSize();

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == event.Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            } else if (event.type == event.Resized) {
                resizeSprite(sprite, window, windowDimensions, scale);
                sprite->setPosition(((window.getSize().x / 2) - (texture->getSize().x * scale.x) / 2), ((window.getSize().y / 2) - (texture->getSize().y * scale.y) / 2));
                windowDimensions = window.getSize();
            }
        }
        if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseTimer.getElapsedTime().asSeconds() >= 0.25f) 
            || clock.getElapsedTime().asSeconds() >= 5.0f) {
            cyclePicture(textures, texture, sprites, sprite, curPicture);
            resizeSprite(sprite, window, windowDimensions, scale);
            sprite->setPosition(((window.getSize().x / 2) - (texture->getSize().x * scale.x) / 2), ((window.getSize().y / 2) - (texture->getSize().y * scale.y) / 2));
            if (mouseTimer.getElapsedTime().asSeconds() >= 0.25f) {
                mouseTimer.restart();
            }
            clock.restart();
        }
        window.clear();
        window.draw(*sprite);
        window.display();
    }

    deleteTextures(textures);
    deleteSprites(sprites);
    return 0;
}

// Resizes the Sprite to maintain constant size based on past window Dimensions and new window dimensions
void resizeSprite(sf::Sprite* &sprite, const sf::RenderWindow &window, const sf::Vector2u &windowDimensions, sf::Vector2f &scale) {
    scale.x = float(windowDimensions.x) / float(window.getSize().x) * scale.x;
    scale.y = float(windowDimensions.y) / float(window.getSize().y) * scale.y;
    sprite->setScale(scale.x, scale.y);
}

// Generates a unique filename string based the given number input
std::string getPictureFilename(unsigned int num)
{
    return "pic (" + std::to_string(num) + ").jpg";
}

// Loads the image textures from the library
void loadTextures(std::vector<sf::Texture*> &textures)
{
    for (unsigned int i = 0; i < textures.size(); i++) {
        textures[i] = new sf::Texture();
        textures[i]->loadFromFile("../lib/" + getPictureFilename(i));
        textures[i]->setSmooth(true);
    }
}

// Deletes the loaded textures from the library
void deleteTextures(std::vector<sf::Texture*> &textures)
{
    for (unsigned int i = 0; i < textures.size(); i++) {
        delete textures[i];
        textures[i] = nullptr;
    }
}

// Deletes the created sprites from the library
void deleteSprites(std::vector<sf::Sprite*> &sprites)
{
    for (unsigned int i = 0; i < sprites.size(); i++) {
        delete sprites[i];
        sprites[i] = nullptr;
    }
}

// Links the textures to the sprites (textures are assumed to be already loaded)
void linkTexturesToSprites(const std::vector<sf::Texture*> &textures, std::vector<sf::Sprite*> &sprites)
{
    for (unsigned int i = 0; i < sprites.size(); i++) {
        sprites[i] = new sf::Sprite();
        sprites[i]->setTexture(*textures[i]);
    }
}

// Changes the current texture and sprite pointer to the next ones on the list
void cyclePicture(const std::vector<sf::Texture*> &textures, sf::Texture* &texture,
    const std::vector<sf::Sprite*> &sprites, sf::Sprite* &sprite, unsigned int &num)
{
    num++;
    if (num >= NUM_PICS) {
        num = 0;
    }
    texture = textures[num];
    sprite = sprites[num];
}