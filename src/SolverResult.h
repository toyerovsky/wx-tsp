#ifndef TRAVELINGSALESMANCPP_SOLVERRESULT_H
#define TRAVELINGSALESMANCPP_SOLVERRESULT_H

#include <vector>
#include "City.h"

using namespace std;

/**
 * Struktura opisujaca wynik dzialania algorytmow szukajacych drogi
 */
struct SolverResult {
public:
	/**
	 * @field result przechowuje vector uporzadkowanych miast
	 */
	vector<City> result;

	/**
	 * @field time przechowuje czas dzialania algorytmu
	 */
	time_t time;

	/**
	 * @field permutationCount przechowuje iloœæ permutacji
	 */
	unsigned long long int permutationCount;
};


#endif //TRAVELINGSALESMANCPP_SOLVERRESULT_H