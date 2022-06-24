#include "stdafx.hpp"

int main() {
    while (App::isRunning()) {
        App::update();
    }
    return EXIT_SUCCESS;
}