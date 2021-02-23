#ifndef TRAVELINGSALESMANCPP_GREEDYSOLVER_H
#define TRAVELINGSALESMANCPP_GREEDYSOLVER_H

#include "IPathSolver.h"

/**
 * Klasa odpowiedzialna za szukanie drogi metoda Greedy
 *
 * @class GreedySolver
 */
class GreedySolver : public IPathSolver {
public:
	/**
	 * Metoda sortuje vector
	 *
	 * @param cities
	 * @param startIndex
	 * @return
	 */
	SolverResult Solve(vector<City> cities, int startIndex) override;
};


#endif //TRAVELINGSALESMANCPP_GREEDYSOLVER_H