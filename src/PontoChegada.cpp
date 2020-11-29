#include "PontoChegada.h"


PontoChegada::PontoChegada()
{

}

PontoChegada::PontoChegada(double lat, double lon)
{

	setLastPoint(Point(lat, lon, 0));
	
}

void PontoChegada::setApproxPoint(double lat, double lon, double h)
{
	setApproxPoint(Point(lat, lon, h));
}
