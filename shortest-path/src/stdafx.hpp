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

#define WINDOW_HEIGHT 700.0f
#define WINDOW_WIDTH  700.0f
#define DIM_X 51
#define DIM_Y 51

enum MouseState {HOVER, RIGHT_CLICK, LEFT_CLICK, RIGHT_HOLD, LEFT_HOLD};
enum {UP=0, RIGHT, DOWN, LEFT};

#if (NDEBUG)
    #define LOG(x) std::cout << x << std::endl;
#else
    #define LOG(x)
#endif

#endif