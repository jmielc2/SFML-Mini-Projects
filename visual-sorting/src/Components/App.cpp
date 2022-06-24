#include "App.hpp"

class App::Impl {
public:
    // Private Member Variables
    static App app;
    App::Stage curStage;
    static sf::Clock clock;
    std::unique_ptr<sf::RenderWindow> window;
    sf::Event event;
    SortController controller;

    // Private Methods
    void configure();
    void sort();
    void setStage(App::Stage newStage);

    Impl();
};

std::unique_ptr<App::Impl> App::impl = std::unique_ptr<App::Impl>(new App::Impl());

App App::Impl::app;

sf::Clock App::Impl::clock;

App::Impl::Impl() {
    this->setStage(App::Stage::CONFIGURING);
}

void App::Impl::configure() {
    char option = 'A';
    std::cout << "Enter 'S' to sort or 'Q' to quit: ";
    std::cin >> option;
    if (option == 's' || option == 'S') {
        this->setStage(App::Stage::SORTING);
    } else if (option == 'q' || option == 'Q') {
        this->setStage(App::Stage::END);
        return;
    } else {
        std::cout << std::endl << "Error, invalid option." << std::endl << std::endl;
        return;
    }

    std::cout << std::endl << "Sorting Algorithm Options:" << std::endl;
    std::cout << "'I' = Insertion Sort" << std::endl;
    std::cout << "'S' = Selection Sort" << std::endl;
    std::cout << "'B' = Bubble Sort" << std::endl;
    std::cout << std::endl << "Choose a sorting algorithm: ";
    std::cin >> option;
    if (option == 'I' || option == 'i') {
        this->controller.setSortType(SortController::Algo::INSERTION);
    } else if (option == 'B' || option == 'b') {
        this->controller.setSortType(SortController::Algo::BUBBLE);
    } else if (option == 'S' || option == 's') {
        this->controller.setSortType(SortController::Algo::SELECTION);
    } else {
        this->setStage(App::Stage::CONFIGURING);
        std::cout << std::endl << "Error, invalid sorting algorithm." << std::endl << std::endl;
    }
}

void App::Impl::sort() {
    std::string name;
    switch (this->controller.getSortType()) {
        case(SortController::Algo::INSERTION):
            name = "Insertion Sorting";
            break;
        case(SortController::Algo::BUBBLE):
            name = "Bubble Sorting";
            break;
        case(SortController::Algo::SELECTION):
            name = "Selection Sorting";
            break;
        default:
            LOG("ERROR: Selected algorithm not recognized.");
            break;
    }
    this->window.reset(new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), name, sf::Style::Titlebar | sf::Style::Close));
    while (window->isOpen())
    {
        while (window->pollEvent(this->event))
        {
            if (this->event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window->close();
            }
        }

        this->window->clear();
        this->controller.render(this->window.get());
        window->display();
        if (this->clock.getElapsedTime().asMilliseconds() >= 33) {
            this->clock.restart();
            this->controller.update();
        }
    }
    this->setStage(App::Stage::CONFIGURING);
}

void App::Impl::setStage(App::Stage newStage) {
    this->curStage = newStage;
}

//////////////////////////////////////////////////////////////

bool App::isRunning() {
    return (App::getStage() != App::Stage::END);
}

void App::update() {
    switch (App::getStage()) {
        case(App::Stage::CONFIGURING):
            impl->controller.reset();
            impl->configure();
            break;
        case(App::Stage::SORTING):
            impl->clock.restart();
            impl->sort();
            break;
        case(App::Stage::END):
            break;
        default:
            LOG("ERROR: Unidentified app stage on app update.");
            break;
    };
}

App::Stage App::getStage() {
    return impl->curStage;
}