#pragma once
#include <cstddef>

static constexpr int numJobs = 6;

struct JobType {
    enum Jobs {
        King, Peacekeepers, Farmer, Unemployed, Student, Craftsman
    };

    ///Job type
    Jobs job;

    ///F.e peacekeepers do not offer any products
    bool jobOffersProducts;

    // int averageIncome{}; ///Income before taxation

    ///On scale of 0-100, percentage of income taken to the king
    std::byte taxationLevel{};

    ///E.g production cost MONTHLY. This is default price it should be calculated in ticks (f.e by average)
    double defaultPrice;

    JobType() = default;

    JobType(Jobs jobs, bool offersProducts, int taxationLevel, double defaultPrice) : job(jobs), jobOffersProducts(offersProducts), taxationLevel(std::byte(taxationLevel)), defaultPrice(defaultPrice) {}

};
