#pragma once
#include <cstddef>

#include "Race.h"

///Represents a purely social class f.e: wealthy, close to the king elites, normal citizens, hardworking slaves
class SocialClass {
public:
    Race dominantRace{};
    int averageIncome{};
    int averageClosenessToKing{};
    std::byte averageApprovalOfCurrentKing{}; ///How much does this social class approve king on average
};
