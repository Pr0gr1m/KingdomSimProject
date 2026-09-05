#include "Individual.h"

int addTwoBytes(const std::byte& a, const std::byte& b) {
    return static_cast<int>(a) + static_cast<int>(b);
}

///On scale of 0-100. Here, life satisfaction comes from having all needs met (hunger,thirst are 0)
int Individual::GetLifeSatisfaction() {
    return static_cast<int>(100 * (addTwoBytes(currentHunger, currentThirst) / 200.f)); //currentHunger and currentThirst start at 100 and drain over time
}
