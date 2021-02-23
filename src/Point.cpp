#include <cmath>
#include "./Point.h"

double Point<int>::GetDistanceTo(Point<int> other) {
	return sqrt(pow(other.x - x, 2) + pow(other.y - y, 2));
}