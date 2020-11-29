#ifndef PATHFINDING_OUTPUT_H_INCLUDED
#define PATHFINDING_OUTPUT_H_INCLUDED
#include "Point_output.h"

//recebe a latitude longitude e altura do drone e do destino e tbm quantidade de obstasculos:
vector <Point_O> pathfinding_2D(double lat_drone, double lon_drone, double h_drone, double lat_dest, double lon_dest, double h_dest, int q_obs); // return next Point_O to go
vector <Point_O> pathfinding_3D(double lat_drone, double lon_drone, double h_drone, double lat_dest, double lon_dest, double h_dest, int q_obs);

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
//vector <Point_O> pathfinding_test(double lat_drone, double lon_drone, double h_drone, double lat_dest, double lon_dest, double h_dest, int q_obs);
//vector <Point_O> search_path(const Malha &M, double lat_dest, double lon_dest, double h_dest);
//vector <Point_O> pathfinding_real(double lat_drone, double lon_drone, double h_drone);
