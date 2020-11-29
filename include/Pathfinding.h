#ifndef PATHFINDING_H_INCLUDED
#define PATHFINDING_H_INCLUDED

#include "Class_Malha.h"
#include "Class_Point.h"
#include "Class_Obstacle.h"
#include "Global_Functions.h"

using namespace std;

//recebe a latitude longitude e altura do drone e do destino:
vector <Point> pathfinding_Astar(double lat_drone, double lon_drone, double h_drone, double lat_dest, double lon_dest, double h_dest, int q_obs); // return next point to go (MAS AINDA NAO FUNCIONA EM PROCESSO...)

//vector <Point> search_path(const Malha &M, double lat_dest, double lon_dest, double h_dest);
//vector <Point> pathfinding_real(double lat_drone, double lon_drone, double h_drone);
#endif // PATHFINDING_H_INCLUDED


/*Observaçoes e bugs conhecidos:
>Caso um ponto estiver fora da área da malha, o programa buga, entra em loop se esse ponto for o objetivo
>Para adicionar um obstáculo tem de colocar ainda dentro da funcao search_path
>O erro do pathfinding é de 8 metros
>Se criar um obstaculo em cima do drone, ou do objetivo buga
>a malha cria valores para altura negatvia
>Pathfinding buga para destino com  altura maxima (já consertado esses bugs no Djkstra)
>Pode entrar em loop em certos casos (não cabe explicar aqui)
*/


//outras funcoes que podem vir a serem usadas no futuro, por enquanto nada-----------------------------------------
//vector <Point> pathfinding_test(double lat_drone, double lon_drone, double h_drone, double lat_dest, double lon_dest, double h_dest, int q_obs);
//vector <Point> search_path(const Malha &M, double lat_dest, double lon_dest, double h_dest);
//vector <Point> pathfinding_real(double lat_drone, double lon_drone, double h_drone);
