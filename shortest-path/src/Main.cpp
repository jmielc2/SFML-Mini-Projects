#include "stdafx.hpp"
#include "Controllers/App.hpp"

int main() {
    App app = App::getApp();
    app.init();
    while (app.isRunning()) {
        app.update();
    }

    return EXIT_SUCCESS;
}