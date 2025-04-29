#pragma once
#pragma once
#include <random>

class Random
{
    std::mt19937 engine;

public:
    Random();

    int Range(int min, int max);

    std::mt19937& GetEngine();

    int operator()(int min, int max);
};

