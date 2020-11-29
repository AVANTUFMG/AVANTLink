#include "pathfinding_output.h"
#include <iostream>
#include <fstream>
using namespace std;

vector <Point_O> pathfinding_2D(double lat_drone, double lon_drone, double h_drone, double lat_dest, double lon_dest, double h_dest, int q_obs){
    //Pathfinding 2D with output in txt

    //Iicializacao dos valores
    Malha_O M = transf_O(lat_drone, lon_drone, h_drone); //inicialização da malha
    Point_O destiny(lat_dest, lon_dest, h_dest);       //inicialização do destino
    vector <Point_O> Point_Os_list;                      //inicialização da lista de pontos que guardará o trajeto
    int arrived = 0;
    int pos = -1;

    int pos_aux, pos_aux2;
    double distance_aux;
    double distance = -1;

    //Inicializando arquivos
    ofstream output;
    output.open("output.txt");
    output << 2*M.get_N_lat()+1<<"x"<< 2*M.get_N_lon()+1<<endl;

    //Colocando obstaculo aleatorio
    gen_rand_obs_O(M, q_obs);

    //procurando os obstáculos e colocando no arquivo
    for(int i = 0; i<= M.get_N_Point_Os(); i++){
        if(M.malha[i].get_obs() == 1){
            output<< M.malha[i].get_x() << " " << M.malha[i].get_y()<<";";
            }
        }
    output << "/"<<endl;


    //Printando a malha
    //M.print_malha();
    //Vizinhos sempre são <posicao do vetor> + 1 / <pv> - 1 / <pv> + (2* n_lat +1) / <pv> - (2*n_lat + 1)
    //drone começa na posicao do vetor (tamanho do vetor)/2 ou seja em x,y,z = 0,0,0

    do{

        if(pos == -1){
            pos = M.get_malha().size()/2;
        }
        else{

            pos_aux = pos - 1; //ponto "a esquerda do drone"
            output << M.get_malha()[pos_aux].get_x() <<" " << M.get_malha()[pos_aux].get_y() <<";";
            if(M.get_malha()[pos_aux].get_obs() != 1){
                distance = M.get_malha()[pos_aux].distance_from(destiny);
            }


            pos_aux2 = pos + 1; //ponto "a direita do drone"
            output << M.get_malha()[pos_aux2].get_x() <<" " << M.get_malha()[pos_aux2].get_y() <<";";
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }


            pos_aux2 = pos - (M.get_N_lat()*2 + 1); //ponto "atras do drone"
            output << M.get_malha()[pos_aux2].get_x() <<" " << M.get_malha()[pos_aux2].get_y() <<";";
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

            pos_aux2 = pos - (M.get_N_lat()*2); //ponto "atras-esquerda do drone"
            output << M.get_malha()[pos_aux2].get_x() <<" " << M.get_malha()[pos_aux2].get_y() <<";";
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

            pos_aux2 = pos - (M.get_N_lat()*2 + 2); //ponto "atras-direita do drone"
            output << M.get_malha()[pos_aux2].get_x() <<" " << M.get_malha()[pos_aux2].get_y() <<";";
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }


            pos_aux2 = pos + (M.get_N_lat()*2 + 1); //ponto "a frente do drone"
            output << M.get_malha()[pos_aux2].get_x() <<" " << M.get_malha()[pos_aux2].get_y() <<";";
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

            pos_aux2 = pos + (M.get_N_lat()*2); //ponto "a frente-esquerda do drone"
            output << M.get_malha()[pos_aux2].get_x() <<" " << M.get_malha()[pos_aux2].get_y() <<";";
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

            pos_aux2 = pos + (M.get_N_lat()*2 + 2); //ponto "a frente-direita do drone"
            output << M.get_malha()[pos_aux2].get_x() <<" " << M.get_malha()[pos_aux2].get_y() <<";";
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

            output <<endl<< M.get_malha()[pos_aux].get_x() <<" " << M.get_malha()[pos_aux].get_y() <<";"<<endl; //colocando no arquivo o ponto selecionado

            pos = pos_aux;
            Point_Os_list.push_back(M.get_malha()[pos]);

            if(distance < 8){
            arrived = 1;
            }
        }
    }while(arrived == 0);

return Point_Os_list;
}


