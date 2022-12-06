#pragma once

#ifndef STDAFX_H
#define STDAFX_H 1

#include <string>
#include <limits>
#include <vector>
#include <stack>
#include <set>
#include <queue>
#include <functional>
#include <fstream>
#include <iostream>
#include <time.h>
#include <random>
#include <SFML/Graphics.hpp>

#define WINDOW_HEIGHT 700
#define WINDOW_WIDTH  700
#define DIM_X 20
#define DIM_Y 20
enum MouseState {HOVER, RIGHT_CLICK, LEFT_CLICK, RIGHT_HOLD, LEFT_HOLD};
enum {UP=0, RIGHT, DOWN, LEFT, UP_RIGHT, UP_LEFT, DOWN_RIGHT, DOWN_LEFT};

#if (DEBUG)
    #define LOG(x) std::cout << x << std::endl;
#else
    #define LOG(x)
#endif

#endif