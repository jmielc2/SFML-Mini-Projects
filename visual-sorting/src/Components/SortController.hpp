#pragma once

#ifndef SORT_CONTROLLER_H
#define SORT_CONTROLLER_H 1

#include "../stdafx.hpp"
#include "Bar.hpp"

class SortController {
public:
    enum Algo {INSERTION, BUBBLE, SELECTION, NONE};
    enum State {SORTED, NOT_SORTED};

    SortController();
    ~SortController();

    void reset();
    void update();
    void render(sf::RenderWindow *window);
    void setSortType(SortController::Algo type);
    SortController::Algo getSortType();

private:
    class Impl;
    std::unique_ptr<Impl> impl;
};

#endif