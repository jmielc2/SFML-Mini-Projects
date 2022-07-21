#include "App.hpp"

App App::app;
App::State App::appState = App::State::RUNNING;
GridController<Block> App::gridController;
MouseState App::mouseState = MouseState::HOVER;

sf::RenderWindow* App::window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Shortest Path Finder", sf::Style::Titlebar | sf::Style::Close);
sf::Event App::event;

App::App() {
    return;
}

bool App::isRunning() {
    return (this->getAppState() == App::State::RUNNING) && App::window->isOpen();
}

void App::update() {
    this->window->pollEvent(this->event);
    this->processMouseEvents();
    this->processKeyEvents();

    this->window->clear(sf::Color::Black);
    App::gridController.drawGrid(this->window);
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
    if (event.key.code == sf::Keyboard::Key::Escape) {
        this->window->close();
        return;
    }
    if (event.type == sf::Event::EventType::KeyPressed) {
        switch (this->gridController.getPhase()) {
            case (GridController<Block>::Phase::SETUP):
                if (event.key.code == sf::Keyboard::Key::Enter) {
                    LOG("SOLVING");
                    App::gridController.findPath();
                } else if (event.key.code == sf::Keyboard::Key::R) {
                    LOG("RESETTING");
                    this->gridController.resetGrid();
                }
                break;
            case (GridController<Block>::Phase::DONE):
                if (event.key.code == sf::Keyboard::Key::R) {
                    LOG("RESETTING");
                    this->gridController.resetGrid();
                }
                break;
            default:
                break;
        }
    }
}

void App::processMouseEvents() {
    sf::Vector2i pos = sf::Mouse::getPosition(*this->window);
    if (pos.x < 0 || pos.x >= WINDOW_WIDTH || pos.y < 0 || pos.y >= WINDOW_HEIGHT) {
        return;
    }
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if (mouseState == MouseState::LEFT_CLICK || mouseState == MouseState::LEFT_HOLD) {
            mouseState = MouseState::LEFT_HOLD;
        } else {
            mouseState = MouseState::LEFT_CLICK;
        }
    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
        if (mouseState == MouseState::RIGHT_CLICK || mouseState == MouseState::RIGHT_HOLD) {
            mouseState = MouseState::RIGHT_HOLD;
        } else {
            mouseState = MouseState::RIGHT_CLICK;
        }
    } else {
        mouseState = MouseState::HOVER;
    }

    App::gridController.mouseUpdate(pos, mouseState);
}