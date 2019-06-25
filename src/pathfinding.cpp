#include "pathfinding.h"
using namespace std;

vector <Point> pathfinding_test(double lat_drone, double lon_drone, double h_drone, double lat_dest, double lon_dest, double h_dest, int q_obs){
    //Fazer o construtor e destrutor copia da malha pode ser uma otima ideia

    //Iicializacao dos valores
    Malha M = transf(lat_drone, lon_drone, h_drone);
    Point destiny(lat_dest, lon_dest, h_dest);
    int arrived = 0;
    int pos = -1;
    vector <Point> points_list;

    //Colocando obstaculo aleatorio
    gen_rand_obs(M, q_obs);

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

            //cout << pos << endl;
            pos_aux = pos - 1; //ponto "a esquerda do drone"
            //cout<<M.get_malha()[pos_aux].distance_from(destiny) << endl;
            if(M.get_malha()[pos_aux].get_obs() != 1){
                distance = M.get_malha()[pos_aux].distance_from(destiny);}
           //cout << "distancia = " << distance <<endl;


            pos_aux2 = pos + 1; //ponto "a direita do drone"
            //cout<<M.get_malha()[pos_aux2].distance_from(destiny) << endl;
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }
            //cout << "distancia = " << distance <<endl;


            pos_aux2 = pos - (M.get_N_lat()*2 + 1); //ponto "atras do drone"
            //cout<<M.get_malha()[pos_aux2].distance_from(destiny) << endl;
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }
            //cout << "distancia = " << distance <<endl;


            pos_aux2 = pos + (M.get_N_lat()*2 + 1); //ponto "a frente do drone"
            //cout<<M.get_malha()[pos_aux2].distance_from(destiny) << endl;
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }
            //cout << "distancia = " << distance <<endl;

            pos_aux2 = pos + (M.get_N_lat()*2 + 1)*(M.get_N_lon()*2+1); //ponto acima do drone
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

             pos_aux2 = pos - (M.get_N_lat()*2 + 1)*(M.get_N_lon()*2+1); //ponto abaixo do drone
            if(M.get_malha()[pos_aux2].get_obs() != 1){
                distance_aux = M.get_malha()[pos_aux2].distance_from(destiny);
                if(distance_aux <= distance){distance = distance_aux; pos_aux = pos_aux2;}
            }

            pos = pos_aux;
            points_list.push_back(M.get_malha()[pos]);
            //M.get_malha()[pos].print_point();


            if(distance < 8){
            arrived = 1;
            //M.get_malha()[pos].print_point();
            }
        }
    }while(arrived == 0);

return points_list;
}
