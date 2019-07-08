#include <iostream>
#include "pathfinding.h"
#include <cmath>
using namespace std;

int main()
{
    //------ PARTE DO MAIN DE TESTE PARA PATHFINDING------ //
    cout.precision(10); //apenas aumentando a precisao do cout

    /*
    Sobre a malha default:
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


    double latitude_destino = -19.866475; // Essa latitude equivale ao X = 600, Extremo "esquerdo"
    double longitude_destino = -43.96482; // Essa longitude equivale ao Y = 600, Extrema "cima"
    double altura_destino = 105; // Essa altura equivale ao Z = 45, Nao coloque o extremo de altura (default 120m ou Z = 60), bug a ser resolvido

    int quantidade_obstaculo = 2;

    //funcao de teste, vai retornar o caminho encontrado
    vector <Point> N = pathfinding_test(latitude_drone, longitude_drone, altura_drone, latitude_destino, longitude_destino, altura_destino, quantidade_obstaculo);
    //A malha gerada está dentro da funcao de pathfinding_test, caso deseje printar, descomentente "M.print_malha();" no pathfinding.cpp dentro da funcao "pathfinding.test",
    //porém em default temos muitos pontos na malha e demora pra printar, pode ser que queira talvez diminuir o N_lat, N_lon, N_H para a malha ficar menor

    //Funcao que irá imprimir quais pontos o drone vai passar
    cout<<"imprimindo o caminho"<<endl;
     for(int i = 0; i<N.size();i++){
        N[i].print_point();
        cout<<endl;
    }

    return 0;
}
