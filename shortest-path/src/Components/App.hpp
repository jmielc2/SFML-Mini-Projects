#pragma once

#ifndef APP_HPP
#define APP_HPP 1

#include "../stdafx.hpp"
#include "BlockGrid.hpp"


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
    static BlockGrid* grid;
    
    static sf::RenderWindow* window;
    static sf::Event event;
};

#endif