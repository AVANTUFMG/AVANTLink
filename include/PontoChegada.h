#pragma once
#include "Class_Point.h"


class PontoChegada
{
private:
	Point lastPoint;
	Point approxPoint;

public:

	PontoChegada();
	PontoChegada(double lat, double lon);

	
	void setApproxPoint(double lat, double lon, double h);

	Point getLastPoint() { return lastPoint; };
	Point getApproxPoint() { return approxPoint; };

	void setLastPoint(Point point) { lastPoint = point; }
	void setApproxPoint(Point point) { approxPoint = point; }

};

