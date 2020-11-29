#ifndef BUSCA_H_INCLUDED
#define BUSCA_H_INCLUDED

#pragma once
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <sstream>
#include "Class_Point.h"
#include "Arestas.h"
#include <list>
#include <map>
#include "json.hpp"

using json = nlohmann::ordered_json;
using namespace std;

class Busca
{
private:
	int ptsRota;
	int nvert;
	Arestas* arestas[1000];
	Point* vertices[1000];
	Point* rota[1000];
	bool loop;
	int timeout;
	double dist;
	double ymax;


public:
	Busca() { };
	Busca(int v, double d) : nvert(v), dist(d) {}

	enum objetos { pessoa, objeto, obstaculo };

	void setyMax(double k);
	void setDist(double d);
	void setVertices(int vert);
	void setRepeticao(bool rept);
	void setNumVert(int vert);
	void getVert();
	json getVertJson(); //Pedro quem colocou aqui
	void setVertsFromJson(json j); //Pedro quem colocou aqui
	void setPtsRota(int p);
	void setTempo(int tempo);
	void setListaVertices(double x, double y, int i);
	//void setObjetos(elementos obj);

	int getPtsRota();
	int getNumVertices();
	double getDist();
	double getyMax();
	string getVerticesString(int aux);

	void setArestas();

	void iniciarPol(int v, int tempo, bool rept);

	void iniciarBusca(int met, Busca::objetos o, double d);

	void pontosDaRota();

};

#endif // BUSCA_H_INCLUDED
