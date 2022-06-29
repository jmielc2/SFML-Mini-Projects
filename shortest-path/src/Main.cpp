#include "stdafx.hpp"
#include "Components/App.hpp"

int main() {
    App app = App::getApp();

    while (app.isRunning()) {
        app.update();
    }

    return EXIT_SUCCESS;
}