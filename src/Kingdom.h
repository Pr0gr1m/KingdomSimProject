#pragma once

#include <cstddef>
#include <iostream>
#include <map>

#include "Individual.h"
#include "Strike.h"

static constexpr int maxOngoingStrikes = 5;

template<int N>
class Kingdom {
public:
    std::size_t Width,Height;

    std::size_t populationTotal;

    Individual* individuals;

    int numOngoingStrikes = 0;
    Strike* ongoingStrikes[maxOngoingStrikes]{};

    Kingdom(size_t width, size_t height, size_t currentPopulationTotal, Individual* individuals) : Width(width), Height(height), populationTotal(currentPopulationTotal) {
        this->individuals = individuals;
    }

    void DisplayToConsole();

    void StartStrike(Strike* strike);
    void EndStrike(Strike* strike);
};

template<int N>
void Kingdom<N>::DisplayToConsole() {
    fmt::print("Kingdom {}x{}:",Width,Height);
    fmt::print("\n\tTotal population: {}",populationTotal);
    fmt::print("\n\tTotal ongoing strikes: {}", numOngoingStrikes);

    std::map<JobType::Jobs, int> numOfJobsInKingdom;
    std::map<JobType::Jobs, double> totalIncomePerJobs;
    std::map<JobType::Jobs, double> totalPricesPerProduct;

    for (int i = 0; i < populationTotal; i += 1) {
        Individual individual = *(individuals+i);
        numOfJobsInKingdom[individual.job.job]++;
        totalIncomePerJobs[individual.job.job] += individual.jobIncome;
        totalPricesPerProduct[individual.job.job] += (individual.job.jobOffersProducts?individual.jobPricePerProduct:0);
    }

    fmt::print("\n\tNum of employees by job.");
    for (int i = 0; i < numJobs; i += 1) {
        auto jobIndex = static_cast<JobType::Jobs>(i);
        size_t numJobInKingdom = numOfJobsInKingdom[jobIndex];
        double totalIncome = totalIncomePerJobs[jobIndex];
        double totalPricePerProduct = totalPricesPerProduct[jobIndex];

        totalIncome = totalIncome!=0?totalIncome/numJobInKingdom : 0;
        totalPricePerProduct = totalPricePerProduct!=0?totalPricePerProduct/numJobInKingdom:0;

        fmt::print("\n\t\tFor job {} there are {} employees with an average of {} income and average price product of {:.4f}", i, numJobInKingdom, totalIncome, totalPricePerProduct);// (totalIncome / numJobInKingdom));
    }
}

template<int N>
void Kingdom<N>::StartStrike(Strike *strike) {
    ongoingStrikes[numOngoingStrikes++] = strike;
}

template<int N>
void Kingdom<N>::EndStrike(Strike *strike) {
    delete strike;
    ongoingStrikes[numOngoingStrikes--] = nullptr;
}
