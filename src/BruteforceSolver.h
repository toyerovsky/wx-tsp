#ifndef TRAVELINGSALESMANCPP_BRUTEFORCESOLVER_H
#define TRAVELINGSALESMANCPP_BRUTEFORCESOLVER_H

#include "IPathSolver.h"

/**
 * Klasa odpowiedzialna za szukanie drogi metoda si³ow¹
 *
 * @class BruteforceSolver
 */
class BruteforceSolver : public IPathSolver {
public:
	/**
	 * Metoda rozpoczyna algorytm brute force, odpowiada za liczenie czasu oraz ilosci permutacji
	 *
	 * @param cities vector przechowujacy miasta
	 * @param startIndex zmienna przechowujaca index miasta, od ktorego nalezy zaczac
	 */
	SolverResult Solve(vector<City> cities, int startIndex) override;

private:
	/**
	 * Metoda rekurencyjna, sortuje tablice aby odleglosci miedzy miastami byly jak najmniejsze
	 *
	 * @param cities vector przechowujacy miasta
	 * @param startIndex zmienna przechowujaca index miasta, od ktorego nalezy zaczac
	 * @param i iterator miast
	 */
	void FindUsingBruteforce(vector<City> cities, int startIndex, int i);
};


#endif //TRAVELINGSALESMANCPP_BRUTEFORCESOLVER_H