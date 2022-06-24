#pragma once

#ifndef APP_H
#define APP_H 1

#include "../stdafx.hpp"
#include "SortController.hpp"

class App {
public:
    // App Stage Enumeration
    enum Stage {SORTING, CONFIGURING, END};

    // Deleted Operators
    App operator=(const App&) = delete;
    App(const App&) = delete;

    // Modifiers
    static void update();

    // Getters & Setters
    static bool isRunning();
    static App::Stage getStage();

private:
    App() {};
    class Impl;
    static std::unique_ptr<Impl> impl;
};

#endif