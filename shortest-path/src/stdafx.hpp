#pragma once

#ifndef STDAFX_H
#define STDAFX_H 1

#include <string>
#include <limits>
#include <vector>
#include <queue>
#include <functional>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>

#define DEBUG 0
#define WINDOW_HEIGHT 700
#define WINDOW_WIDTH  700
#define DIM_X 25
#define DIM_Y 25
enum MouseState {HOVER, RIGHT_CLICK, LEFT_CLICK, RIGHT_HOLD, LEFT_HOLD};

#if (DEBUG)
    #define LOG(x) std::cout << x << std::endl;
#else
    #define LOG(x)
#endif

#endif