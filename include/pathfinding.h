#ifndef PATHFINDING_H_INCLUDED
#define PATHFINDING_H_INCLUDED
#include "Point.h"

//recebe a latitude longitude e altura do drone e do destino:
vector <Point> search_path(double lat_drone, double lon_drone, double h_drone, double lat_dest, double lon_dest, double h_dest); // return next point to go (MAS AINDA NAO FUNCIONA EM PROCESSO...)


/*Observaçoes e bugs conhecidos:
>Caso um ponto estiver fora da área da malha, o programa buga, entra em loop se esse ponto for o objetivo
>A malha sempre considera o primeiro ponto procurado (ponto a esquerda do drone) como viável
>Para adicionar um obstáculo tem de colocar ainda dentro da funcao search_path
>O erro do pathfinding é de 8 metros, ainda temos que ajustar
>Arthur esta trabalhando para calcular com todos pontos vizinhos do drone e nao só 6
*/

#endif // PATHFINDING_H_INCLUDED
