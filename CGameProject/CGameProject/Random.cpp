#include "Random.h"

int Random::Randint(size_t start, size_t end)
{
    if (start > end)
        throw std::logic_error("Logic Error: start > end");

    if (start > static_cast<size_t>(INT_MAX) || end > static_cast<size_t>(INT_MAX))
        throw std::out_of_range("Range too big for int");

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(static_cast<int>(start), static_cast<int>(end));
    return dist(gen);
}