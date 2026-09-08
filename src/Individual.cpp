#include "Individual.h"

#include <algorithm>
#include <fmt/base.h>

static constexpr double energyDecreasedPerTickWorking = 5; //only needed in this file

///names may be misleading as it should be LOST not GAINED
static constexpr std::byte hungerGainedFromEatingPerTick = std::byte{25};//so is this
static constexpr std::byte thirstGainedFromDrinkingPerTick = std::byte{50};//so is this

//constexpr already implies inline since C++11, offering one function at every translation unit
constexpr int addTwoBytes(const std::byte& a, const std::byte& b) {
    // return static_cast<int>(a) + static_cast<int>(b);
    return std::to_integer<int>(a) + std::to_integer<int>(b);
}

constexpr int substractTwoBytes(const std::byte& a, const std::byte& b) {
    return std::to_integer<int>(a) - std::to_integer<int>(b);
}

///On scale of 0-100. Here, life satisfaction comes from having all needs met (hunger,thirst are 0)
int Individual::GetLifeSatisfaction() const {
    return static_cast<int>(100 * (addTwoBytes(currentHunger, currentThirst) / 200.f)); //currentHunger and currentThirst start at 100 and drain over time
}

void Individual::DecreaseStatsOnTick() {
    constexpr std::byte hungerDecrease{5}, thirstDecrease{0}; //ignore thirst for now

    this->currentHunger = static_cast<std::byte>(std::clamp(substractTwoBytes(this->currentHunger, hungerDecrease), 0, 100));
    this->currentThirst = static_cast<std::byte>(std::clamp(substractTwoBytes(this->currentThirst, thirstDecrease), 0, 100));
}

void Individual::PerformSelectedAction() {
    switch (nextAction) {
        case Work:
            this->nextProductProgress += job.productsPerTick;
            this->totalProductsInStored += static_cast<int>(nextProductProgress);
            this->nextProductProgress -= static_cast<int>(nextProductProgress);
            this->jobIncome = totalProductsInStored * jobPricePerProduct;
            this->energy -= energyDecreasedPerTickWorking;
            break;
        case Eat:
            this->currentHunger = static_cast<std::byte>(addTwoBytes(currentHunger, hungerGainedFromEatingPerTick));
            break;
        case Drink:
            this->currentHunger = static_cast<std::byte>(addTwoBytes(currentHunger, thirstGainedFromDrinkingPerTick));
            break;
        case Rest:
            this->energy += 2*energyDecreasedPerTickWorking;
            break;
    }
}

void Individual::DecideNextAction() {
    if (GetLifeSatisfaction() < std::clamp<int>(static_cast<int>(temper)*1.5f,20,100)) {
        if (static_cast<int>(currentHunger) < static_cast<int>(currentThirst))
        {
            nextAction = Drink;
            return;
        }

        nextAction = Eat;
        return;
    }

    if (energy > energyDecreasedPerTickWorking) {
        nextAction = Work;
        return;
    }

    nextAction = Rest;
}
