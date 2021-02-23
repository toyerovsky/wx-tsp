#ifndef TRAVELINGSALESMANCPP_POINT_H
#define TRAVELINGSALESMANCPP_POINT_H

/**
 * Klasa opisujaca punkt na ekranie
 *
 * @class Point
 */
template<
	typename TNumeric, 
	typename = typename std::enable_if<std::is_arithmetic<TNumeric>::value, TNumeric>::type
>
class Point {
public:
	/**
	 * @field x wspolrzedna x
	 */
	TNumeric x;

	/**
	 * @field y wspolrzedna y
	 */
	TNumeric y;

	/**
	 * Klasa liczaca odleglosc do innego punktu na ekranie
	 *
	 * @param other punkt, do ktorego ma byc zmierzona odleglosc
	 * @return odleglosc do punktu
	 */
	double GetDistanceTo(Point other);
};

#endif //TRAVELINGSALESMANCPP_POINT_H