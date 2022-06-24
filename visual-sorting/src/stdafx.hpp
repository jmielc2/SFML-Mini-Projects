#pragma once

#ifndef STDAFX_H
#define STDAFX_H 1

#define DEBUG 0
#define WINDOW_HEIGHT 500.f
#define WINDOW_WIDTH 600.f

#if (DEBUG)
#define LOG(x) std::cout << x << std::endl
#else
#define LOG(x)
#endif

#include <iostream>
#include <memory>
#include <algorithm>
#include <string>
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>
#include "Components/App.hpp"

#endif