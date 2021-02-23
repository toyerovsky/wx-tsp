#ifndef TRAVELINGSALESMANCPP_IPATHSOLVER_H
#define TRAVELINGSALESMANCPP_IPATHSOLVER_H

#include "City.h"
#include "SolverResult.h"
#include <vector>

/**
 * Interfejs bazowy do definiowania swoich implementacji wyznaczania cyklu hamiltona
 *
 * @class IPathSolver
 */
class IPathSolver {
public:
	/**
	 * Metoda wyznaczajaca cykl hamiltona
	 *
	 * @param cities vector miast
	 * @param startIndex zmienna przechowujaca index miasta, od ktorego nalezy zaczac
	 * @return
	 */
	virtual SolverResult Solve(vector<City> cities, int startIndex) = 0;
};

#endif //TRAVELINGSALESMANCPP_IPATHSOLVER_H