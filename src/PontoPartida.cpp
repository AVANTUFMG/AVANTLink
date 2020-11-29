#include "PontoPartida.h"


PontoPartida::PontoPartida()
{

}

PontoPartida::PontoPartida(double lat, double lon)
{

	setInitialPoint(Point(lat, lon, 0));

}

void PontoPartida::setApproxPoint(double lat, double lon, double h)
{
	setApproxPoint(Point(lat, lon, h));
}

