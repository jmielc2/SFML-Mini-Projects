#ifndef CORE_HPP
#define CORE_HPP 1
#define DEBUG 0

#if (DEBUG)
    #include <iostream>
    #define LOG(x) if (DEBUG) std::cerr << x << std::endl
#else
    #define LOG(X)
#endif

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800

#include <algorithm>
#include <cmath>
#include <stack>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#endif