vector <Point_O> pathfinding_3D(double lat_drone, double lon_drone, double h_drone, double lat_dest, double lon_dest, double h_dest, int q_obs){
    //Fazer o construtor e destrutor copia da malha pode ser uma otima ideia

    //Iicializacao dos valores
    Malha_O M = transf_O(lat_drone, lon_drone, h_drone);
    Point_O destiny(lat_dest, lon_dest, h_dest);
    int arrived = 0;
    int pos = -1;
    vector <Point_O> Point_Os_list;

    //Colocando obstaculo aleatorio
    gen_rand_obs_O(M, q_obs);

    //Printando a malha
    //M.print_malha();

    //Vizinhos sempre são <posicao do vetor> + 1 / <pv> - 1 / <pv> + (2* n_lat +1) / <pv> - (2*n_lat + 1)
    //drone começa na posicao do vetor (tamanho do vetor)/2 ou seja em x,y,z = 0,0,0
    do{
        int pos_aux, pos_aux2;
        double distance_aux;
        double distance = -1;

        if(pos == -1){
            pos = M.get_malha().size()/2;
        }
        else{

            pos_aux = pos - 1; //ponto "a esquerda do drone"
            if(M.get_malha()[pos_aux].get_obs() != 1){
                distance = M.get_malha()[pos_aux].distance_from(destiny);
            }

            pos_aux2 = pos + 1; //ponto "a direita do drone"
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

            pos_aux2 = pos - (M.get_N_lat()*2 + 1); //ponto "atras do drone"
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

            pos_aux2 = pos + (M.get_N_lat()*2 + 1); //ponto "a frente do drone"
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

            pos_aux2 = pos - (M.get_N_lat()*2); //ponto "esquerda-atrás do drone"
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

            pos_aux2 = pos - (M.get_N_lat()*2 + 2); //ponto "direita-atrás do drone"
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

            pos_aux2 = pos + (M.get_N_lat()*2); //ponto "esquerda-frente do drone"
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

            pos_aux2 = pos + (M.get_N_lat()*2 + 2); //ponto "direita-frente do drone"
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

            pos_aux2 = pos + (M.get_N_lat()*2 + 1)*(M.get_N_lon()*2 + 1); //ponto acima do drone
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

            pos_aux2 = pos + (M.get_N_lat()*2 + 2)*(M.get_N_lon()*2 + 1); //ponto acima e frente do drone
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

            pos_aux2 = pos + (M.get_N_lat()*2 + 2)*(M.get_N_lon()*2 + 1) + 1; //ponto acima e diagonal frente-direita do drone
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

            pos_aux2 = pos + (M.get_N_lat()*2 + 2)*(M.get_N_lon()*2 + 1) - 1; //ponto acima e diagonal frente-esquerda do drone
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

            pos_aux2 = pos + (M.get_N_lat()*2)*(M.get_N_lon()*2 + 1); //ponto acima e atrás do drone
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

            pos_aux2 = pos + (M.get_N_lat()*2)*(M.get_N_lon()*2 + 1) + 1; //ponto acima e giagonal atrás-direita do drone
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

            pos_aux2 = pos + (M.get_N_lat()*2)*(M.get_N_lon()*2 + 1) - 1; //ponto acima e diagonal atrás-esquerda do drone
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

            pos_aux2 = pos + (M.get_N_lat()*2 + 1)*(M.get_N_lon()*2 + 1) + 1; //ponto acima e direita do drone
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

            pos_aux2 = pos + (M.get_N_lat()*2 + 1)*(M.get_N_lon()*2 + 1) - 1; //ponto acima e esquerda do drone
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

             pos_aux2 = pos - (M.get_N_lat()*2 + 1)*(M.get_N_lon()*2 + 1); //ponto abaixo do drone
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

            pos_aux2 = pos - (M.get_N_lat()*2 + 1)*(M.get_N_lon()*2 + 1) + 1; //ponto abaixo e direita do drone
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

            pos_aux2 = pos - (M.get_N_lat()*2 + 1)*(M.get_N_lon()*2 + 1) - 1; //ponto abaixo e esquerda do drone
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

            pos_aux2 = pos - (M.get_N_lat()*2 + 2)*(M.get_N_lon()*2 + 1); //ponto abaixo e atrás do drone
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

            pos_aux2 = pos - (M.get_N_lat()*2 + 2)*(M.get_N_lon()*2 + 1) + 1; //ponto abaixo e atrás-direita do drone
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

            pos_aux2 = pos - (M.get_N_lat()*2 + 2)*(M.get_N_lon()*2 + 1) - 1; //ponto abaixo e atrás-esquerda do drone
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

            pos_aux2 = pos - (M.get_N_lat()*2)*(M.get_N_lon()*2 + 1); //ponto abaixo e frente do drone
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

            pos_aux2 = pos - (M.get_N_lat()*2)*(M.get_N_lon()*2 + 1) + 1; //ponto abaixo e frente-direita do drone
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

            pos_aux2 = pos - (M.get_N_lat()*2)*(M.get_N_lon()*2 + 1) - 1; //ponto abaixo e frente-esquerda do drone
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

            pos = pos_aux;
            Point_Os_list.push_back(M.get_malha()[pos]);

            if(distance < 8){
            arrived = 1;
            }
        }
    }while(arrived == 0);

return Point_Os_list;
}
