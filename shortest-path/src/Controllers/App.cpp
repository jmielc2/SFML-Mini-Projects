#include "App.hpp"

App App::app;
App::State App::appState = App::State::RUNNING;
GridController<Block> App::gridController;
MouseState App::mouseState = MouseState::HOVER;

sf::RenderWindow* App::window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Shortest Path Finder", sf::Style::Titlebar | sf::Style::Close);
sf::Event App::event;

static void printCommands(std::string file) {
    std::ifstream inFile(file);
    if (inFile.good()) {
        std::string input;
        while (!inFile.eof()) {
            std::getline(inFile, input);
            std::cout << input << std::endl;
        }
    } else {
        LOG("Error: Failed to open '" + file + "'.");
    }
}

App::App() {
    srand(time(NULL));
    MG_Algorithm::init();
    return;
}

bool App::isRunning() {
    return (this->getAppState() == App::State::RUNNING) && App::window->isOpen();
}

void App::update() {
    if (this->window->pollEvent(this->event)) {
        if (this->event.type == sf::Event::EventType::Closed) {
            quit();
            return;
        }
        this->processMouseEvents();
        this->processKeyEvents();
    }

    this->window->clear(sf::Color::Black);
    App::gridController.drawGrid(this->window);
    this->window->display();
}

App App::getApp() {
    return App::app;
}

void App::quit() {
    if (this->window->isOpen()) {
        this->window->close();
    }
    this->setAppState(App::State::CLOSED);
}

void App::init() {
    App::window->setFramerateLimit(60);
    printCommands("../lib/commands.txt");
}

App::State App::getAppState() const {
    return this->appState;
}

void App::setAppState(App::State state) {
    this->appState = state;
}

void App::processKeyEvents() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        quit();
        return;
    }
    switch (this->gridController.getPhase()) {
        case (GridController<Block>::Phase::SETUP):
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
                App::gridController.findPath();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
                this->gridController.resetGrid();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) {
                this->gridController.generateMaze();
            }
            break;
        case (GridController<Block>::Phase::DONE):
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
                this->gridController.resetGrid();
            }
            break;
        default:
            break;
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