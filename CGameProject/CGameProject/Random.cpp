#include "Random.h"

int Random::randint(int start, int end)
{
	if (start > end)
		throw "Logic Error";
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(start, end);
	return dist(gen);
}