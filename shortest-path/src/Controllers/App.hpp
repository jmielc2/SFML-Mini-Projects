#pragma once

#ifndef APP_HPP
#define APP_HPP 1

#include "../stdafx.hpp"
#include "GridController.hpp"
#include "../Components/Block.hpp"

class App {
public:
    enum State {RUNNING, CLOSED};

    bool isRunning();
    void update();
    void quit();

    static App getApp();
    App::State getAppState() const;

    App operator=(const App &other) = delete;
private:
    App();
    void setAppState(App::State state);
    void processKeyEvents();
    void processMouseEvents();

    static App app;
    static App::State appState;
    static GridController<Block> gridController;
    
    static sf::RenderWindow* window;
    static sf::Event event;
};

#endif