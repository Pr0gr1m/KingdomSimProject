#pragma once

#include <cstddef>
#include <iostream>
#include <map>
#include <fmt/base.h>

#include "Individual.h"
#include "Strike.h"

inline constexpr int maxOngoingStrikes = 5;
static constexpr int taxationPercantage = 12;

template<int N>
class Kingdom {
public:
    std::size_t Width,Height;

    std::size_t populationTotal;

    Individual* individuals;
    Individual* king{nullptr};

    int numOngoingStrikes = 0;
    Strike* ongoingStrikes[maxOngoingStrikes]{};

    Kingdom(size_t width, size_t height, size_t currentPopulationTotal, Individual* individuals) : Width(width), Height(height), populationTotal(currentPopulationTotal) {
        this->individuals = individuals;

        if (currentPopulationTotal <= 0) {
            king = individuals;
        }
    }

    void DisplayToConsole();

    void StartStrike(Strike* strike);
    void EndStrike(Strike* strike);

    void Tick();

    void DisplayEveryIndividual();

    void CollectTaxes();
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
        const Individual& individual = individuals[i];
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

        if (numJobInKingdom!=0) fmt::print("\n\t\tFor job {} there are {} employees with an average income of {:.4f} and average price product of {:.4f}", i, numJobInKingdom, totalIncome, totalPricePerProduct);// (totalIncome / numJobInKingdom));
    }

    fmt::print("\n"); //could of just used std::cout
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

template<int N>
void Kingdom<N>::Tick() {
    //1 Decrease every individual decreasing stats
    for (int i = 0; i < populationTotal; i += 1) {
        Individual& individual = individuals[i];

        individual.DecideNextAction();
        individual.PerformSelectedAction();
        individual.DecreaseStatsOnTick();

        int individualLifeSatisfaction = individual.GetLifeSatisfaction();

        if (individualLifeSatisfaction < static_cast<int>(individual.eagernessToFight)) {
            fmt::print("\n\tIndividual {} will start a local outbreak because of poor LS: {} (< {}).", individual.IdentificationNumber, individual.GetLifeSatisfaction(), static_cast<int>(individual.eagernessToFight));
        }
        else if (individualLifeSatisfaction < static_cast<int>(individual.temper)) {
            fmt::print("\n\tIndividual {} will start supporting local outbreaks because of poor LS: {} (< {}).", individual.IdentificationNumber, individual.GetLifeSatisfaction(), static_cast<int>(individual.temper));
        } else {
            //fmt::print("\n\t\t{} / {}", individualLifeSatisfaction, std::to_integer<int>(individual.temper));
        }
    }
}

template<int N>
void Kingdom<N>::DisplayEveryIndividual() {
    for (int i = 0; i < populationTotal; i += 1) {
        const Individual& individual = individuals[i];
        fmt::print("\nIndividual {} is going to do {}", individual.IdentificationNumber, static_cast<int>(individual.nextAction));
        fmt::print("\n\tHunger {} Thirst {} Energy {} Satisfaction {}", std::to_integer<int>(individual.currentHunger), std::to_integer<int>(individual.currentThirst), individual.energy,individual.GetLifeSatisfaction());
        fmt::print("\n\tWorth {:.2f}, job income {:.2f}", individual.worth, individual.jobIncome);
    }

    std::cout << "\n";
    std::flush(std::cout);
}

template<int N>
void Kingdom<N>::CollectTaxes() {
    double taxationTotal{};

    for (int i = 0; i< populationTotal; i += 1) {
        Individual& individual = individuals[i];

        double tax = (individual.jobIncome)*(1-(taxationPercantage/100.0));
        taxationTotal += tax;
        individual.jobIncome -= tax;
    }

    fmt::print("\nTaxes collected: {}\n", taxationTotal);

    if (king != nullptr) king->jobIncome += taxationTotal;
}
