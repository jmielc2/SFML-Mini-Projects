#include "SortController.hpp"

class SortController::Impl {
public:
    int numBars;
    std::vector<Bar*> bars;
    SortController::Algo curAlgorithm;
    SortController::State curState;
    static std::mt19937 generator;

    void selectionSortStep(bool reset);
    void insertionSortStep(bool reset);
    void bubbleSortStep(bool reset);
    void scramble();
};

std::mt19937 SortController::Impl::generator;

void SortController::Impl::selectionSortStep(bool reset = false) {
    static long long unsigned i = 0, j;
    if (i < this->bars.size() && !reset) {
        j = i;
        int minIndex = j;
        for (; j < this->bars.size(); j++) {
            if (this->bars.at(minIndex)->getHeight() > this->bars.at(j)->getHeight()) {
                minIndex = j;
            }
        }
        Bar *temp = this->bars.at(i);
        this->bars[i] = this->bars[minIndex];
        this->bars[minIndex] = temp;
        i++;
    } else {
        i = j = 0;
        this->curState = SortController::State::SORTED;
    }
}

void SortController::Impl::insertionSortStep(bool reset = false) {
    static long long unsigned i = 1;
    if (i < this->bars.size() && !reset) {
        int j = i;
        while (j > 0 && this->bars[j]->getHeight() < this->bars[j - 1]->getHeight()) {
            Bar *temp = this->bars[j];
            this->bars[j] = this->bars[j - 1];
            this->bars[j - 1] = temp;
            j--;
        }
        i++;
    } else {
        i = 0;
        this->curState = SortController::State::SORTED;
    }
}

void SortController::Impl::bubbleSortStep(bool reset = false) {
    static int j = 0;
    static bool swapped = false;
    if (!reset) {
        for (long long unsigned i = 0; i < this->bars.size() - 1 - j; i++) {
            if (this->bars[i + 1]->getHeight() < this->bars[i]->getHeight()) {
                swapped = true;
                Bar *temp = this->bars[i];
                this->bars[i] = this->bars[i + 1];
                this->bars[i + 1] = temp;
            }
        }
        j++;
        if (!swapped) {
            swapped = false;
            this->curState = SortController::State::SORTED;
        }
    } else {
        swapped = false;
        this->curState = SortController::State::SORTED;
    }
    j = 0;
}

void SortController::Impl::scramble() {
    for (int i = 0; i < this->numBars; i++) {
        int index1 = this->generator() % this->numBars;
        int index2 = this->generator() % this->numBars;
        Bar *temp1 = this->bars.at(index1);
        this->bars[index1] = this->bars[index2];
        this->bars[index2] = temp1;
    }
}

///////////////////////////////////////////////////////////

SortController::SortController() : impl(new Impl()) {
    this->impl->numBars = 100;
    float width = WINDOW_WIDTH / this->impl->numBars;
    float height = WINDOW_HEIGHT / this->impl->numBars;
    for (int i = 1; i <= this->impl->numBars; i++) {
        sf::Vector2f dim, pos;
        dim = {width, height * i};
        this->impl->bars.push_back(new Bar(dim));
    }
}

SortController::~SortController() {
    for (Bar *curBar : this->impl->bars) {
        delete curBar;
    }
}


void SortController::reset() {
    this->impl->insertionSortStep(true);
    this->impl->selectionSortStep(true);
    this->impl->bubbleSortStep(true);
    this->impl->scramble();
    this->impl->curState = SortController::State::NOT_SORTED;
    this->impl->curAlgorithm = SortController::Algo::NONE;
}

void SortController::update() {
    if (this->impl->curState == SortController::State::SORTED) {
        return;
    }
    switch (this->impl->curAlgorithm) {
        case(SortController::Algo::INSERTION):
            this->impl->insertionSortStep();
            break;
        case(SortController::Algo::BUBBLE):
            this->impl->bubbleSortStep();
            break;
        case(SortController::Algo::SELECTION):
            this->impl->selectionSortStep();
            break;
        default:
            LOG("ERROR: Selected algorithm not recognized.");
            break;
    }
}

void SortController::render(sf::RenderWindow* window) {
    float width = WINDOW_WIDTH / this->impl->numBars;
    sf::Vector2f pos = {-width, 0.0f};
    for (Bar *curBar : this->impl->bars) {
        pos.x += width;
        pos.y = WINDOW_HEIGHT - (curBar->getHeight());
        curBar->setPosition(pos);
        curBar->render(window);
    }
}

void SortController::setSortType(SortController::Algo type) {
    switch (type) {
        case(SortController::Algo::INSERTION):
            this->impl->curAlgorithm = type;
            std::cout << "Sorting with INSERTION!" << std::endl;
            break;
        case(SortController::Algo::BUBBLE):
            this->impl->curAlgorithm = type;
            std::cout << "Sorting with BUBBLE!" << std::endl;
            break;
        case(SortController::Algo::SELECTION):
            this->impl->curAlgorithm = type;
            std::cout << "Sorting with SELECTION!" << std::endl;
            break;
        default:
            LOG("ERROR: Unidentified sorting type selected.");
            break;
    }
    this->impl->curAlgorithm = type;
}

SortController::Algo SortController::getSortType() {
    return this->impl->curAlgorithm;
}