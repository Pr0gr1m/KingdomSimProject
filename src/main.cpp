#include <iostream>
#include <random>
#include <algorithm>
#include <cmath>

#include "Individual.h"
#include "Kingdom.h"

constexpr auto startingPopulation = 100; //include king

int main() {
    std::random_device rd{};
    std::mt19937 randomGenerator{rd()}; //TODO: research more about whatever mt19937 is

    Individual individuals[startingPopulation];

    JobType kingJobType{JobType::King, false, 0, 0};
    JobType farmerJobType{JobType::Farmer, true, 12, 2.20};
    JobType studentJobType{JobType::Student, false, 0, 0};
    JobType craftsmanJobType{JobType::Craftsman, true, 8, 8.50};

    Individual king{White, 0, std::byte{50}, std::byte{100}, std::byte{0},
        std::byte{0}, std::byte{100}, kingJobType, 1000};
    king.currentHunger = std::byte{100};
    king.currentThirst = std::byte{100};
    king.closenessToClosestSocialClass = std::byte{100};
    king.jobIncome = 0; //i guess kings income comes from taxation, calculated in ticks
    king.jobNetIncome = 0;
    king.jobPricePerProduct = 0;
    individuals[0] = king;

    Race dominantkingdomRace = White;
    double chanceForOtherRace = 3.0;

    //Normal distribution for race that s centered around dominant race
    std::normal_distribution<double> raceDistribution{static_cast<double>(dominantkingdomRace), chanceForOtherRace};
    std::normal_distribution<double> ageDistribution(35.0, 15.0);
    //General distribution for general stats
    std::normal_distribution<double> generalDist(50.0, 25.0);

    std::uniform_int_distribution<int> jobChoiceDist(0, 2);
    std::normal_distribution<double> jobPricePerProductMultiplier(1, 0.175f); //TODO: find out why it tends to go below 1 (slightly)

    JobType allowedRandomJobs[] = {farmerJobType, studentJobType, craftsmanJobType};

    for (int i = 1; i < startingPopulation; i += 1) {
        int raceVal = std::abs(static_cast<int>(std::round(raceDistribution(randomGenerator)))) % numRaces;
        Race race = static_cast<Race>(raceVal);

        int ageVal = std::clamp(static_cast<int>(std::round(ageDistribution(randomGenerator))), 0, 120);
        int closenessToKingVal = std::clamp(static_cast<int>(std::round(generalDist(randomGenerator))), 0, 100);
        int temperVal = std::clamp(static_cast<int>(std::round(generalDist(randomGenerator))), 0, 100);
        int eagernessVal = std::clamp(static_cast<int>(std::round(generalDist(randomGenerator))), 0, 100);
        int approvalVal = std::clamp(static_cast<int>(std::round(generalDist(randomGenerator))), 0, 100);

        JobType job = allowedRandomJobs[jobChoiceDist(randomGenerator)];
        int startingWorth = 0;

        Individual randomInd{race, i, static_cast<std::byte>(ageVal), static_cast<std::byte>(closenessToKingVal),
            static_cast<std::byte>(temperVal), static_cast<std::byte>(eagernessVal),
            static_cast<std::byte>(approvalVal), job, startingWorth};

        randomInd.currentHunger = static_cast<std::byte>(std::clamp(static_cast<int>(std::round(generalDist(randomGenerator))), 25, 100));
        randomInd.currentThirst = static_cast<std::byte>(std::clamp(static_cast<int>(std::round(generalDist(randomGenerator))), 25, 100));
        randomInd.closenessToClosestSocialClass = static_cast<std::byte>(std::clamp(static_cast<int>(std::round(generalDist(randomGenerator))), 0, 100));

        randomInd.jobPricePerProduct = jobPricePerProductMultiplier(randomGenerator) * job.defaultPrice;

        individuals[i] = randomInd;

        fmt::print("Ind {}: Race={}, Age={}, Hunger={}, Thirst={}, Satisfaction={}\n", i, (int)race, ageVal, (int)randomInd.currentHunger, (int) randomInd.currentThirst, (int)randomInd.GetLifeSatisfaction());
    }

    std::cout << std::endl;
    Kingdom<startingPopulation> kingdom{100,100,startingPopulation, &individuals[0]};
    kingdom.DisplayToConsole();
}
