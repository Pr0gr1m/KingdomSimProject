#include "Kingdom.h"


//With template classes you CANNOT have their function definisions in .cpp file
//because compile will compile main.cpp without ever seening the function body
//(basically if this.cpp file will not instantiate Kingdom<100> no code is generated)??

// template<int N>
// void Kingdom<N>::DisplayToConsole() {
//     fmt::print("Kingdom {}x{}:",Width,Height);
//     fmt::print("\n\tTotal population: {}",populationTotal);
//     fmt::print("\n\tTotal ongoing strikes: {}", numOngoingStrikes);
//
//     std::map<JobType::Jobs, int> numOfJobsInKingdom;
//     std::map<JobType::Jobs, double> totalIncomePerJobs;
//     std::map<JobType::Jobs, double> totalPricesPerProduct;
//
//     for (int i = 0; i < populationTotal; i += 1) {
//         Individual& individual = individuals[i];
//         numOfJobsInKingdom[individual.job.job]++;
//         totalIncomePerJobs[individual.job.job] += individual.jobIncome;
//         totalPricesPerProduct[individual.job.job] += (individual.job.jobOffersProducts?individual.jobPricePerProduct:0);
//     }
//
//     fmt::print("\n\tNum of employees by job.");
//     for (int i = 0; i < numJobs; i += 1) {
//         auto jobIndex = static_cast<JobType::Jobs>(i);
//         size_t numJobInKingdom = numOfJobsInKingdom[jobIndex];
//         double totalIncome = totalIncomePerJobs[jobIndex];
//         double totalPricePerProduct = totalPricesPerProduct[jobIndex];
//
//         totalIncome = totalIncome!=0?totalIncome/numJobInKingdom : 0;
//         totalPricePerProduct = totalPricePerProduct!=0?totalPricePerProduct/numJobInKingdom:0;
//
//         fmt::print("\n\t\tFor job {} there are {} employees with an average income of {:.4f} and average price product of {:.4f}", i, numJobInKingdom, totalIncome, totalPricePerProduct);// (totalIncome / numJobInKingdom));
//     }
// }
//
// template<int N>
// void Kingdom<N>::StartStrike(Strike *strike) {
//     ongoingStrikes[numOngoingStrikes++] = strike;
// }
//
// template<int N>
// void Kingdom<N>::EndStrike(Strike *strike) {
//     delete strike;
//     ongoingStrikes[numOngoingStrikes--] = nullptr;
// }
//
// template<int N>
// void Kingdom<N>::Tick() {
//     //1 Decrease every individual decreasing stats
//     for (int i = 0; i < populationTotal; i += 1) {
//         Individual& individual = individuals[i];
//         individual.DecreaseStatsOnTick();
//         int individualLifeSatisfaction = individual.GetLifeSatisfaction();
//
//         if (individualLifeSatisfaction > static_cast<int>(individual.eagernessToFight)) {
//             fmt::print("Individual {} will start a local outbreak.", individual.IdentificationNumber);
//         }
//         else if (individualLifeSatisfaction > static_cast<int>(individual.temper)) {
//             fmt::print("Individual {} will start supporting local outbreaks.", individual.IdentificationNumber);
//         }
//     }
// }
// template<int N>
// void Kingdom<N>::DisplayToConsole() {
//     fmt::print("Kingdom {}x{}:",Width,Height);
//     fmt::print("\n\tTotal population: {}",populationTotal);
//     fmt::print("\n\tTotal ongoing strikes: {}", numOngoingStrikes);
//
//     std::map<JobType::Jobs, int> numOfJobsInKingdom;
//     std::map<JobType::Jobs, double> totalIncomePerJobs;
//     std::map<JobType::Jobs, double> totalPricesPerProduct;
//
//     for (int i = 0; i < populationTotal; i += 1) {
//         Individual& individual = individuals[i];
//         numOfJobsInKingdom[individual.job.job]++;
//         totalIncomePerJobs[individual.job.job] += individual.jobIncome;
//         totalPricesPerProduct[individual.job.job] += (individual.job.jobOffersProducts?individual.jobPricePerProduct:0);
//     }
//
//     fmt::print("\n\tNum of employees by job.");
//     for (int i = 0; i < numJobs; i += 1) {
//         auto jobIndex = static_cast<JobType::Jobs>(i);
//         size_t numJobInKingdom = numOfJobsInKingdom[jobIndex];
//         double totalIncome = totalIncomePerJobs[jobIndex];
//         double totalPricePerProduct = totalPricesPerProduct[jobIndex];
//
//         totalIncome = totalIncome!=0?totalIncome/numJobInKingdom : 0;
//         totalPricePerProduct = totalPricePerProduct!=0?totalPricePerProduct/numJobInKingdom:0;
//
//         fmt::print("\n\t\tFor job {} there are {} employees with an average income of {:.4f} and average price product of {:.4f}", i, numJobInKingdom, totalIncome, totalPricePerProduct);// (totalIncome / numJobInKingdom));
//     }
// }
