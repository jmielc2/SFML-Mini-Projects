#pragma once

#ifndef MG_ALGORITHM
#define MG_ALGORITHM 1

#include "../stdafx.hpp"
#include "../Components/Node.hpp"

class MG_Algorithm {
public:
    template <typename E> static void generateMaze(E* start, const std::vector<E*> &grid);
};

//////////////////////////////////////////////

template <typename E> void MG_Algorithm::generateMaze(E* start, const std::vector<E*> &grid) {
    LOG("Generating maze...");
}

#endif