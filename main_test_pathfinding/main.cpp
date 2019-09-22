#include <iostream>
#include "pathfinding.h"
#include <cmath>
using namespace std;

//funcoes para converter valores X e Y em metros para coordenadas no plano cartesiano da malha
double conversor_X(double lat_drone, int X){
double x_coord = lat_drone + X*0.000009;
return x_coord;
}
double conversor_Y(double lon_drone, int Y){
double y_coord = lon_drone + Y*0.000009;
return y_coord;
}

int main()
{
    //------ PARTE DO MAIN DE TESTE PARA PATHFINDING PRECISÃO DE +-8 METROS------ //
    cout.precision(10); //apenas aumentando a precisao do cout

    /*
    Sobre a malha default: *DESATUALIZADA PEDIR A CONTI PRA ATUALIZAR SE NECESSÁRIO*
    O tamanho da malha é definido em Point.cpp pelos valores de N_lat, N_lon e N_H
    A malha default colocamos N_lat = 10, N_lon = 10, N_H = 4, e terá (10*2 + 1)*(10*2 + 1)*(4*2 + 1) = 3969 pontos que formam a malha
    O espaçamento entre cada pontos é 15 metros, logo a malha em 2D corresponde à (10*2 + 1)*15*(10*2 + 1)*15 = 99225 m²
    Em 3D: 99225*(4*2 + 1)*15 = 13395375 m³
    Nesse caso, 315 m de largura, 315 m de comprimento e 135 m  de altura
    Válido lembrar que o drone, está sempre no centro desse paralelepípedo
    */


    //Mude para os valores desejados
    //Os valores X,Y,Z do drone sao sempre 0,0,0
    double latitude_drone = -19.871875;
    double longitude_drone = -43.970220;
    double altura_drone = 60;

    //insira os valores desejados de x,y em metros sendo que -600 < x,y < 600. Insira também a quantidade de obstáculos desejados
    int x_metros = 400;
    int y_metros = 400;
    int quantidade_obstaculo = 4;

    //--------------------------------------------------------------------------------------------------------------------------

    double latitude_destino = conversor_X(latitude_drone, x_metros); // Essa latitude equivale ao X = 600, Extremo "esquerdo"
    double longitude_destino = conversor_Y(longitude_drone, y_metros); // Essa longitude equivale ao Y = 600, Extrema "cima"
    double altura_destino = 60; // Não mude a altura, já que está testando apenas 2D

     vector <Point> N = pathfinding_2D(latitude_drone, longitude_drone, altura_drone, latitude_destino, longitude_destino, altura_destino, quantidade_obstaculo);
    //vector <Point> N = pathfinding_3D(latitude_drone, longitude_drone, altura_drone, latitude_destino, longitude_destino, altura_destino, quantidade_obstaculo);

    //Funcao que imprime quais pontos o drone vai passar
    cout<<"imprimindo o caminho"<<endl;
     for(int i = 0; i<N.size();i++){
        N[i].print_point();
        cout<<endl;
    }

    return 0;
}
