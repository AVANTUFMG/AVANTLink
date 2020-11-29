#pragma once
#include "Class_Point.h"


class PontoPartida
{
private:
	Point initialPoint;
	Point approxPoint;

public:

	PontoPartida();
	PontoPartida(double lat, double lon);


	void setApproxPoint(double lat, double lon, double h);

	Point getInitialPoint() { return initialPoint; };
	Point getApproxPoint() { return approxPoint; };

	void setInitialPoint(Point point) { initialPoint = point; }
	void setApproxPoint(Point point) { approxPoint = point; }

	
};

