#include <limits>
#include "./BruteforceSolver.h"
#include <cmath>
#include <time.h>


vector<City> currentMinVector = vector<City>();
double minLength = numeric_limits<double>::infinity();

SolverResult BruteforceSolver::Solve(vector<City> cities, int startIndex) {
    SolverResult solverResult;
    time_t startTime = clock();
    FindUsingBruteforce(cities, startIndex, 0);
    solverResult.result = currentMinVector;
    solverResult.time = clock() - startTime;
    solverResult.permutationCount = (unsigned long long int) pow((double)cities.size(), (double)cities.size());

    return solverResult;
}

void BruteforceSolver::FindUsingBruteforce(vector<City> cities, int startIndex, int i) {
    if (currentMinVector.empty()) {
        swap(cities[0], cities[startIndex]);
    }

    if (i == cities.size()) {
        double lenght = 0.0;
        for (int j = 0; j < cities.size() - 1; ++j)
            lenght += cities[j].location.GetDistanceTo(cities[j + 1].location);

        if (lenght < minLength) {
            currentMinVector = cities;
            minLength = lenght;
        }
        return;
    }

    for (int j = i; j < cities.size(); ++j) {
        swap(cities[i], cities[j]);
        FindUsingBruteforce(cities, startIndex, i + 1);
        swap(cities[i], cities[j]);
    }
}