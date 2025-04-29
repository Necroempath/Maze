#include "Random.h"

Random::Random()
{
	std::random_device random;
	engine = std::mt19937(random());
}

int Random::Range(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(engine);
}

std::mt19937& Random::GetEngine()
{
	return engine;
}

int Random::operator()(int min, int max)
{
	return Range(min, max);
}