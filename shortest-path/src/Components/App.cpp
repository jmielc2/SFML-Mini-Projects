#include "App.hpp"

App App::app;

App::State App::appState = App::State::RUNNING;

sf::RenderWindow* App::window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Shortest Path Finder", sf::Style::Titlebar | sf::Style::Close);

sf::Event App::event;

App::App() {

}

bool App::isRunning() {
    return (this->getAppState() == App::State::RUNNING) && App::window->isOpen();
}

void App::update() {
    this->window->pollEvent(this->event);
    if (event.type == sf::Event::Closed) {
        this->window->close();
    }
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