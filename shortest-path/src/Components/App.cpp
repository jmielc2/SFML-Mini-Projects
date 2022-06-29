#include "App.hpp"

App App::app;
App::State App::appState = App::State::RUNNING;
BlockGrid* App::grid;

sf::RenderWindow* App::window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Shortest Path Finder", sf::Style::Titlebar | sf::Style::Close);
sf::Event App::event;

App::App() {
    this->grid = BlockGrid::getGrid();
}

bool App::isRunning() {
    return (this->getAppState() == App::State::RUNNING) && App::window->isOpen();
}

void App::update() {
    this->window->pollEvent(this->event);
    this->processKeyEvents();
    this->processMouseEvents();

    this->window->clear(sf::Color::Black);

    this->grid->draw(this->window);

    this->window->display();
}

void App::quit() {
    if (this->window->isOpen()) {
        this->window->close();
    }
    this->setAppState(App::State::CLOSED);
}

App App::getApp() {
    return App::app;
}

App::State App::getAppState() const {
    return this->appState;
}

void App::setAppState(App::State state) {
    this->appState = state;
}

void App::processKeyEvents() {
    if (event.type == sf::Event::Closed) {
        this->window->close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        this->window->close();
    }
}

void App::processMouseEvents() {
    sf::Vector2i pos = sf::Mouse::getPosition(*this->window);
    if (pos.x < 0 || pos.x > WINDOW_WIDTH || pos.y < 0 || pos.y > WINDOW_HEIGHT) {
        return;
    }


    MouseState mouseState = MouseState::HOVER;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        mouseState = MouseState::LEFT_CLICK;
    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
        mouseState = MouseState::RIGHT_CLICK;
    }
    App::grid->mouseUpdate(pos, mouseState);
}