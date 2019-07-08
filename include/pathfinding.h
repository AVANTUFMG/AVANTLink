#ifndef PATHFINDING_H_INCLUDED
#define PATHFINDING_H_INCLUDED
#include "Point.h"

//recebe a latitude longitude e altura do drone e do destino:
vector <Point> pathfinding_test(double lat_drone, double lon_drone, double h_drone, double lat_dest, double lon_dest, double h_dest, int q_obs); // return next point to go (MAS AINDA NAO FUNCIONA EM PROCESSO...)


vector <Point> search_path(const Malha &M, double lat_dest, double lon_dest, double h_dest); //ver com tacito
vector <Point> pathfinding_real(double lat_drone, double lon_drone, double h_drone); //ver com Tacito

//ADicionei as variaveis de coordenadas limites dentro de obstaculo
//K começa em -K

/*Observaçoes e bugs conhecidos:
>Caso um ponto estiver fora da área da malha, o programa buga, entra em loop se esse ponto for o objetivo
>A malha sempre considera o primeiro ponto procurado (ponto a esquerda do drone) como viável
>Para adicionar um obstáculo tem de colocar ainda dentro da funcao search_path
>O erro do pathfinding é de 8 metros, ainda temos que ajustar
>Se criar um obstaculo em cima do drone, ou do objetivo buga
>a malha cria valores para altura negatvia
>Pathfinding buga para destino com  altura maxima
*/

#endif // PATHFINDING_H_INCLUDED
