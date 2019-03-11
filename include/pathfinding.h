#ifndef PATHFINDING_H_INCLUDED
#define PATHFINDING_H_INCLUDED
#include "Point.h"

//recebe a latitude longitude e altura do drone e do destino:
Point search_path(double lat_drone, double lon_drone, double h_drone, double lat_dest, double lon_dest, double h_dest); // return next point to go (MAS AINDA NAO FUNCIONA EM PROCESSO...)
//ainda nao funciona colocar um obstaculo nessa malha que a funcao cria diretamente mas a funcao que adiciona obstaculo
//em alguma malha é a add_obs no point.h

#endif // PATHFINDING_H_INCLUDED
