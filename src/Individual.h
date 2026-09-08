#pragma once

#include <cstddef>

#include "JobType.h"
#include "Race.h"
#include "SocialClass.h"

enum IndividualAction {
    Work, Eat, Drink, Rest //Work default state unless its work hours
};

///Class representing an individual
class Individual {
//private:
    //std::byte lifeSatisfaction{}; ///On scale of 0-100. Here, life satisfaction comes from having all needs met (hunger,thirst are 0)
public:
    ///Race of the individual
    Race race{};

    ///Alternative to names
    int IdentificationNumber{};
    std::byte age{};

    ///On scale of 0-100, higher scale means f.e more food and privelages.
    std::byte closenessToKing{0};

    ///On scale of 0-100. Starting at 100, decreases by an amount hourly
    std::byte currentHunger{100}, currentThirst{100};

    ///On scale of 0-100. Threshold of life satisfaction until individual starts locally supporting ongoing strikes
    std::byte temper{};
    std::byte eagernessToFight{}; ///On scale of 0-100. Threshold of life satisfaction until individual starts participating in strikes
    std::byte approvalOfKing{}; ///On scale of 0-100 Approval of king.

    JobType job{};

    ///Before taxation
    double jobIncome{};

    ///After taxation, what an individual takes on monthly basis
    double jobNetIncome{};
    double worth{};

    int totalProductsInStored;
    double nextProductProgress;

    ///0-100 range. Decreased when working, increased when resting
    double energy{};

    ///Does not work for f.e peacekeepers or king, selling price of the product
    double jobPricePerProduct{};

    ///Closest social class that the individaul identifies with
    SocialClass closestSocialClass;

    ///On scale of 0-100. Individual is more eager to fight on side of their own social class
    std::byte closenessToClosestSocialClass{};

    IndividualAction nextAction{Rest};

    Individual() = default;

    Individual(Race race, int ID, std::byte age, std::byte closenessToKing, std::byte temper, std::byte eagernessToFight, std::byte approvalOfKing, JobType jobType,
        int startingWorth) {
        this->race = race;
        this->IdentificationNumber = ID;
        this->age = age;
        this->closenessToKing = closenessToKing;
        this->temper = temper;
        this->eagernessToFight = eagernessToFight;
        this->approvalOfKing = approvalOfKing;
        this->job = jobType;
        this->worth = startingWorth;
    }

    [[nodiscard]] int GetLifeSatisfaction() const;

    void DecreaseStatsOnTick();

    void PerformSelectedAction();

    void DecideNextAction();
};
