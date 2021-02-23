    #include "./GreedySolver.h"
#include <time.h>

SolverResult GreedySolver::Solve(vector<City> cities, int startIndex) {
    SolverResult solverResult;
    solverResult.permutationCount = 0;
    time_t startTime = clock();
    vector<City> newCities = vector<City>();
    newCities.push_back(cities.at((unsigned long long int) startIndex));

    auto citiesIterator = cities.begin() + startIndex;
    auto currentCity = *citiesIterator;
    cities.erase(citiesIterator);

    while (!cities.empty()) {
        City nearestCity = *cities.begin();
        auto nearestCityIterator = cities.begin();

        for (citiesIterator = cities.begin(); citiesIterator != cities.end(); citiesIterator++) {
            auto distanceToNearest = currentCity.location.GetDistanceTo(nearestCity.location);
            auto distanceToTemp = currentCity.location.GetDistanceTo(citiesIterator->location);

            if (distanceToNearest > distanceToTemp) {
                nearestCity = *citiesIterator;
                nearestCityIterator = citiesIterator;
                solverResult.permutationCount++;
            }
        }
        cities.erase(nearestCityIterator);
        newCities.push_back(nearestCity);
    }

    solverResult.result = newCities;
    solverResult.time = clock() - startTime;
    return solverResult;
}