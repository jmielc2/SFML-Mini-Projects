#pragma once

#ifndef STDAFX_H
#define STDAFX_H 1

#include <memory>
#include <string>
#include <SFML/graphics.hpp>

#define DEBUG 1
#define WINDOW_HEIGHT 800.f
#define WINDOW_WIDTH  800.f

#if (DEBUG)
    #include <iostream>
    #define LOG(x) std::cout << x << std::endl;
#else
    #define LOG(x)
#endif

#endif